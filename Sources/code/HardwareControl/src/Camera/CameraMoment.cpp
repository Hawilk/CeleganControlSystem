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
		//�ر���������ر�PVCAM����������һ����������
		CloseCamera(context);
		UninitPVCAM(contexts);
	}
}

bool CameraMoment::AutoDo(int argc, char* argv[])
{
	//���SDK����״̬
	if (!showCameraInformation(argc, argv))
		return CAM_ERR;

	//��ʼ�����������ҵ����
	if (!initCameraData())
		return CAM_ERR;

	//�����ʼ����
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

	//ȡ���ҵ���������
	this->context = contexts.at(cSingleCamIndex);

	//����������װ ctrl + c ����
	if (!InstallGenericCliTerminationHandler(contexts))
	{
		CloseAllCamerasAndUninit(contexts);
		this->camOperaStatus = CameraStatus::InitCamFailed;
		return CAM_ERR;
	}

	//���������Ƿ��б����䵽�ڴ�
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
	//�˴����Բο�Pvcam SDKʾ������ �趨���ⴥ����ʵ������

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

	//�趨�����ں�����Ϊ2
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

	//�������ⴥ���� ���������ع�
	PeriodicTimerStart();

	return CAM_SUC;
}

uint16_t* CameraMoment::returnCapturedImage()
{
	//�ȴ����������㷵�� Eof ָ��ץȡ��Ƭ
	if (!WaitForEofEvent(context, 5000, errorOccurred))
		return CAM_ERR;

	//ȡ���ڴ��е���Ƭ
	const uns16* pBuffer = reinterpret_cast<const uns16*>(context->eofFrame);

	//���һ�ݵ�ַ���ڴ� ���ظ��ⲿ�ӿ� �ṩ��Ƭ��ַ
	std::memcpy(imageData, pBuffer, sizeof(imageData));

	return imageData;
}

void CameraMoment::PeriodicTimerStart()
{
	//�������ⶨʱ������
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
					// �ñ�����ڿ��ǹر� or ���Ͻ�������־log��
					//ԭ��������ع��ڼ�����عⴥ�������¸ôδ���ʧЧ
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
