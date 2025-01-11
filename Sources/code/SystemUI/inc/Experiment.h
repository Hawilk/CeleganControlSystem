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
#include "NematodeProcess.h"

typedef struct OriginInfo
{
	uint32_t frameNum;
	uint32_t timeStamp;
}originInfo;

class Experiment
{
	/*************** ���ⲿ�ӿ� ****************/
public:
	Experiment();
	Experiment(int argc, char* argv[]);
	~Experiment();

	//�๦���������
	void AutoDo();

	//ȷ���豸���Ƿ�����
	bool checkDeviceStatus();

	/*
	* ���̼�ģ�鹦��
	*/
	void setLedPercent(uint32_t value);     //���ù�ǿ
	void setLedSwitch();                    //���Ŵ�����

	/*
	* ͼ����ģ�鹦��
	*/
	cv::Mat getCurImage();                  //��ȡ��ǰͼ��
	cv::Mat getCurImageWithInfo();		    //��ȡ��ǰͼ�񣨴�������Ϣ��
	cv::Mat getCurPrcImage();				//��ȡ�Ѵ���ͼ��
	cv::Mat getCurPrcImageWithIndicate();   //��ȡ�Ѵ���ͼ�񣨴�������Ϣ��
	uint32_t getCurFrame();					//��ȡ��ǰ֡��
	uint32_t getCurFPS();					//��ȡ��ǰ֡��
	void setMask(MaskType m_type);			//������Ĥ
	void setRadius(uint32_t radius);		//���ð뾶
	void setCenterLine(uint32_t centerline);//����������
	void setBinThresh(uint32_t thresh);		//���ö�ֵ����ֵ
	void setDenoise(uint32_t param);		//����ȥ�����
	void beginProcess();					//��ʼͼ����
	void endProcess();						//����ͼ����
	void contrastImage();					//��ǿ�Աȶ�

	/*
	* �洢ģ�鹦��
	*/

	/*
	* λ��̨����ģ�鹦��
	*/

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

	//�������ͼƬ(����Ϣ�������Ӧ���̣߳���������Ӧ���ź���
	void pushImageWithInfoToThread(std::pair<cv::Mat, originInfo> imageWithInfo, std::mutex& mtx, std::deque<std::pair<cv::Mat, originInfo>>& images, std::condition_variable& cond);

	//���ݵ㼯��ͼƬ�Ͻ������
	void signalImageByPoints(cv::Mat& image, std::vector<cv::Point>& pts, int color);

public:
	/*-------------- �������� ----------------*/
	void pvcamTest();
	bool handleKey(int& key);
	void picProcessTest();

	/************** ���ڲ���Ա���� *************/
private:
	std::deque<std::pair<cv::Mat, originInfo>>  originImages;   //ԭʼͼ�����
	std::deque<cv::Mat>  unprocessedImages;  //δ�����ͼ�� -- PS���ö����ڵ�ǰ�汾ֻȡ�ö�β��ͼ��Ҳ�������������һ֡ͼ�񡣳��ڴ���ͼ����ٶ�ԶԶС������ͼ����ٶȣ����������Ƕ�ÿһ֡ͼ����д������Բ����̳߳ضԸö��н����Ż�����
	std::deque<std::pair<cv::Mat, picInfoPtr>> processedImages;    //�����ͼ��

	CameraBasePtr  m_Cam;           //Moment���
	StageBasePtr   m_Stage;         //Pwsλ��̨
	NematodeProcessPtr m_np;        //ͼ����ģ��
	std::thread    m_CamThread;     //�����߳�
	std::thread    m_StageThread;   //λ��̨�߳�
	std::thread    m_ProcessThread; //ͼ�����߳�
	std::atomic<bool>  cam_threadActive;     //����߳�״̬
	std::atomic<bool>  stage_threadActive;   //λ��̨�߳�״̬ 
	std::atomic<bool>  process_threadActive; //ͼ�����߳�״̬
	std::mutex     originImage_mtx;          //ԭʼͼƬ����
	std::mutex     unprocessedImage_mtx;     //������ͼƬ����
	std::mutex     processedImage_mtx;       //�Ѵ���ͼƬ����

	std::condition_variable cond_origin;      //ԭʼͼ���ź���
	std::condition_variable cond_unprocessed; //δ����ͼ���ź���
	std::condition_variable cond_processed;   //ͼ��������ź���

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