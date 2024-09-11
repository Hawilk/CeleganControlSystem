#include "Experiment.h"

Experiment::Experiment(int argc, char* argv[])
{
	initInternalVar(argc, argv);

	InitPanelParam();
}

Experiment::Experiment()
{

}

Experiment::~Experiment()
{
	stopThread(cam_threadActive, m_CamThread);
	stopThread(process_threadActive, m_ProcessThread);
	stopThread(stage_threadActive, m_StageThread);

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

	InitProcessing();

	//图像显示测试
	pvcamTest();
}

void Experiment::InitPanelParam()
{
	Data = Parameters::getInstance()->getParam();

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
	m_CamThread = std::thread(&Experiment::imageCapturing, this);
	waitThreadStart(cam_threadActive, 10);

	return EXP_SUC;
}

void Experiment::imageCapturing()
{
	cam_threadActive = true;
	uint8_t* dstImage = new uint8_t[picWidth * picHeight];
	while (cam_threadActive)
	{
		uint16_t* image = new uint16_t[picWidth * picHeight];
		std::memcpy(image, m_Cam->returnCapturedImage(), picWidth * picHeight * sizeof(uint16_t));

		std::pair<uint16_t, uint16_t> extrema = commonAlgorithm::findExtremaInImage(image);
		commonAlgorithm::histogramEqualization(dstImage, image, extrema);
		cv::Mat image_8bit = cv::Mat(picHeight, picWidth, CV_8UC1, dstImage);

		//将图像放入临界区，使用信号量管理
		pushImageToThread(image_8bit, originImage_mtx, originImages, cond_origin);
		pushImageToThread(image_8bit, unprocessedImage_mtx, unprocessedImages, cond_unprocessed);

		delete[] image;
	}
	delete[] dstImage;
}

bool Experiment::InitStage()
{
	m_Stage = std::make_shared<StagePws>(m_com);

	//开启位移台线程
	m_StageThread = std::thread(&Experiment::stageDisplacing, this);
	waitThreadStart(stage_threadActive, 500);

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

void Experiment::InitProcessing()
{
	m_ProcessThread = std::thread(&Experiment::imageProcessing, this);
	waitThreadStart(process_threadActive, 10);
}

void Experiment::imageProcessing()
{
	process_threadActive = true;
	while (process_threadActive)
	{
		cv::Mat image;
		{
			std::unique_lock<std::mutex> lock(unprocessedImage_mtx);
			if (unprocessedImages.empty())
			{//等待deque不为空
				cond_unprocessed.wait(lock);
			}
			//此处逻辑与直接拿到图片显示不一样，从队尾取出最新拍照的图像，然后进行处理
			image = unprocessedImages.back();
			unprocessedImages.pop_back();
		}

		//后续处理操作
		std::this_thread::sleep_for(std::chrono::milliseconds(100));  //此处模拟图像处理的速度远小于拍摄的速度
	}
}

void Experiment::initInternalVar(int& argc, char* argv[])
{
	m_argc = argc;
	m_argv = argv;
	m_com = 3;
	cam_threadActive = false;
	stage_threadActive = false;
	process_threadActive = false;
}

void Experiment::waitThreadStart(std::atomic<bool>& active, uint8_t time_ms)
{
	//主要用于等待线程标志置真
	while (!active)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
	}
}

void Experiment::stopThread(std::atomic<bool>& active, std::thread& thrd)
{
	if (active)
	{
		active = false;
		if (thrd.joinable())
			thrd.join();
	}
}

void Experiment::resetParamInitialPos()
{
	auto item = m_Stage->getStagePosition();
	panelParam.initialPos_x = item.first;
	panelParam.initialPos_y = item.second;
}

void Experiment::pushImageToThread(cv::Mat& image, std::mutex& mtx, std::deque<cv::Mat>& images, std::condition_variable& cond)
{
	{
		std::lock_guard<std::mutex> lock(mtx);
		if (images.size() >= MAX_QUEUE_SIZE)
		{
			images.pop_front();
		}
		images.push_back(image);
	}
	cond.notify_one();
}

void Experiment::pvcamTest()
{
	while(true)
	{
		cv::Mat image;
		{
			std::unique_lock<std::mutex> lock(originImage_mtx);
			if (originImages.empty())
			{//等待deque不为空
				cond_origin.wait(lock);
			}
			image = originImages.front();
			originImages.pop_front();
		}

		cv::imshow("Origin Image", image);
		auto key = cv::waitKey(1);

		if (!handleKey(key))
			break;
	}

	resetParamInitialPos();
}

bool Experiment::handleKey(int& key)
{
	double disp = 0.1;
	if (key == 27)
		return false;
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
	
	return true;
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