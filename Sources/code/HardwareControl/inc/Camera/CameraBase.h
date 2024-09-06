/*
 *@file     CameraBase.h
 *@brief    �������
 *@author   yangshuhao
 *@date     2024/9/1
 *@remarks
 *@version  1.1
 */

#pragma once
#include "const_def.h"
#include <stdint.h>

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	/**
	 * @brief    �Զ������й���
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    int argc, char** argv
	 */
	virtual bool AutoDo(int argc, char* argv[]) = 0;

	/**
	 * @brief    ��ʾ�����Ϣ
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    int argc, char** argv
	 * @return   bool::false-������� true-��ʾ��ȷ
	 */
	virtual bool showCameraInformation(int argc, char* argv[]) = 0;

	/**
	 * @brief    ��ʼ�����
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    void
	 * @return   bool::false-������� true-��ʾ��ȷ
	 */
	virtual bool initCameraData() = 0;

	/**
	 * @brief    ��ʼץȡ��Ƭ
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    void
	 * @return   bool::false-������� true-��ʾ��ȷ
	 */
	virtual bool beginGrabFrames() = 0;

	/**
	 * @brief    �����󷵻�һ��ץȡ����Ƭ
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    void
	 * @return   uint16_t * ��Ƭ��ַ
	 */
	virtual uint16_t* returnCapturedImage() = 0;

	/**
	 * @brief    �ⲿ��ȡ�������״̬�ķ���
	 * @author   yangshuhao
	 * @date     2024/9/1
	 * @param    void
	 * @return   CameraStatus
	 */
	CameraStatus getCamStatus();

	/**
	 * @brief    ��ȡ�жϵ�ǰָ���Ƿ�Ϊ�յķ���
	 * @author   yangshuhao
	 * @date     2024/9/3
	 * @param    void
	 * @return   true ��ǰʵ������  falseʵ��������
	 */
	bool isNull();

protected:
	uint16_t*    imageData;       //����õ���ͼƬ 16bitԭʼͼ��
	uint32_t     exposureTime;    //������ع�ʱ��
	uint64_t     frameNum;        //����֡��

	CameraStatus camOperaStatus;  //�������״̬
};