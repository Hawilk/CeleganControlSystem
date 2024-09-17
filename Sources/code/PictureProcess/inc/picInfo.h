/*
 *@file     picInfo.h
 *@brief    图像处理后信息量
 *@author   yangshuhao
 *@date     2024/9/11
 *@remarks
 *@version  1.1
 */

#pragma once
#include <vector>
#include <stdint.h>
#include <memory>
#include <opencv2/opencv.hpp>

class picInfo
{
public:
	std::vector<cv::Point> contour;         //线虫轮廓
	std::vector<cv::Point> left_contour;    //左半轮廓
	std::vector<cv::Point> right_contour;   //右半轮廓
	std::vector<cv::Point> centerLine;      //中心线

	cv::Point curHead;      //当前线虫头位置
	cv::Point curTail;      //当前线虫尾位置
	cv::Point prevHead;     //上一帧线虫头位置
	cv::Point prevTail;     //上一帧线虫尾位置

	uint32_t  headIndex;    
	uint32_t  tailIndex;

	cv::Point nematode_center;     //线虫中心
	uint32_t  timestamp;           //帧数时间戳

	bool      DataStatus;    //计算数据是否完整

public:
	picInfo();

	void DataIntegrityCheck();   //数据合法性检验
};
typedef std::shared_ptr<picInfo> picInfoPtr;