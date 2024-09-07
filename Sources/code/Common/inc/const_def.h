/*
 *@file     const_def.h
 *@brief    ���������ĵ�
 *@author   yangshuhao
 *@date     2024/9/1
 *@remarks
 *@version  1.1
 */

#pragma once

#define  picWidth       1600      //ͼƬ���
#define  picHeight      1100      //ͼƬ�߶�
#define  picDepthBit    16        //ͼƬλ���

#define  CAM_ERR        false     //���������ʾ
#define  CAM_SUC        true

#define  axisX          255       //λ��̨������
#define  axisY          254

#define  STAGE_ERR      false     //λ��̨������ʾ
#define  STAGE_SUC      true

#define  EXP_ERR        false     //ʵ�������ʾ
#define  EXP_SUC        true

//���״̬
enum class CameraStatus
{
	Normal,                  //������ʼ��״̬
	ShowInfoFailed,          //SDK��Ϣ��ѯ״̬
	InitCamFailed,           //��ʼ��״̬
	BeginGrabFrameFailed,    //��ʼץȡͼ��ש״̬
	GrabFrameFailed          //ץȡͼ��״̬
};

//���״̬
enum class StageStatus
{
	Normal,                  //����״̬
	Initializing             //��ʼ����
};

//λ��̨�ƶ��ķ�λ
enum class Direction
{
	Up,                      //��
	Down,                    //��
	Left,                    //��
	Right                    //��
};