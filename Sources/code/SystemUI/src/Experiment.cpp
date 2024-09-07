#include "Experiment.h"

Experiment::Experiment(int argc, char* argv[])
{
	m_argc = argc;
	m_argv = argv;
}

Experiment::Experiment()
{

}

Experiment::~Experiment()
{

}

void Experiment::AutoDo()
{
	if (!InitCamera())
	{
		return;
	}

	pvcamTest();
}

bool Experiment::InitCamera()
{
	m_Cam = std::make_shared<CameraMoment>();
	if (!m_Cam->AutoDo(m_argc, m_argv))
	{
		CamErrOccr(m_Cam->getCamStatus());
		return EXP_ERR;
	}

	return EXP_SUC;
}

void Experiment::imageProcessing()
{
	cam_threadActive = true;
	while (cam_threadActive)
	{
		uint16_t* image = new uint16_t[picWidth * picHeight];
		std::memcpy(image, m_Cam->returnCapturedImage(), picWidth * picHeight * sizeof(uint16_t));
	}
}

bool Experiment::InitStage()
{
	return true;
}

void Experiment::pvcamTest()
{
	uint16_t* image = new uint16_t[picWidth * picHeight];
	std::memcpy(image, m_Cam->returnCapturedImage(), picWidth * picHeight * sizeof(uint16_t));

	for (int i = 0; i < 5; i++)
	{
		std::cout << image[i] << std::endl;
	}

	m_image_16bit = cv::Mat(picHeight, picWidth, CV_16UC1, image);
	m_image_16bit.convertTo(m_image_8bit, CV_8UC1, 255.0 / 65535.0);

	cv::imshow("1", m_image_8bit);
	cv::waitKey(0);
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

void Experiment::stageTest(int com)
{
	StageBase* m_stage = new StagePws(com);

	auto pos = std::make_pair(static_cast<double>(10), static_cast<double>(10));
	m_stage->AutoDo(pos);
	auto newpos = m_stage->getStagePosition();
	std::cout << newpos.first << " : " << newpos.second << std::endl;

	delete m_stage;
}
