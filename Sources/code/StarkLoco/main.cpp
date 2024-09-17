#include "Experiment.h"

int main(int argc, char* argv[])
{
	/*ExperimentPtr exp = std::make_unique<Experiment>(argc, argv);

	exp->AutoDo();*/

	NematodeProcessPtr np = std::make_shared<NematodeProcess>();
	uint32_t r = 275;
	np->createCircleMask(r, 800, 550);
	
// 	cv::Mat mask = np->getMask();
// 	cv::imshow("mask", mask);
	cv::Mat colorImage = cv::imread("D:/Hasuyo/Code_files/Matlab_Code/视频提取脚本/extracted_frame.png", cv::IMREAD_COLOR);
	if (colorImage.empty()) {
		std::cerr << "无法读取图像文件!" << std::endl;
		return -1;
	}

	cv::Mat grayImage;
	cv::cvtColor(colorImage, grayImage, cv::COLOR_BGR2GRAY);
	//cv::GaussianBlur(grayImage, grayImage, cv::Size(9, 9), 0);
	np->setBinThresh(50);
	auto picinfo = np->AutoDo(grayImage);
#if 0
	for (const auto& point : picinfo->centerLine)
	{
		cv::circle(colorImage, point, 3, cv::Scalar(0, 255, 0), -1);
	}

	for (const auto& point : picinfo->left_contour)
	{
		cv::circle(colorImage, point, 3, cv::Scalar(255, 0, 0), -1);
	}
	for (const auto& point : picinfo->right_contour)
	{
		cv::circle(colorImage, point, 3, cv::Scalar(0, 0, 255), -1);
	}
#else
	/*for (const auto& point : picinfo->contour)
	{
		cv::circle(colorImage, point, 3, cv::Scalar(0, 255, 0), -1);
	}*/
	cv::circle(colorImage, picinfo->curHead, 3, cv::Scalar(0, 255, 0), -1);
	cv::circle(colorImage, picinfo->curTail, 3, cv::Scalar(255, 0, 0), -1);
#endif

	cv::imshow("grayImage", colorImage);
	cv::waitKey(0);

    return 0;
}