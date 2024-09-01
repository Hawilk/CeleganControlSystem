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

#define  CAM_ERR        false     //�������
#define  CAM_SUC        true

//���״̬
enum class CameraStatus
{
	Normal,                  //������ʼ��״̬
	ShowInfoFailed,          //SDK��Ϣ��ѯ״̬
	ShowInfoSuccess,
	InitCamFailed,           //��ʼ��״̬
	InitCameSuccess,
	BeginGrabFrameFailed,    //��ʼץȡͼ��ש״̬
	BeginGrabFrameSuccess,
	GrabFrameFailed,         //ץȡͼ��״̬
	GrabFrameSuccess
};