/*
 *@file     NematodeProcess.h
 *@brief    ͼ������
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
	/*************** ���ⲿ�ӿ� ****************/
public:
	NematodeProcess();
	~NematodeProcess();

	//�Զ����������
	picInfoPtr AutoDo(cv::Mat& originImage);

	/****************** Mask *****************/
	//����Բ����Ĥ
	void createCircleMask(uint32_t& radius, uint32_t width, uint32_t height);

	//���ɾ�����Ĥ
	void createRectangleMask(uint32_t& halfHeight, uint32_t centerVerti, uint32_t width, uint32_t height);

	/************** �ⲿ���Խӿ� ***************/
	cv::Mat getMask();
	void setBinThresh(uint32_t thresh);  //���ö�ֵ����ֵ
	void setKernelSize(uint32_t size);   //�������͸�ʴ��
	void setSegmentedNum(uint32_t num);  //�����ز�������

	/*************** ���ڲ�ʵ�� ****************/
private:
	void InitPanelParam();      //���ؿ���������
	void SavePanelParam();      //�������������

	void CopyImageByMask(cv::Mat& image);           //����mask����ͼ��
	void ImageDenosingBinary();                     //ͼ��ȥ�벢��ֵ��
	bool FindLongestBoundary(picInfoPtr& context);  //��λ�߳�����
	bool FindHeadTail(picInfoPtr& context);         //��λ�߳�ͷ��β
	bool FindCenterLine(picInfoPtr& context);       //�ҵ��߳�������
	void FindCenterOfWorm(picInfoPtr& context);     //�ҵ��߳��������

private:
	/***************** Common ****************/
	//���浱ǰmask����
	void saveCurMaskParam(MaskType maskType, uint32_t& radius, uint32_t centerVerti);

	uint32_t PointDot(const cv::Point& VecA, const cv::Point& VecB);     //���
	uint32_t PointCross(const cv::Point& VecA, const cv::Point& VecB);     //���
	float dist(const cv::Point& a, const cv::Point& b); //��������֮��ľ���
	int DistBetPtsOnCircBound(const int& PtsOnBound, const int& IndexA, const int& IndexB);
	void InsertPartBoundary(std::vector<cv::Point>& boundA, std::vector<cv::Point>& boundB, std::vector<cv::Point>& boundary, int headIndex, int tailIndex);       //��������Ϊ����������
	void resampleBoundaryByNum(std::vector<cv::Point>& origin, std::vector<cv::Point>& dst, int num);  //�������ߵ㼯���������ز���
	void resampleBoundary(std::vector<cv::Point>& newBoundA, std::vector<cv::Point>& newBoundB, std::vector<cv::Point>& originBoundA, std::vector<cv::Point>& originBoundB, int& num);  //�����������յ����ٵİ�߽����ز���
	void findCenterLineByBoundary(const std::vector<cv::Point>& boundA, const std::vector<cv::Point>& boundB, std::vector<cv::Point>& centerLine);   //���������ҵ��߳�������� boundA.size() == boundB.size()
	void ConvolveInt1D(const std::vector<int>& src, std::vector<int>& dst, const std::vector<int>& kernel, int klength, int normfactor);
	void ConvolveCvPtSeq(const std::vector<cv::Point>& src, std::vector<cv::Point>& dst, const std::vector<int>& kernel, int klength, int normfactor);   //�Ե㼯���о������
	void CreateGaussianKernel(double sigma, std::vector<int>& kernel, int& normfactor);  //���ɸ�˹��
	std::vector<cv::Point> smoothCenterLine(const std::vector<cv::Point>& src, double sigma);  //���߳������߽���ƽ������
	void resampleSeqConstPtsPerArcLength(const std::vector<cv::Point>& sequence, std::vector<cv::Point>& resampledSeq, int numSegments);   //�������߽����ز���

	//����������ĵ�����
	void calcBoundaryVec(std::vector<int>& DotProds, std::vector<int>& CrossProds, std::vector<cv::Point>& boundary, uint32_t& lengthScale);

	//�ҵ��߳�β����λ��
	void findWormTail(picInfoPtr& context, std::vector<int>& DotProds, std::vector<int>& CrossProds);

	//�ҵ��߳�ͷ����λ��
	void findWormHead(picInfoPtr& context, std::vector<int>& DotProds, std::vector<int>& CrossProds);

private:
	cv::Mat unprocessedImage;   //������ͼ��
	cv::Mat processedImage;     //�Ѵ���ͼ��

	uint32_t gaussKernel;       //��˹�˲���
	uint32_t binThresh;         //��ֵ����ֵ
	uint32_t kernelSize;        //���͸�ʴ����ֵ
	int32_t segmentedNum;       //�ز�������

	struct Mask  //ͼ����Ĥ
	{
		cv::Mat    m_mask;         //��Ĥ
		MaskType   m_type;         //����

		uint32_t   m_radius;       //Բ����Ĥ�뾶����ΰ��
		uint32_t   m_centerVerti;  //��ֱ����
	}mask;

	struct PtAndSum {
		int x;
		int y;
		float sum;
	};
};
typedef std::shared_ptr<NematodeProcess> NematodeProcessPtr;