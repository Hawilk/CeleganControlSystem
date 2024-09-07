/*
 *@file     StagePws.h
 *@brief    PWS位移台类
 *@author   yangshuhao
 *@date     2024/9/5
 *@remarks
 *@version  1.1
 */

#pragma once
#include "StageBase.h"
#include <SLS_Dll.h>

class StagePws : public StageBase
{
public:
	StagePws(int com);
	~StagePws();

	//将位移台初始化后再根据偏移量移动
	void AutoDo(std::pair<double, double>& disp) override;

	//初始化位移台坐标
	void InitCoordinates();

	//将位移台根据方位和偏移量移动
	void moveStageByDirection(Direction& dir, double& disp) override;

	//将位移台根据偏移量移动
	void moveStageAxisXandY(std::pair<double, double>& disp) override;

	//设定位移台速度
	void setStageVelocity(std::pair<float, float>& vel) override;

	//设定位移台加速度
	void setStageAcceleration(std::pair<float, float>& acc) override;

	//类内部使用获取位移台坐标
	void getPos();

	//获取位移台当前实际坐标
	std::pair<double, double> getStagePosition() override;

	//获取当前位移台初始化状态
	StageStatus getStageStatus();

	//根据位移台的状态阻塞线程（如果位移台状态处于正在移动，阻塞线程）
	void waitStageMove();

	//将当前位置设为原点
	void setPointZero();

private:
	int handle;   //位移台句柄
};
typedef std::shared_ptr<StagePws> StagePwsPtr;