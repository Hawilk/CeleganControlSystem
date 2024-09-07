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
	if (m_Cam != nullptr)
		delete m_Cam;
}

void Experiment::pvcamTest()
{
	uint16_t* image = new uint16_t[picWidth * picHeight];
	std::memcpy(image, m_Cam->returnCapturedImage(), picWidth * picHeight * sizeof(uint16_t));

	m_image = cv::Mat(picHeight, picWidth, CV_16UC1, image);
	m_image.convertTo(m_image, CV_8UC1, 255.0 / 65535.0);

	cv::imshow("1", m_image);
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
