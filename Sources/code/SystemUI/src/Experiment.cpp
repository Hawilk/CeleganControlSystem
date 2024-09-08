#include "Experiment.h"

Experiment::Experiment(int argc, char* argv[])
{
	m_argc = argc;
	m_argv = argv;

	Data = Parameters::getInstance()->getParam();
	InitPanelParam();
}

Experiment::Experiment()
{

}

Experiment::~Experiment()
{
	SavePanelParam();

	//停止线程
	if (cam_threadActive)
	{
		cam_threadActive = false;
		if (m_CamThread.joinable())
			m_CamThread.join();
	}
}

void Experiment::AutoDo()
{
	if (!InitCamera())
	{
		return;
	}

	m_CamThread = std::thread(&Experiment::imageProcessing, this);
	pvcamTest();
}

void Experiment::InitPanelParam()
{
	for (const auto& item : Data)
	{
		if (item.first == "InitPosition_x")
		{
			panelParam.initialPos_x = std::stod(item.second);
		}
		else if (item.first == "InitPosition_y")
		{
			panelParam.initialPos_y = std::stod(item.second);
		}
	}
}

void Experiment::SavePanelParam()
{
	auto item = Parameters::getInstance();
	item->set("InitPosition_x", std::to_string(panelParam.initialPos_x));
	item->set("InitPosition_y", std::to_string(panelParam.initialPos_y));

	item->saveData();
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
	uint8_t* dstImage = new uint8_t[picWidth * picHeight];
	while (cam_threadActive)
	{
		uint16_t* image = new uint16_t[picWidth * picHeight];
		std::memcpy(image, m_Cam->returnCapturedImage(), picWidth * picHeight * sizeof(uint16_t));

		std::pair<uint16_t, uint16_t> extrema = commonAlgorithm::findExtremaInImage(image);
		commonAlgorithm::histogramEqualization(dstImage, image, extrema);

		//图片写入加锁  防止数据竞争
		image_mtx.lock();
		m_image_8bit = cv::Mat(picHeight, picWidth, CV_8UC1, dstImage);
		image_mtx.unlock();

		delete[] image;
	}
	delete[] dstImage;
}

bool Experiment::InitStage()
{
	m_Stage = std::make_shared<StagePws>(m_com);
	auto pos = std::make_pair(panelParam.initialPos_x, panelParam.initialPos_y);

	panelParam.initialPos_x = 1.234;

	return true;
}

void Experiment::pvcamTest()
{
	waitCamThreadStart();

	while (cam_threadActive)
	{
		if(m_image_8bit.empty())
			continue;

		image_mtx.lock();
		cv::imshow("1", m_image_8bit);
		image_mtx.unlock();
		auto key = cv::waitKey(100);

		if (key == 27)
			break;
	}
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

void Experiment::waitCamThreadStart()
{
	while (!cam_threadActive)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::cout << "wait for cam take a pic" << std::endl;
	}
}
