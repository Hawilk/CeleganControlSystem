/*
 *@file     CameraMoment.h
 *@brief    Moment相机类
 *@author   yangshuhao
 *@date     2024/9/1
 *@remarks
 *@version  1.1
 */

#pragma once
#include "CameraBase.h"
#include "Common.h"

class CameraMoment : public CameraBase
{
public:
	CameraMoment();
	~CameraMoment();

	/*************** 外部可使用接口 ****************/

	//自动化过程
	bool AutoDo(int argc, char* argv[]) override;

	//返回一张拍摄的照片 使用该内存推荐深拷贝
	uint16_t* returnCapturedImage() override;

private:
	//显示相机信息
	bool showCameraInformation(int argc, char* argv[]) override;

	//找到相机并初始化完成
	bool initCameraData() override;

	//开始进行照片拍摄
	bool beginGrabFrames() override;

	//开启虚拟触发 定时曝光
	void PeriodicTimerStart();

private:
	/************ Moment 相机内部参数 ****************/
	CameraContext*                context;   //相机句柄
	std::vector<CameraContext*>   contexts;  //相机句柄vec

	uns32 exposureBytes;      //曝光字节
	uns16 circBufferFrames;   //一次缓存的帧数
	int16 bufferMode;         //曝光模式
	uns32 circBufferBytes;    //一次缓存的字节数
	uns8* circBufferInMemory; //循环缓存的内存大小
	uns32 intervalMs;         //照片间隔

	bool  errorOccurred;      //抓取照片错误

private:
	bool          g_periodicTimerActive;  //触发器激活状态
	std::thread   g_periodicTimerThread;  //触发器线程
};