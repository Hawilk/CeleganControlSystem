/*
 *@file     const_def.h
 *@brief    常量定义文档
 *@author   yangshuhao
 *@date     2024/9/1
 *@remarks
 *@version  1.1
 */

#pragma once

#define  picWidth       1600      //图片宽度
#define  picHeight      1100      //图片高度
#define  picDepthBit    16        //图片位深度

#define  CAM_ERR        false     //相机出错
#define  CAM_SUC        true

//相机状态
enum class CameraStatus
{
	Normal,                  //正常初始化状态
	ShowInfoFailed,          //SDK信息查询状态
	ShowInfoSuccess,
	InitCamFailed,           //初始化状态
	InitCameSuccess,
	BeginGrabFrameFailed,    //开始抓取图像砖状态
	BeginGrabFrameSuccess,
	GrabFrameFailed,         //抓取图像状态
	GrabFrameSuccess
};