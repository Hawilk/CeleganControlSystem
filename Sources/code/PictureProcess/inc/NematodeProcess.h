/*
 *@file     NematodeProcess.h
 *@brief    图像处理类
 *@author   yangshuhao
 *@date     2024/9/11
 *@remarks
 *@version  1.1
 */

#pragma once
#include <opencv2/opencv.hpp>
#include <memory>
#include <stdint.h>
#include <chrono>
#include <ctime>

#include "const_def.h"
#include "picInfo.h"

class NematodeProcess
{
	/*************** 类外部接口 ****************/
public:
	NematodeProcess();
	~NematodeProcess();

	//自动化处理过程
	picInfoPtr AutoDo(cv::Mat& originImage);

	/****************** Mask *****************/
	//生成圆形掩膜
	void createCircleMask(uint32_t& radius, uint32_t width, uint32_t height);

	//生成矩形掩膜
	void createRectangleMask(uint32_t& halfHeight, uint32_t centerVerti, uint32_t width, uint32_t height);

	/************** 外部测试接口 ***************/
	cv::Mat getMask();
	void setBinThresh(uint32_t thresh);  //设置二值化阈值
	void setKernelSize(uint32_t size);   //设置膨胀腐蚀核
	void setSegmentedNum(uint32_t num);  //设置重采样点数

	/*************** 类内部实现 ****************/
private:
	void InitPanelParam();      //加载控制面板参数
	void SavePanelParam();      //保存控制面板参数

	void CopyImageByMask(cv::Mat& image);           //根据mask复制图像
	void ImageDenosingBinary();                     //图像去噪并二值化
	bool FindLongestBoundary(picInfoPtr& context);  //定位线虫轮廓
	bool FindHeadTail(picInfoPtr& context);         //定位线虫头和尾
	bool FindCenterLine(picInfoPtr& context);       //找到线虫中心线
	void FindCenterOfWorm(picInfoPtr& context);     //找到线虫跟踪中心

private:
	/***************** Common ****************/
	//保存当前mask参数
	void saveCurMaskParam(MaskType maskType, uint32_t& radius, uint32_t centerVerti);

	uint32_t PointDot(const cv::Point& VecA, const cv::Point& VecB);     //点积
	uint32_t PointCross(const cv::Point& VecA, const cv::Point& VecB);     //叉积
	float dist(const cv::Point& a, const cv::Point& b); //计算两点之间的距离
	int DistBetPtsOnCircBound(const int& PtsOnBound, const int& IndexA, const int& IndexB);
	void InsertPartBoundary(std::vector<cv::Point>& boundA, std::vector<cv::Point>& boundB, std::vector<cv::Point>& boundary, int headIndex, int tailIndex);       //将轮廓分为上下两部分
	void resampleBoundaryByNum(std::vector<cv::Point>& origin, std::vector<cv::Point>& dst, int num);  //根据曲线点集数量进行重采样
	void resampleBoundary(std::vector<cv::Point>& newBoundA, std::vector<cv::Point>& newBoundB, std::vector<cv::Point>& originBoundA, std::vector<cv::Point>& originBoundB, int& num);  //根据轮廓按照点数少的半边进行重采样
	void findCenterLineByBoundary(const std::vector<cv::Point>& boundA, const std::vector<cv::Point>& boundB, std::vector<cv::Point>& centerLine);   //根据轮廓找到线虫的中心线 boundA.size() == boundB.size()
	void ConvolveInt1D(const std::vector<int>& src, std::vector<int>& dst, const std::vector<int>& kernel, int klength, int normfactor);
	void ConvolveCvPtSeq(const std::vector<cv::Point>& src, std::vector<cv::Point>& dst, const std::vector<int>& kernel, int klength, int normfactor);   //对点集进行卷积操作
	void CreateGaussianKernel(double sigma, std::vector<int>& kernel, int& normfactor);  //生成高斯核
	std::vector<cv::Point> smoothCenterLine(const std::vector<cv::Point>& src, double sigma);  //对线虫中心线进行平滑处理
	void resampleSeqConstPtsPerArcLength(const std::vector<cv::Point>& sequence, std::vector<cv::Point>& resampledSeq, int numSegments);   //对中心线进行重采样

	//计算轮廓点的点积叉积
	void calcBoundaryVec(std::vector<int>& DotProds, std::vector<int>& CrossProds, std::vector<cv::Point>& boundary, uint32_t& lengthScale);

	//找到线虫尾部定位点
	void findWormTail(picInfoPtr& context, std::vector<int>& DotProds, std::vector<int>& CrossProds);

	//找到线虫头部定位点
	void findWormHead(picInfoPtr& context, std::vector<int>& DotProds, std::vector<int>& CrossProds);

private:
	cv::Mat unprocessedImage;   //待处理图像
	cv::Mat processedImage;     //已处理图像

	uint32_t gaussKernel;       //高斯核参数
	uint32_t binThresh;         //二值化阈值
	uint32_t kernelSize;        //膨胀腐蚀核阈值
	int32_t segmentedNum;       //重采样点数

	struct Mask  //图像掩膜
	{
		cv::Mat    m_mask;         //掩膜
		MaskType   m_type;         //类型

		uint32_t   m_radius;       //圆形掩膜半径或矩形半高
		uint32_t   m_centerVerti;  //垂直中心
	}mask;

	struct PtAndSum {
		int x;
		int y;
		float sum;
	};
};
typedef std::shared_ptr<NematodeProcess> NematodeProcessPtr;