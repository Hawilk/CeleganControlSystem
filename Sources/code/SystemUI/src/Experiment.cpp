#include "Experiment.h"

Experiment::Experiment()
{

}

Experiment::~Experiment()
{

}

void Experiment::print()
{
	printhello();
	std::cout << "hello_world" << std::endl;
}

void Experiment::matTest()
{
	cv::Mat img;
	img = cv::imread("D:/Hasuyo/Code_files/C++_Code/opencv480test//test.jpg"); // �ĳ��Լ���ͼƬ·��
	if (img.empty())
	{
		std::cout << "��ȷ��ͼ���ļ����Ƿ���ȷ" << std::endl;
	}
	cv::imshow("test", img);
	cv::waitKey(0);
}

void Experiment::pvcamTest(int argc, char* argv[])
{
	CameraBase* cam = new CameraMoment;
	cam->AutoDo(argc, argv);
	CamErrOccr(cam->getCamStatus());

	delete cam;
	std::cout << "pvcamTest" << std::endl;
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