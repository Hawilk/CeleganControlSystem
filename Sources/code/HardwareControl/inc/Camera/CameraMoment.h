/*
 *@file     CameraMoment.h
 *@brief    Moment�����
 *@author   yangshuhao
 *@date     2024/9/1
 *@remarks
 *@version  1.1
 */

#pragma once
#include "CameraBase.h"
#include "Common.h"

class CameraMoment : public CameraBase
{
public:
	CameraMoment();
	~CameraMoment();

	/*************** �ⲿ��ʹ�ýӿ� ****************/

	//�Զ�������
	bool AutoDo(int argc, char* argv[]) override;

	//����һ���������Ƭ ʹ�ø��ڴ��Ƽ����
	uint16_t* returnCapturedImage() override;

private:
	//��ʾ�����Ϣ
	bool showCameraInformation(int argc, char* argv[]) override;

	//�ҵ��������ʼ�����
	bool initCameraData() override;

	//��ʼ������Ƭ����
	bool beginGrabFrames() override;

	//�������ⴥ�� ��ʱ�ع�
	void PeriodicTimerStart();

private:
	/************ Moment ����ڲ����� ****************/
	CameraContext*                context;   //������
	std::vector<CameraContext*>   contexts;  //������vec

	uns32 exposureBytes;      //�ع��ֽ�
	uns16 circBufferFrames;   //һ�λ����֡��
	int16 bufferMode;         //�ع�ģʽ
	uns32 circBufferBytes;    //һ�λ�����ֽ���
	uns8* circBufferInMemory; //ѭ��������ڴ��С
	uns32 intervalMs;         //��Ƭ���

	bool  errorOccurred;      //ץȡ��Ƭ����

private:
	bool          g_periodicTimerActive;  //����������״̬
	std::thread   g_periodicTimerThread;  //�������߳�
};