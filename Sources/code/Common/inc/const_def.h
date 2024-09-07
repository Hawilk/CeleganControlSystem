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

#define  CAM_ERR        false     //相机错误提示
#define  CAM_SUC        true

#define  axisX          255       //位移台坐标轴
#define  axisY          254

#define  STAGE_ERR      false     //位移台错误提示
#define  STAGE_SUC      true

#define  EXP_ERR        false     //实验错误提示
#define  EXP_SUC        true

//相机状态
enum class CameraStatus
{
	Normal,                  //正常初始化状态
	ShowInfoFailed,          //SDK信息查询状态
	InitCamFailed,           //初始化状态
	BeginGrabFrameFailed,    //开始抓取图像砖状态
	GrabFrameFailed          //抓取图像状态
};

//相机状态
enum class StageStatus
{
	Normal,                  //正常状态
	Initializing             //初始化中
};

//位移台移动的方位
enum class Direction
{
	Up,                      //上
	Down,                    //下
	Left,                    //左
	Right                    //右
};