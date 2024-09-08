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
#include <atomic>
#include <chrono>
#include <thread>
#include <mutex>

#include "CameraMoment.h"
#include "StagePws.h"
#include "commonAlgorithm.h"
#include "Parameters.h"

class Experiment
{
	/*************** 类外部接口 ****************/
public:
	Experiment();
	Experiment(int argc, char* argv[]);
	~Experiment();

	//类功能启动入口
	void AutoDo();

	void pvcamTest();
	void CamErrOccr(CameraStatus status);
	void stageTest(int com);

	/*************** 类内部实现 ****************/
private:  
	//加载控制面板参数
	void InitPanelParam();

	//保存控制面板参数
	void SavePanelParam();

	//初始化相机
	bool InitCamera();

	//图像处理线程内部
	void imageProcessing();

	//等待相机线程启动
	void waitCamThreadStart();

	//关闭相机线程
	void stopCamThread();

	//初始化位移台
	bool InitStage();

	//位移台移动线程内部
	void stageDisplacing();

	//等待位移台线程启动
	void waitStageThreadStart();

	//关闭位移台线程
	void stopStageThread();

	/************** 类内部成员变量 *************/
private:
	cv::Mat        m_image_16bit; //内部原始图像(16位深）
	cv::Mat        m_image_8bit;  //显示图像(8位深）

	CameraBasePtr  m_Cam;         //Moment相机
	StageBasePtr   m_Stage;       //Pws位移台
	std::thread    m_CamThread;   //拍摄线程（处理图像）
	std::thread    m_StageThread; //位移台线程

	std::atomic<bool>  cam_threadActive;  //相机线程状态
	std::atomic<bool>  stage_threadActive;//位移台线程状态
	std::mutex     image_mtx;     //图片加锁

	std::map<std::string, std::string> Data; //配置文件参数 原始数据

	struct PanelParam
	{
		double  initialPos_x;   //初始位置
		double  initialPos_y;
	}panelParam;

	/************** 类内部系统变量 *************/
private:
	int     m_argc;
	char**  m_argv;
	int     m_com;     //位移台端口号
};
typedef std::unique_ptr<Experiment> ExperimentPtr;