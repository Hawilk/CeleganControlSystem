/*
 *@file     StageBase.h
 *@brief    位移台基类
 *@author   yangshuhao
 *@date     2024/9/1
 *@remarks
 *@version  1.1
 */

#pragma once
#include <const_def.h>
#include <stdint.h>
#include <memory>
#include <opencv2/opencv.hpp>

class StageBase
{
public:
	StageBase();
	virtual ~StageBase();

	//将位移台初始化后再根据偏移量移动
	virtual void AutoDo(std::pair<double, double>& disp) = 0;

	//初始化位移台坐标
	virtual void InitCoordinates() = 0;

	//将位移台根据方位和偏移量移动
	virtual void moveStageByDirection(Direction& dir, double& disp) = 0;

	//将位移台根据偏移量移动
	virtual void moveStageAxisXandY(std::pair<double, double>& disp) = 0;

	//设定位移台速度
	virtual void setStageVelocity(std::pair<float, float>& vel) = 0;

	//设定位移台加速度
	virtual void setStageAcceleration(std::pair<float, float>& acc) = 0;

	//获取位移台当前实际坐标
	virtual std::pair<double, double> getStagePosition() = 0;

protected:
	uint32_t  portNum;     //位移台连接端口号

	std::pair<double, double>   Pos;              //位移台实际坐标
	std::pair<float, float>     axisVelocity;     //轴速度
	std::pair<float, float>     axisAcceleration; //轴加速度

	StageStatus  m_Status;      //位移台准备状态
};
typedef std::shared_ptr<StageBase> StageBasePtr;