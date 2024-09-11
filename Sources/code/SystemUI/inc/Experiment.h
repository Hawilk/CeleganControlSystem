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
#include <deque>
#include <condition_variable>

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

	/*************** ���ڲ�ʵ�� ****************/
private:  
	/*--------------- Ӳ������ ----------------*/
	void InitPanelParam();      //���ؿ���������
	void SavePanelParam();      //�������������

	bool InitCamera();          //��ʼ�����
	void imageCapturing();      //�����߳��ڲ�

	bool InitStage();           //��ʼ��λ��̨
	void stageDisplacing();     //λ��̨�ƶ��߳��ڲ�

	void InitProcessing();      //��ʼ��ͼ����ģ��
	void imageProcessing();     //ͼ�����߳��ڲ�

	/*---------------- Common ----------------*/
	//��ʼ���ڲ�����
	void initInternalVar(int& argc, char* argv[]);

	//�ȴ��߳�����
	void waitThreadStart(std::atomic<bool>& active, uint8_t time_ms);

	//�ȴ��߳�ֹͣ
	void stopThread(std::atomic<bool>& active, std::thread& thrd);

	//���ݴ���ԭ���ӡ����
	void CamErrOccr(CameraStatus status);

	//����Param�е�λ��̨��ʼλ��
	void resetParamInitialPos();

	//�������ͼƬ�����Ӧ���̣߳���������Ӧ���ź���
	void pushImageToThread(cv::Mat& image, std::mutex& mtx, std::deque<cv::Mat>& images, std::condition_variable& cond);

	/*-------------- �������� ----------------*/
	void pvcamTest();

	bool handleKey(int& key);

	/************** ���ڲ���Ա���� *************/
private:
	std::deque<cv::Mat>  originImages;   //ԭʼͼ�����
	std::deque<cv::Mat>  unprocessedImages;  //δ�����ͼ�� -- PS���ö����ڵ�ǰ�汾ֻȡ�ö�β��ͼ��Ҳ�������������һ֡ͼ�񡣳��ڴ���ͼ����ٶ�ԶԶС������ͼ����ٶȣ����������Ƕ�ÿһ֡ͼ����д������Բ����̳߳ضԸö��н����Ż�����

	CameraBasePtr  m_Cam;           //Moment���
	StageBasePtr   m_Stage;         //Pwsλ��̨
	std::thread    m_CamThread;     //�����߳�
	std::thread    m_StageThread;   //λ��̨�߳�
	std::thread    m_ProcessThread; //ͼ�����߳�
	std::atomic<bool>  cam_threadActive;     //����߳�״̬
	std::atomic<bool>  stage_threadActive;   //λ��̨�߳�״̬ 
	std::atomic<bool>  process_threadActive; //ͼ�����߳�״̬
	std::mutex     originImage_mtx;          //ԭʼͼƬ����
	std::mutex     unprocessedImage_mtx;     //������ͼƬ����

	std::condition_variable cond_origin;      //ԭʼͼ���ź���
	std::condition_variable cond_unprocessed; //δ����ͼ���ź���
	std::condition_variable cond_processed;   //ͼ��������ź���

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