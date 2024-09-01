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
		//�ر���������ر�PVCAM����������һ����������
		CloseCamera(context);
		UninitPVCAM(contexts);
	}
}

void CameraMoment::AutoDo(int argc, char* argv[])
{
	//���SDK����״̬
	if (!showCameraInformation(argc, argv))
		return;

	//��ʼ�����������ҵ����
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

	//ȡ���ҵ���������
	this->context = contexts.at(cSingleCamIndex);

	//����������װ ctrl + c ����
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
