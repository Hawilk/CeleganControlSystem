/*
 *@file     picInfo.h
 *@brief    ͼ�������Ϣ��
 *@author   yangshuhao
 *@date     2024/9/11
 *@remarks
 *@version  1.1
 */

#pragma once
#include <vector>
#include <stdint.h>
#include <memory>
#include <opencv2/opencv.hpp>

class picInfo
{
public:
	std::vector<cv::Point> contour;         //�߳�����
	std::vector<cv::Point> left_contour;    //�������
	std::vector<cv::Point> right_contour;   //�Ұ�����
	std::vector<cv::Point> centerLine;      //������

	cv::Point curHead;      //��ǰ�߳�ͷλ��
	cv::Point curTail;      //��ǰ�߳�βλ��
	cv::Point prevHead;     //��һ֡�߳�ͷλ��
	cv::Point prevTail;     //��һ֡�߳�βλ��

	uint32_t  headIndex;    
	uint32_t  tailIndex;

	cv::Point nematode_center;     //�߳�����
	uint32_t  timestamp;           //֡��ʱ���

	bool      DataStatus;    //���������Ƿ�����

public:
	picInfo();

	void DataIntegrityCheck();   //���ݺϷ��Լ���
};
typedef std::shared_ptr<picInfo> picInfoPtr;