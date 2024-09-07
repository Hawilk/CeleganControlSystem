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
#include "CameraBase.h"
#include "CameraMoment.h"
#include "StagePws.h"
#include "commonAlgorithm.h"

class Experiment
{
public:
	Experiment();
	Experiment(int argc, char* argv[]);
	~Experiment();

	void AutoDo();

	//��ʼ�����
	bool InitCamera();

	//ͼ�����߳��ڲ�
	void imageProcessing();

	//��ʼ��λ��̨
	bool InitStage();

	void pvcamTest();
	void CamErrOccr(CameraStatus status);
	void stageTest(int com);

private:
	cv::Mat        m_image_16bit; //�ڲ�ԭʼͼ��(16λ�
	cv::Mat        m_image_8bit;  //��ʾͼ��(8λ�

	CameraBasePtr  m_Cam;         //Moment���
	StageBasePtr   m_Stage;       //Pwsλ��̨
	std::thread    m_CamThread;   //�����̣߳�����ͼ��
	std::thread    m_StageThread; //λ��̨�߳�

	bool  cam_threadActive;       //����߳�״̬
	bool  stage_threadActive;     //λ��̨�߳�״̬

private:
	int     m_argc;
	char**  m_argv;
};
typedef std::unique_ptr<Experiment> ExperimentPtr;