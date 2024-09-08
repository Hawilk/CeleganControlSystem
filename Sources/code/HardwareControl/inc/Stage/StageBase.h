/*
 *@file     StageBase.h
 *@brief    λ��̨����
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

	//��λ��̨��ʼ�����ٸ���ƫ�����ƶ�
	virtual void AutoDo(std::pair<double, double>& disp) = 0;

	//��ʼ��λ��̨����
	virtual void InitCoordinates() = 0;

	//��λ��̨���ݷ�λ��ƫ�����ƶ�
	virtual void moveStageByDirection(Direction& dir, double& disp) = 0;

	//��λ��̨����ƫ�����ƶ�
	virtual void moveStageAxisXandY(std::pair<double, double>& disp) = 0;

	//�趨λ��̨�ٶ�
	virtual void setStageVelocity(std::pair<float, float>& vel) = 0;

	//�趨λ��̨���ٶ�
	virtual void setStageAcceleration(std::pair<float, float>& acc) = 0;

	//��ȡλ��̨��ǰʵ������
	virtual std::pair<double, double> getStagePosition() = 0;

protected:
	uint32_t  portNum;     //λ��̨���Ӷ˿ں�

	std::pair<double, double>   Pos;              //λ��̨ʵ������
	std::pair<float, float>     axisVelocity;     //���ٶ�
	std::pair<float, float>     axisAcceleration; //����ٶ�

	StageStatus  m_Status;      //λ��̨׼��״̬
};
typedef std::shared_ptr<StageBase> StageBasePtr;