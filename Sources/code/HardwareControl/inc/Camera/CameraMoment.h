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

	/*********** 基类方法重写 *************/
	void AutoDo(int argc, char* argv[]) override;
	bool showCameraInformation(int argc, char* argv[]) override;
	bool initCameraData() override;
	bool beginGrabFrames() override;
	bool returnCapturedImage() override;

	/*********** Moment中通用方法 *********/
	

private:
	CameraContext* context;   //相机句柄
	std::vector<CameraContext*> contexts;  //相机句柄vec

	uns32 exposureBytes;      //曝光字节
	uns16 circBufferFrames;   //一次缓存的帧数
	int16 bufferMode;         //曝光模式
	uns32 circBufferBytes;    //一次缓存的字节数
	uns8* circBufferInMemory; //循环缓存的内存大小
};