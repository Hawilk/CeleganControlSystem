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
#include "commonAlgorithm.h"

class Experiment
{
public:
	Experiment();
	Experiment(int argc, char* argv[]);
	~Experiment();

	void AutoDo();

	//初始化相机
	bool InitCamera();

	//图像处理线程内部
	void imageProcessing();

	//初始化位移台
	bool InitStage();

	void pvcamTest();
	void CamErrOccr(CameraStatus status);
	void stageTest(int com);

private:
	cv::Mat        m_image_16bit; //内部原始图像(16位深）
	cv::Mat        m_image_8bit;  //显示图像(8位深）

	CameraBasePtr  m_Cam;         //Moment相机
	StageBasePtr   m_Stage;       //Pws位移台
	std::thread    m_CamThread;   //拍摄线程（处理图像）
	std::thread    m_StageThread; //位移台线程

	bool  cam_threadActive;       //相机线程状态
	bool  stage_threadActive;     //位移台线程状态

private:
	int     m_argc;
	char**  m_argv;
};
typedef std::unique_ptr<Experiment> ExperimentPtr;