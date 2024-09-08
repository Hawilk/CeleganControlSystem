#include "Experiment.h"

Experiment::Experiment(int argc, char* argv[])
{
	m_argc = argc;
	m_argv = argv;
	m_com  = 3;
	cam_threadActive = false;
	stage_threadActive = false;

	Data = Parameters::getInstance()->getParam();
	InitPanelParam();
}

Experiment::Experiment()
{

}

Experiment::~Experiment()
{
	stopCamThread();
	stopStageThread();

	SavePanelParam();
}

void Experiment::AutoDo()
{
	if (!InitStage())
	{
		return;
	}

	if (!InitCamera())
	{
		return;
	}

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

	//开启相机线程
	m_CamThread = std::thread(&Experiment::imageProcessing, this);
	//waitCamThreadStart();

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
		m_image_8bit = cv::Mat(picHeight, picWidth, CV_8UC1, dstImage);

		//将图像放入临界区，使用信号量管理
		{
			std::lock_guard<std::mutex> lock(originImage_mtx);
			if (originImages.size() >= MAX_QUEUE_SIZE)
			{
				originImages.pop_front();
			}
			originImages.push_back(m_image_8bit);
		}
		cond_unprocessed.notify_one();

		delete[] image;
	}
	delete[] dstImage;
}

bool Experiment::InitStage()
{
	m_Stage = std::make_shared<StagePws>(m_com);

	//开启位移台线程
	m_StageThread = std::thread(&Experiment::stageDisplacing, this);
	waitStageThreadStart();

	return EXP_SUC;
}

void Experiment::stageDisplacing()
{
	auto pos = std::make_pair(panelParam.initialPos_x, panelParam.initialPos_y);
	m_Stage->AutoDo(pos);

	stage_threadActive = true;
	while (stage_threadActive)
	{
		
	}
}

void Experiment::waitStageThreadStart()
{
	while (!stage_threadActive)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "wait for stage initializing" << std::endl;
	}
}

void Experiment::stopStageThread()
{
	//停止线程
	if (stage_threadActive)
	{
		stage_threadActive = false;
		if (m_StageThread.joinable())
			m_StageThread.join();
	}
}

void Experiment::pvcamTest()
{
	std::pair<double, double> item;
	//while (cam_threadActive && stage_threadActive)
	int i = 0;
	while(true)
	{
		cv::Mat image;
		{
			std::unique_lock<std::mutex> lock(originImage_mtx);
			if (originImages.empty())
			{//等待deque不为空
				cond_unprocessed.wait(lock);
			}
			image = originImages.front();
			originImages.pop_front();
		}

		cv::imshow("Origin Image", image);
		auto key = cv::waitKey(1);

		double disp = 0.1;
		if (key == 27)
			break;
		else if (key == 50)
		{//下
			m_Stage->moveStageByDirection(Direction::Down, disp);
		}
		else if (key == 56)
		{//上
			m_Stage->moveStageByDirection(Direction::Up, disp);
		}
		else if (key == 52)
		{//左
			m_Stage->moveStageByDirection(Direction::Left, disp);
		}
		else if (key == 54)
		{//右
			m_Stage->moveStageByDirection(Direction::Right, disp);
		}
	}

	panelParam.initialPos_x = item.first;
	panelParam.initialPos_y = item.second;
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
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		std::cout << "wait for cam take a pic" << std::endl;
	}
}

void Experiment::stopCamThread()
{
	//停止线程
	if (cam_threadActive)
	{
		cam_threadActive = false;
		if (m_CamThread.joinable())
			m_CamThread.join();
	}
}
              