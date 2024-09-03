#include "Experiment.h"

Experiment::Experiment(int argc, char* argv[])
{
	//初始化相机
	m_Cam = new CameraMoment;
	if (!m_Cam->AutoDo(argc, argv))
		CamErrOccr(m_Cam->getCamStatus());

}

Experiment::Experiment()
{

}

Experiment::~Experiment()
{

}

void Experiment::pvcamTest(int argc, char* argv[])
{
	CameraBase* cam = new CameraMoment;

	//当初始化相机失败，就调用接口查看失败原因
	if(!cam->AutoDo(argc, argv))
		CamErrOccr(cam->getCamStatus());
}

void Experiment::CamErrOccr(CameraStatus status)
{
	switch (status)
	{
	case CameraStatus::BeginGrabFrameFailed:
	{
		std::cout << "Begin Grab Frame Failed" << std::endl;
		break;
	}
	case CameraStatus::GrabFrameFailed:
	{
		std::cout << "Grab Frame Failed" << std::endl;
		break;
	}
	case CameraStatus::InitCamFailed:
	{
		std::cout << "Init Cam Failed" << std::endl;
		break;
	}
	case CameraStatus::ShowInfoFailed:
	{
		std::cout << "Show SDK Information Failed" << std::endl;
		break;
	}
	default:
		break;
	}
}
