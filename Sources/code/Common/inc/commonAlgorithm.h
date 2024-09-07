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
#include "const_def.h"

class commonAlgorithm
{
public:
	/**
	 * @brief    ��16λ��ͼ����ͼ��Ҷ�ֵ�ֲ�ӳ�䵽8λ��ͼ����
	 * @author   yangshuhao
	 * @date     2024/9/7
	 * @param    uint8_t* dst- Ŀ��ͼ��uint16_t* image-�������ͼ��
	 */
	void histogramEqualization(uint8_t* dst, uint16_t* image, std::pair<uint16_t, uint16_t>& extrema);

	/**
	 * @brief    �ҵ�16λ��ͼ����������С����ֵ
	 * @author   yangshuhao
	 * @date     2024/9/7
	 * @param    uint16_t* image-�������ͼ��
	 * @return   pair first-��Сֵ��second-���ֵ
	 */
	std::pair<uint16_t, uint16_t> findExtremaInImage(const uint16_t* image);
};