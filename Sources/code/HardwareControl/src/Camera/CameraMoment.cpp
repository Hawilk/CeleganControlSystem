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

void CameraMoment::AutoDo(int argc, char* argv[])
{
	//检查SDK运行状态
	if (!showCameraInformation(argc, argv))
		return;

	//初始化相机句柄，找到相机
	if (!initCameraData())
		return;
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
	return CAM_SUC;
}

bool CameraMoment::returnCapturedImage()
{
	return CAM_SUC;
}
