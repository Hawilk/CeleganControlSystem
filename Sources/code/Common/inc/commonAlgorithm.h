/*
 *@file     commonAlgorithm.h
 *@brief    自定义算法函数
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
	 * @brief    将16位深图像按照图像灰度值分布映射到8位深图像上
	 * @author   yangshuhao
	 * @date     2024/9/7
	 * @param    uint8_t* dst- 目标图像，uint16_t* image-待处理的图像
	 */
	static void histogramEqualization(uint8_t* dst, uint16_t* image, std::pair<uint16_t, uint16_t>& extrema);

	/**
	 * @brief    找到16位深图像上最大和最小像素值
	 * @author   yangshuhao
	 * @date     2024/9/7
	 * @param    uint16_t* image-待处理的图像
	 * @return   pair first-最小值，second-最大值
	 */
	static std::pair<uint16_t, uint16_t> findExtremaInImage(uint16_t* image);

	/**
	 * @brief    获取当前的时间戳
	 * @author   yangshuhao
	 * @date     2024/9/16
	 * @return   uint32_t - style : hhmmssmmm
	 */
	static uint32_t getCurTimeStamp();

	/**
	 * @brief    将当前的时间戳转化为时分秒
	 * @author   yangshuhao
	 * @date     2024/9/16
	 * @param    uint32_t - style : hhmmssmmm
	 * @return   curTime
	 */
	static curTime convertTimeStamp(uint32_t timestamp);
};