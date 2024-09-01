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

	/*********** ���෽����д *************/
	void AutoDo(int argc, char* argv[]) override;
	bool showCameraInformation(int argc, char* argv[]) override;
	bool initCameraData() override;
	bool beginGrabFrames() override;
	bool returnCapturedImage() override;

	/*********** Moment��ͨ�÷��� *********/
	

private:
	CameraContext* context;   //������
	std::vector<CameraContext*> contexts;  //������vec

	uns32 exposureBytes;      //�ع��ֽ�
	uns16 circBufferFrames;   //һ�λ����֡��
	int16 bufferMode;         //�ع�ģʽ
	uns32 circBufferBytes;    //һ�λ�����ֽ���
	uns8* circBufferInMemory; //ѭ��������ڴ��С
};