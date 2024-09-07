/*
 *@file     Experiment.h
 *@brief    控制系统实验类
 *@author   yangshuhao
 *@date     2024/8/31
 *@remarks
 *@version  1.1
 */

#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "CameraBase.h"
#include "CameraMoment.h"
#include "StagePws.h"

class Experiment
{
public:
	Experiment();
	Experiment(int argc, char* argv[]);
	~Experiment();

	void pvcamTest();
	void CamErrOccr(CameraStatus status);
	void stageTest(int com);

private:
	cv::Mat m_image;    //exp内部原始图像

	CameraBase*  m_Cam;         //Moment相机
	std::thread  m_CamThread;   //拍摄线程（处理图像）
};
typedef std::unique_ptr<Experiment> ExperimentPtr;