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
#include <atomic>
#include <chrono>
#include <thread>
#include <mutex>

#include "CameraMoment.h"
#include "StagePws.h"
#include "commonAlgorithm.h"
#include "Parameters.h"

class Experiment
{
	/*************** ���ⲿ�ӿ� ****************/
public:
	Experiment();
	Experiment(int argc, char* argv[]);
	~Experiment();

	//�๦���������
	void AutoDo();

	void pvcamTest();
	void CamErrOccr(CameraStatus status);
	void stageTest(int com);

	/*************** ���ڲ�ʵ�� ****************/
private:  
	//���ؿ���������
	void InitPanelParam();

	//�������������
	void SavePanelParam();

	//��ʼ�����
	bool InitCamera();

	//ͼ�����߳��ڲ�
	void imageProcessing();

	//�ȴ�����߳�����
	void waitCamThreadStart();

	//�ر�����߳�
	void stopCamThread();

	//��ʼ��λ��̨
	bool InitStage();

	//λ��̨�ƶ��߳��ڲ�
	void stageDisplacing();

	//�ȴ�λ��̨�߳�����
	void waitStageThreadStart();

	//�ر�λ��̨�߳�
	void stopStageThread();

	/************** ���ڲ���Ա���� *************/
private:
	cv::Mat        m_image_16bit; //�ڲ�ԭʼͼ��(16λ�
	cv::Mat        m_image_8bit;  //��ʾͼ��(8λ�

	CameraBasePtr  m_Cam;         //Moment���
	StageBasePtr   m_Stage;       //Pwsλ��̨
	std::thread    m_CamThread;   //�����̣߳�����ͼ��
	std::thread    m_StageThread; //λ��̨�߳�

	std::atomic<bool>  cam_threadActive;  //����߳�״̬
	std::atomic<bool>  stage_threadActive;//λ��̨�߳�״̬
	std::mutex     image_mtx;     //ͼƬ����

	std::map<std::string, std::string> Data; //�����ļ����� ԭʼ����

	struct PanelParam
	{
		double  initialPos_x;   //��ʼλ��
		double  initialPos_y;
	}panelParam;

	/************** ���ڲ�ϵͳ���� *************/
private:
	int     m_argc;
	char**  m_argv;
	int     m_com;     //λ��̨�˿ں�
};
typedef std::unique_ptr<Experiment> ExperimentPtr;