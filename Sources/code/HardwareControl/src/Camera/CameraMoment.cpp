#include "CameraMoment.h"
#include <vector>

CameraMoment::CameraMoment()
{
	context = nullptr;

	exposureBytes = 0;
	circBufferFrames = 20;
	bufferMode = CIRC_OVERWRITE;
	circBufferBytes = 0;
	circBufferInMemory = nullptr;
	intervalMs = 32;

	g_periodicTimerActive = false;
	errorOccurred = false;
}

CameraMoment::~CameraMoment()
{
	if (context != nullptr)
	{
		//关闭相机，并关闭PVCAM（仅适用于一个相机情况）
		CloseCamera(context);
		UninitPVCAM(contexts);
	}
}

bool CameraMoment::AutoDo(int argc, char* argv[])
{
	//检查SDK运行状态
	if (!showCameraInformation(argc, argv))
		return CAM_ERR;

	//初始化相机句柄，找到相机
	if (!initCameraData())
		return CAM_ERR;

	//相机开始拍照
	if (!beginGrabFrames())
		return CAM_ERR;

	return CAM_SUC;
}

bool CameraMoment::showCameraInformation(int argc, char* argv[])
{
	if (!ShowAppInfo(argc, argv))
	{
		this->camOperaStatus = CameraStatus::ShowInfoFailed;
		return CAM_ERR;
	}

	this->camOperaStatus = CameraStatus::ShowInfoSuccess;
	return CAM_SUC;
}

bool CameraMoment::initCameraData()
{
	if (!InitAndOpenOneCamera(contexts, cSingleCamIndex))
	{
		this->camOperaStatus = CameraStatus::InitCamFailed;
		return CAM_ERR;
	}

	//取出找到的相机句柄
	this->context = contexts.at(cSingleCamIndex);

	//给相机句柄安装 ctrl + c 按键
	if (!InstallGenericCliTerminationHandler(contexts))
	{
		CloseAllCamerasAndUninit(contexts);
		this->camOperaStatus = CameraStatus::InitCamFailed;
		return CAM_ERR;
	}

	//检查相机里是否有被分配到内存
	if (this->context == nullptr)
	{
		this->camOperaStatus = CameraStatus::InitCamFailed;
		return CAM_ERR;
	}

	this->camOperaStatus = CameraStatus::InitCameSuccess;
	return CAM_SUC;
}

bool CameraMoment::beginGrabFrames()
{
	//此处可以参考Pvcam SDK示例代码 设定虚拟触发器实现拍照

	const int16 selectedExposureMode = EXT_TRIG_SOFTWARE_EDGE;

	NVPC supportedExposeOutModes;
	if (!ReadEnumeration(context->hcam, &supportedExposeOutModes, PARAM_EXPOSE_OUT_MODE,
		"PARAM_EXPOSE_OUT_MODE"))
	{
		this->camOperaStatus = CameraStatus::BeginGrabFrameFailed;
		CloseAllCamerasAndUninit(contexts);
		return CAM_ERR;
	}
	const int16 selectedExposeOutMode = static_cast<int16>(supportedExposeOutModes[0].value);

	if (PV_OK != pl_cam_register_callback_ex3(context->hcam, PL_CALLBACK_EOF,
		(void*)GenericEofHandler, context))
	{
		this->camOperaStatus = CameraStatus::BeginGrabFrameFailed;
		CloseAllCamerasAndUninit(contexts);
		return CAM_ERR;
	}

	//设定像素融合因子为2
	context->region.sbin = 2;
	context->region.pbin = 2;

	const int16 expMode = selectedExposureMode | selectedExposeOutMode;

	if (PV_OK != pl_exp_setup_cont(context->hcam, 1, &context->region, expMode,
		exposureTime, &exposureBytes, bufferMode))
	{
		this->camOperaStatus = CameraStatus::BeginGrabFrameFailed;
		CloseAllCamerasAndUninit(contexts);
		return CAM_ERR;
	}
	UpdateCtxImageFormat(context);

	circBufferBytes = circBufferFrames * exposureBytes;
	circBufferInMemory = new (std::nothrow) uns8[circBufferBytes];

	if (PV_OK != pl_exp_start_cont(context->hcam, circBufferInMemory, circBufferBytes))
	{
		this->camOperaStatus = CameraStatus::BeginGrabFrameFailed;
		CloseAllCamerasAndUninit(contexts);
		delete[] circBufferInMemory;
		return CAM_ERR;
	}

	//开启虚拟触发器 进行连续曝光
	PeriodicTimerStart();

	return CAM_SUC;
}

uint16_t* CameraMoment::returnCapturedImage()
{
	//等待相机完成拍摄返回 Eof 指令抓取照片
	if (!WaitForEofEvent(context, 5000, errorOccurred))
		return CAM_ERR;

	//取出内存中的照片
	const uns16* pBuffer = reinterpret_cast<const uns16*>(context->eofFrame);

	//深拷贝一份地址的内存 返回给外部接口 提供照片地址
	std::memcpy(imageData, pBuffer, sizeof(imageData));

	return imageData;
}

void CameraMoment::PeriodicTimerStart()
{
	//开启虚拟定时触发器
	g_periodicTimerActive = true;
	g_periodicTimerThread = std::thread([this]()
		{
			unsigned int triggerCount = 0;
			auto nextTrigTime = std::chrono::steady_clock::now();
			while (g_periodicTimerActive)
			{
				nextTrigTime += std::chrono::milliseconds(intervalMs);

				uns32 flags = 0;
				if (PV_OK != pl_exp_trigger(context->hcam, &flags, 0))
				{
					PrintErrorMessage(pl_error_code(), "SW Trigger failed, pl_exp_trigger() error");
					break;
				}
				++triggerCount;

				switch (flags)
				{
				case PL_SW_TRIG_STATUS_IGNORED:
					// 该报错后期考虑关闭 or 整合进报错日志log里
					//原因：在相机曝光期间进行曝光触发，导致该次触发失效
					printf("SW Trigger #%u ignored (triggering too fast?)\n", triggerCount);
					break;
				case PL_SW_TRIG_STATUS_TRIGGERED:
					printf("SW Trigger #%u accepted\n", triggerCount);
					break;
				default:
					printf("SW Trigger #%u: Unknown status\n", triggerCount);
					break;
				}
				std::this_thread::sleep_until(nextTrigTime);
			}
		});
}
