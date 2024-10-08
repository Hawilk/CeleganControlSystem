/*
 *@file     CameraBase.h
 *@brief    相机基类
 *@author   yangshuhao
 *@date     2024/9/1
 *@remarks
 *@version  1.1
 */

#pragma once
#include "const_def.h"
#include <stdint.h>
#include <memory>

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	/**
	 * @brief    自动化运行过程
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    int argc, char** argv
	 */
	virtual bool AutoDo(int argc, char* argv[]) = 0;

	/**
	 * @brief    显示相机信息
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    int argc, char** argv
	 * @return   bool::false-程序错误 true-显示正确
	 */
	virtual bool showCameraInformation(int argc, char* argv[]) = 0;

	/**
	 * @brief    初始化相机
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    void
	 * @return   bool::false-程序错误 true-显示正确
	 */
	virtual bool initCameraData() = 0;

	/**
	 * @brief    开始抓取照片
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    void
	 * @return   bool::false-程序错误 true-显示正确
	 */
	virtual bool beginGrabFrames() = 0;

	/**
	 * @brief    给对象返回一张抓取的照片
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    void
	 * @return   uint16_t * 照片地址
	 */
	virtual uint16_t* returnCapturedImage() = 0;

	/**
	 * @brief    外部获取相机运行状态的方法
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    void
	 * @return   CameraStatus
	 */
	CameraStatus getCamStatus();

	/**
	 * @brief    获取判断当前指针是否为空的方法
	 * @author   yangshuhao
	 * @date     2024/9/3
	 * @param    void
	 * @return   true 当前实例存在  false实例不存在
	 */
	bool isNull();

protected:
	uint16_t*    imageData;       //拍摄得到的图片 16bit原始图像
	uint32_t     exposureTime;    //相机的曝光时间
	uint64_t     frameNum;        //拍摄帧数
	uint64_t     imageSize;       //16位深图像内存大小

	CameraStatus camOperaStatus;  //相机运行状态
};
typedef std::shared_ptr<CameraBase> CameraBasePtr;