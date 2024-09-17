/*
 *@file     commonAlgorithm.h
 *@brief    �Զ����㷨����
 *@author   yangshuhao
 *@date     2024/9/7
 *@remarks
 *@version  1.1
 */

#include <algorithm>
#include <vector>
#include <cstdint>
#include <chrono>
#include <ctime>

#include "const_def.h"

struct curTime {
	uint32_t hour;
	uint32_t minute;
	uint32_t second;
	uint32_t millisecond;
};

class commonAlgorithm
{
public:
	/**
	 * @brief    ��16λ��ͼ����ͼ��Ҷ�ֵ�ֲ�ӳ�䵽8λ��ͼ����
	 * @author   yangshuhao
	 * @date     2024/9/7
	 * @param    uint8_t* dst- Ŀ��ͼ��uint16_t* image-�������ͼ��
	 */
	static void histogramEqualization(uint8_t* dst, uint16_t* image, std::pair<uint16_t, uint16_t>& extrema);

	/**
	 * @brief    �ҵ�16λ��ͼ����������С����ֵ
	 * @author   yangshuhao
	 * @date     2024/9/7
	 * @param    uint16_t* image-�������ͼ��
	 * @return   pair first-��Сֵ��second-���ֵ
	 */
	static std::pair<uint16_t, uint16_t> findExtremaInImage(uint16_t* image);

	/**
	 * @brief    ��ȡ��ǰ��ʱ���
	 * @author   yangshuhao
	 * @date     2024/9/16
	 * @return   uint32_t - style : hhmmssmmm
	 */
	static uint32_t getCurTimeStamp();

	/**
	 * @brief    ����ǰ��ʱ���ת��Ϊʱ����
	 * @author   yangshuhao
	 * @date     2024/9/16
	 * @param    uint32_t - style : hhmmssmmm
	 * @return   curTime
	 */
	static curTime convertTimeStamp(uint32_t timestamp);
};