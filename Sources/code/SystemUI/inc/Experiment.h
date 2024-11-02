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
#include <deque>
#include <condition_variable>

#include "CameraMoment.h"
#include "StagePws.h"
#include "commonAlgorithm.h"
#include "Parameters.h"
#include "NematodeProcess.h"

class Experiment
{
	/*************** 类外部接口 ****************/
public:
	Experiment();
	Experiment(int argc, char* argv[]);
	~Experiment();

	//类功能启动入口
	void AutoDo();

	/*
	* 光电刺激模块功能
	*/
	void setLedPercent(uint32_t value);     //设置光强
	void setLedSwitch();                    //光遗传开关

	/*
	* 图像处理模块功能
	*/
	cv::Mat getCurImage();                  //获取当前图像
	cv::Mat getCurImageWithInfo();		    //获取当前图像（带参数信息）
	cv::Mat getCurPrcImage();				//获取已处理图像
	cv::Mat getCurPrcImageWithIndicate();   //获取已处理图像（带参数信息）
	uint32_t getCurFrame();					//获取当前帧数
	uint32_t getCurFPS();					//获取当前帧率
	void setMask(MaskType m_type);			//设置掩膜
	void setRadius(uint32_t radius);		//设置半径
	void setCenterLine(uint32_t centerline);//设置中心线
	void setBinThresh(uint32_t thresh);		//设置二值化阈值
	void setDenoise(uint32_t param);		//设置去噪参数
	void beginProcess();					//开始图像处理
	void endProcess();						//结束图像处理
	void contrastImage();					//增强对比度

	/*
	* 存储模块功能
	*/

	/*
	* 位移台控制模块功能
	*/

	/*************** 类内部实现 ****************/
private:  
	/*--------------- 硬件流程 ----------------*/
	void InitPanelParam();      //加载控制面板参数
	void SavePanelParam();      //保存控制面板参数

	bool InitCamera();          //初始化相机
	void imageCapturing();      //拍摄线程内部

	bool InitStage();           //初始化位移台
	void stageDisplacing();     //位移台移动线程内部

	void InitProcessing();      //初始化图像处理模块
	void imageProcessing();     //图像处理线程内部

	/*---------------- Common ----------------*/
	//初始化内部变量
	void initInternalVar(int& argc, char* argv[]);

	//等待线程启动
	void waitThreadStart(std::atomic<bool>& active, uint8_t time_ms);

	//等待线程停止
	void stopThread(std::atomic<bool>& active, std::thread& thrd);

	//根据错误原因打印数据
	void CamErrOccr(CameraStatus status);

	//重置Param中的位移台初始位置
	void resetParamInitialPos();

	//将拍摄的图片放入对应的线程，并发出对应的信号量
	void pushImageToThread(cv::Mat& image, std::mutex& mtx, std::deque<cv::Mat>& images, std::condition_variable& cond);

public:
	/*-------------- 仅供测试 ----------------*/
	void pvcamTest();
	bool handleKey(int& key);
	void picProcessTest();

	/************** 类内部成员变量 *************/
private:
	std::deque<cv::Mat>  originImages;   //原始图像队列
	std::deque<cv::Mat>  unprocessedImages;  //未处理的图像 -- PS：该队列在当前版本只取用队尾的图像，也就是最新拍摄的一帧图像。出于处理图像的速度远远小于拍摄图像的速度，后续若考虑对每一帧图像进行处理，可以采用线程池对该队列进行优化处理。

	CameraBasePtr  m_Cam;           //Moment相机
	StageBasePtr   m_Stage;         //Pws位移台
	std::thread    m_CamThread;     //拍摄线程
	std::thread    m_StageThread;   //位移台线程
	std::thread    m_ProcessThread; //图像处理线程
	std::atomic<bool>  cam_threadActive;     //相机线程状态
	std::atomic<bool>  stage_threadActive;   //位移台线程状态 
	std::atomic<bool>  process_threadActive; //图像处理线程状态
	std::mutex     originImage_mtx;          //原始图片加锁
	std::mutex     unprocessedImage_mtx;     //待处理图片加锁

	std::condition_variable cond_origin;      //原始图像信号量
	std::condition_variable cond_unprocessed; //未处理图像信号量
	std::condition_variable cond_processed;   //图像处理完毕信号量

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