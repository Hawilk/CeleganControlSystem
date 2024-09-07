/*
 *@file     StagePws.h
 *@brief    PWSλ��̨��
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

	//��λ��̨��ʼ�����ٸ���ƫ�����ƶ�
	void AutoDo(std::pair<double, double>& disp) override;

	//��ʼ��λ��̨����
	void InitCoordinates();

	//��λ��̨���ݷ�λ��ƫ�����ƶ�
	void moveStageByDirection(Direction& dir, double& disp) override;

	//��λ��̨����ƫ�����ƶ�
	void moveStageAxisXandY(std::pair<double, double>& disp) override;

	//�趨λ��̨�ٶ�
	void setStageVelocity(std::pair<float, float>& vel) override;

	//�趨λ��̨���ٶ�
	void setStageAcceleration(std::pair<float, float>& acc) override;

	//���ڲ�ʹ�û�ȡλ��̨����
	void getPos();

	//��ȡλ��̨��ǰʵ������
	std::pair<double, double> getStagePosition() override;

	//��ȡ��ǰλ��̨��ʼ��״̬
	StageStatus getStageStatus();

	//����λ��̨��״̬�����̣߳����λ��̨״̬���������ƶ��������̣߳�
	void waitStageMove();

	//����ǰλ����Ϊԭ��
	void setPointZero();

private:
	int handle;   //λ��̨���
};
typedef std::shared_ptr<StagePws> StagePwsPtr;