/*
 *@file     Experiment.h
 *@brief    ����ϵͳʵ����
 *@author   yangshuhao
 *@date     2024/8/31
 *@remarks
 *@version  1.1
 */

#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "hello.h"
#include "CameraBase.h"
#include "CameraMoment.h"

class Experiment
{
public:
	Experiment();
	Experiment(int argc, char* argv[]);
	~Experiment();

	void pvcamTest(int argc, char* argv[]);
	void CamErrOccr(CameraStatus status);

private:
	CameraBase*  m_Cam;         //Moment���
	std::thread  m_CamThread;   //�����̣߳�����ͼ��
};