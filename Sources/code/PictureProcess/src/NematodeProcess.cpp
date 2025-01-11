#include "NematodeProcess.h"
#include "Parameters.h"
#include "commonAlgorithm.h"
#include <cmath>
#include <algorithm>

NematodeProcess::NematodeProcess()
{
	InitPanelParam();
}

NematodeProcess::~NematodeProcess()
{
	//SavePanelParam();
}

picInfoPtr NematodeProcess::AutoDo(cv::Mat& originImage)
{
	picInfoPtr context = std::make_shared<picInfo>();
	
	CopyImageByMask(originImage);
	ImageDenosingBinary();
	if (!FindLongestBoundary(context))
	{
		return context;
	}
	if (!FindHeadTail(context))
	{
		return context;
	}
	if (!FindCenterLine(context))
	{
		return context;
	}
	FindCenterOfWorm(context);

	context->timestamp = commonAlgorithm::getCurTimeStamp();
	context->DataIntegrityCheck();
	return context;
}

void NematodeProcess::createCircleMask(uint32_t& radius, uint32_t width, uint32_t height)
{
	if (MaskType::Circle == mask.m_type && radius == mask.m_radius)
		return;

	mask.m_mask = cv::Mat::zeros(height, width, CV_8UC1);
	cv::Point center(width / 2, height / 2);
	cv::circle(mask.m_mask, center, radius, cv::Scalar(255), -1);

	saveCurMaskParam(MaskType::Circle, radius, height / 2);
}

void NematodeProcess::createRectangleMask(uint32_t& halfHeight, uint32_t centerVerti, uint32_t width, uint32_t height)
{
	if (MaskType::Rectangle == mask.m_type && halfHeight == mask.m_radius && centerVerti == mask.m_centerVerti)
		return;

	auto top = centerVerti - halfHeight;
	auto bottom = centerVerti + halfHeight;

	top = top > 0 ? top : 0;
	bottom = bottom < height ? bottom : height;

	cv::Point top_left(0, top);
	cv::Point bottom_right(width, bottom);

	mask.m_mask = cv::Mat::zeros(height, width, CV_8UC1);
	cv::rectangle(mask.m_mask, top_left, bottom_right, cv::Scalar(255), -1);

	saveCurMaskParam(MaskType::Rectangle, halfHeight, centerVerti);
}

cv::Mat NematodeProcess::getMask()
{
	return this->mask.m_mask;
}

void NematodeProcess::setBinThresh(uint32_t thresh)
{
	this->binThresh = thresh;
}

void NematodeProcess::setKernelSize(uint32_t size)
{
	this->kernelSize = size;
}

void NematodeProcess::setSegmentedNum(uint32_t num)
{
	this->segmentedNum = num;
}

void NematodeProcess::InitPanelParam()
{
	auto Data = Parameters::getInstance()->getParam();

	for (const auto& item : Data)
	{
		if (item.first == "MaskType")
		{
			auto temp = std::stoi(item.second);
			if (0 == temp)
			{
				mask.m_type = MaskType::Rectangle;
			}
			else if (1 == temp)
			{
				mask.m_type = MaskType::Circle;
			}
		}
		else if (item.first == "MaskRadius")
		{
			mask.m_radius = std::stoi(item.second);
		}
		else if (item.first == "MaskCenterVerti")
		{
			mask.m_centerVerti = std::stoi(item.second);
		}
		else if (item.first == "GaussKernel")
		{
			gaussKernel = std::stoi(item.second);
		}
		else if (item.first == "BinThresh")
		{
			binThresh = std::stoi(item.second);
		}
		else if (item.first == "KernelSize")
		{
			kernelSize = std::stoi(item.second);
		}
		else if (item.first == "SegmentedNum")
		{
			segmentedNum = std::stoi(item.second);
		}
	}
}

void NematodeProcess::SavePanelParam()
{
	auto item = Parameters::getInstance();
	item->set("MaskType", std::to_string(static_cast<int>(MaskType::Rectangle)));
	item->set("MaskRadius", std::to_string(mask.m_radius));
	item->set("MaskCenterVerti", std::to_string(mask.m_centerVerti));
	item->set("GaussKernel", std::to_string(gaussKernel));
	item->set("BinThresh", std::to_string(binThresh));
	item->set("KernelSize", std::to_string(kernelSize));
	item->set("SegmentedNum", std::to_string(segmentedNum));

	item->saveData();
}

void NematodeProcess::CopyImageByMask(cv::Mat& image)
{
	//给未处理的图像上掩膜
	unprocessedImage = cv::Mat::zeros(image.size(), image.type());
	image.copyTo(unprocessedImage, mask.m_mask);
}

void NematodeProcess::ImageDenosingBinary()
{
	//1. 高斯去噪  --  Bug : 消耗大量时间进行去噪
	//cv::GaussianBlur(unprocessedImage, unprocessedImage, cv::Size(gaussKernel, gaussKernel), 0);

	//2. 二值化处理
	cv::threshold(unprocessedImage, unprocessedImage, binThresh, 255, cv::THRESH_BINARY);
	
	//3. 膨胀和腐蚀操作
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernelSize, kernelSize));
	cv::dilate(unprocessedImage, unprocessedImage, element);
	cv::erode(unprocessedImage, processedImage, element);
}

bool NematodeProcess::FindLongestBoundary(picInfoPtr& context)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(processedImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

	if (contours.empty())
		return false;

	// 查找点数最多的轮廓
	int maxContourIndex = -1;
	size_t maxContourSize = 0;
	for (size_t i = 0; i < contours.size(); ++i) {
		if (contours[i].size() > maxContourSize) {
			maxContourSize = contours[i].size();
			maxContourIndex = static_cast<int>(i);
		}
	}
	if (maxContourSize < 200)  //如果最大轮廓点集少于100，不进行后续处理流程
	{
		return false;
	}

	context->contour = contours[maxContourIndex];
	return true;
}

bool NematodeProcess::FindHeadTail(picInfoPtr& context)
{
	auto& boundary = context->contour;
	std::vector<int> DotProds, CrossProds;
	uint32_t lengthScale = 5;    //组成向量的间隔点

	calcBoundaryVec(DotProds, CrossProds, boundary, lengthScale);
	findWormTail(context, DotProds, CrossProds);
	findWormHead(context, DotProds, CrossProds);

	return true;
}

bool NematodeProcess::FindCenterLine(picInfoPtr& context)
{
	std::vector<cv::Point> originBoundA, originBoundB;
	InsertPartBoundary(originBoundA, originBoundB, context->contour, context->headIndex, context->tailIndex);

	int Numsegments = segmentedNum;    //该参数后续处理需要移至函数外部
	if (originBoundB.size() < Numsegments || originBoundA.size() < Numsegments)
	{
		return false;
	}

	std::reverse(originBoundB.begin(), originBoundB.end());

	resampleBoundary(context->left_contour, context->right_contour, originBoundA, originBoundB, Numsegments);
	findCenterLineByBoundary(context->left_contour, context->right_contour, context->centerLine);
	return true;
}

void NematodeProcess::FindCenterOfWorm(picInfoPtr& context)
{
	auto& centerLine = context->centerLine;
	std::vector<cv::Point> SmoothUnresampledCenterline = smoothCenterLine(centerLine, 0.5 * centerLine.size() / segmentedNum);

	resampleSeqConstPtsPerArcLength(SmoothUnresampledCenterline, context->centerLine, segmentedNum);
	context->nematode_center = context->centerLine.at(segmentedNum / 2);
}

void NematodeProcess::saveCurMaskParam(MaskType maskType, uint32_t& radius, uint32_t centerVerti)
{
	this->mask.m_type = maskType;
	this->mask.m_radius = radius;
	this->mask.m_centerVerti = centerVerti;
}

uint32_t NematodeProcess::PointDot(const cv::Point& VecA, const cv::Point& VecB)
{
	return (VecA.x) * (VecB.x) + (VecA.y) * (VecB.y);
}

uint32_t NematodeProcess::PointCross(const cv::Point& VecA, const cv::Point& VecB)
{
	return (VecA.x) * (VecB.y) - (VecA.y) * (VecB.x);
}

float NematodeProcess::dist(const cv::Point& a, const cv::Point& b)
{
	return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int NematodeProcess::DistBetPtsOnCircBound(const int& PtsOnBound, const int& IndexA, const int& IndexB)
{
	int directDistance = std::abs(IndexA - IndexB);
	int circularDistance = PtsOnBound - directDistance;

	// 返回较小的距离
	return std::min(directDistance, circularDistance);
}

void NematodeProcess::InsertPartBoundary(std::vector<cv::Point>& boundA, std::vector<cv::Point>& boundB, std::vector<cv::Point>& boundary, int headIndex, int tailIndex)
{
	if (headIndex < tailIndex) {
		boundA.insert(boundA.end(), boundary.begin() + headIndex, boundary.begin() + tailIndex);
		boundB.insert(boundB.end(), boundary.begin() + tailIndex, boundary.end());
		boundB.insert(boundB.end(), boundary.begin(), boundary.begin() + headIndex);
	}
	else {
		boundB.insert(boundB.end(), boundary.begin() + tailIndex, boundary.begin() + headIndex);
		boundA.insert(boundA.end(), boundary.begin() + headIndex, boundary.end());
		boundA.insert(boundA.end(), boundary.begin(), boundary.begin() + tailIndex);
	}
}

void NematodeProcess::resampleBoundaryByNum(std::vector<cv::Point>& origin, std::vector<cv::Point>& dst, int num)
{
	float n = static_cast<float>(origin.size() - 1) / static_cast<float>(num - 1);
	dst.clear();

	for (int i = 0; i < num; i++)
	{
		int tempPos = static_cast<int>(i * n + 0.5f);

		if (tempPos < 0 || tempPos >= origin.size())
		{
			continue;
		}

		dst.push_back(origin[tempPos]);
	}
}

void NematodeProcess::resampleBoundary(std::vector<cv::Point>& newBoundA, std::vector<cv::Point>& newBoundB, std::vector<cv::Point>& originBoundA, std::vector<cv::Point>& originBoundB, int& num)
{
	if (originBoundA.size() > originBoundB.size())
	{
		resampleBoundaryByNum(originBoundA, newBoundA, originBoundB.size());
		newBoundB = originBoundB;
	}
	else
	{
		resampleBoundaryByNum(originBoundB, newBoundB, originBoundA.size());
		newBoundA = originBoundA;
	}
}

void NematodeProcess::findCenterLineByBoundary(const std::vector<cv::Point>& boundA, const std::vector<cv::Point>& boundB, std::vector<cv::Point>& centerLine)
{
	for (size_t i = 0; i < boundA.size(); i++)
	{
		const cv::Point& sideA = boundA.at(i);
		const cv::Point& sideB = boundB.at(i);

		cv::Point midPt((sideA.x + sideB.x) / 2, (sideA.y + sideB.y) / 2);

		centerLine.push_back(midPt);
	}
}

void NematodeProcess::ConvolveInt1D(const std::vector<int>& src, std::vector<int>& dst, const std::vector<int>& kernel, int klength, int normfactor)
{
	int length = src.size();
	int anchor = klength / 2;

	dst.clear();
	dst.resize(length);

	for (int j = 0; j < length; j++) {
		int sum = 0;
		for (int k = 0; k < klength; k++) {
			int ind = j + k - anchor;
			// 边界处理
			ind = std::max(0, std::min(ind, length - 1));
			sum += src[ind] * kernel[k];
		}
		// 归一化并四舍五入
		dst[j] = static_cast<int>(1.0 * sum / normfactor + 0.5);
	}
}

void NematodeProcess::ConvolveCvPtSeq(const std::vector<cv::Point>& src, std::vector<cv::Point>& dst, const std::vector<int>& kernel, int klength, int normfactor)
{
	int srcTotal = src.size();

	// 使用 vector 替代动态数组
	std::vector<int> x(srcTotal);
	std::vector<int> y(srcTotal);
	std::vector<int> xc(srcTotal);
	std::vector<int> yc(srcTotal);

	// 提取点的坐标
	for (int j = 0; j < srcTotal; j++) {
		x[j] = src[j].x;
		y[j] = src[j].y;
	}

	// 卷积操作
	ConvolveInt1D(x, xc, kernel, klength, normfactor);
	ConvolveInt1D(y, yc, kernel, klength, normfactor);

	// 将卷积后的结果存储在 dst 中
	dst.clear();
	for (int j = 0; j < srcTotal; j++) {
		dst.emplace_back(cv::Point(xc[j], yc[j]));
	}
}

void NematodeProcess::CreateGaussianKernel(double sigma, std::vector<int>& kernel, int& normfactor)
{
	int ll = static_cast<int>(-3 * sigma) - 1;
	int ul = static_cast<int>(3 * sigma) + 1;
	int klength = ul - ll + 1;

	kernel.resize(klength);
	normfactor = 0;

	// 生成高斯核
	double n = std::exp(-1.0 * ll * ll / (2 * sigma * sigma));
	for (int x = 0; x < klength; x++) {
		kernel[x] = static_cast<int>(std::exp(-1.0 * (x + ll) * (x + ll) / (2 * sigma * sigma)) / n + 0.5);
		normfactor += kernel[x];
	}
}

std::vector<cv::Point> NematodeProcess::smoothCenterLine(const std::vector<cv::Point>& src, double sigma)
{
	// 创建高斯核
	std::vector<int> kernel;
	int normfactor;
	CreateGaussianKernel(sigma, kernel, normfactor);

	// 卷积操作
	std::vector<cv::Point> dst;
	ConvolveCvPtSeq(src, dst, kernel, kernel.size(), normfactor);

	return dst;
}

void NematodeProcess::resampleSeqConstPtsPerArcLength(const std::vector<cv::Point>& sequence, std::vector<cv::Point>& resampledSeq, int numSegments)
{
	std::vector<PtAndSum> decimated;
	float n = static_cast<float>(sequence.size() - 1) / static_cast<float>(numSegments - 1);
	float currSum = 0.0f;

	for (int i = 0; i < numSegments; ++i) {
		int tempPos = static_cast<int>(i * n + 0.5f);
		tempPos = std::clamp(tempPos, 0, static_cast<int>(sequence.size()) - 1);
		cv::Point tempPt = sequence[tempPos];

		if (!decimated.empty()) {
			currSum += dist(tempPt, cv::Point(decimated.back().x, decimated.back().y));
		}

		decimated.push_back({ tempPt.x, tempPt.y, currSum });
	}

	int totalArcLength = currSum;
	float optimalArcLength = totalArcLength / static_cast<float>(numSegments - 1);

	resampledSeq.clear();
	int decimatedIndex = 0;
	PtAndSum* prevVertex = &decimated[0];
	PtAndSum* currVertex = nullptr;

	for (int i = 0; i < numSegments; ++i) {
		float s = i * optimalArcLength;

		while (!(s >= prevVertex->sum && (decimatedIndex + 1 < decimated.size() && s <= decimated[decimatedIndex + 1].sum))) {
			if (i == numSegments - 1) {
				prevVertex = &decimated[decimated.size() - 2];
				currVertex = &decimated.back();
				break;
			}
			prevVertex = &decimated[decimatedIndex++];
			currVertex = &decimated[decimatedIndex];
		}

		if (!currVertex) {
			currVertex = &decimated[decimatedIndex];
		}

		double distBetweenVertices = currVertex->sum - prevVertex->sum;
		double t = s - prevVertex->sum;

		cv::Point2f unitVec(0.0, 0.0);
		if (distBetweenVertices >= 1.0) {
			unitVec.x = static_cast<double>(currVertex->x - prevVertex->x) / distBetweenVertices;
			unitVec.y = static_cast<double>(currVertex->y - prevVertex->y) / distBetweenVertices;
		}

		cv::Point interpPt(
			static_cast<int>(prevVertex->x + unitVec.x * t + 0.5),
			static_cast<int>(prevVertex->y + unitVec.y * t + 0.5)
		);

		resampledSeq.push_back(interpPt);
	}
}

void NematodeProcess::calcBoundaryVec(std::vector<int>& DotProds, std::vector<int>& CrossProds, std::vector<cv::Point>& boundary, uint32_t& lengthScale)
{
	uint32_t totalPts = boundary.size();
	for (int i = 0; i < totalPts; i++)
	{
		//确定向量定位点
		int AheadPtr = (i + lengthScale) % totalPts;
		int BehindPtr = (i + lengthScale) % totalPts;

		const cv::Point& Pt = boundary.at(i);
		const cv::Point& AheadPt = boundary.at(AheadPtr);
		const cv::Point& BehindPt = boundary.at(BehindPtr);

		//计算向量
		cv::Point AheadVec = cv::Point(AheadPt.x - Pt.x, AheadPt.y - Pt.y);
		cv::Point BehindVec = cv::Point(Pt.x - BehindPt.x, Pt.y - BehindPt.y);

		// 存储点积
		int DotProdVal = PointDot(AheadVec, BehindVec);
		DotProds.push_back(DotProdVal);

		// 存储叉积
		int CrossProdVal = PointCross(AheadVec, BehindVec);
		CrossProds.push_back(CrossProdVal);
	}
}

void NematodeProcess::findWormTail(picInfoPtr& context, std::vector<int>& DotProds, std::vector<int>& CrossProds)
{
	float MostCurvy = 1000.0f;
	int MostCurvyIndex = 0;

	uint32_t totalPts = context->contour.size();
	for (int i = 0; i < totalPts; i++) {
		int DotProdVal = DotProds[i];
		int CrossProdVal = CrossProds[i];
		if (DotProdVal < MostCurvy && CrossProdVal > 0) {
			MostCurvy = static_cast<float>(DotProdVal);
			MostCurvyIndex = i;
		}
	}

	context->curTail = context->contour[MostCurvyIndex];
	context->tailIndex = MostCurvyIndex;
}

void NematodeProcess::findWormHead(picInfoPtr& context, std::vector<int>& DotProds, std::vector<int>& CrossProds)
{
	float SecondMostCurvy = 1000.0f;
	uint32_t totalPts = context->contour.size();
	int SecondMostCurvyIndex = (context->tailIndex + totalPts / 2) % totalPts;

	for (int i = 0; i < totalPts; i++) {
		int DotProdVal = DotProds[i];
		int CrossProdVal = CrossProds[i];
		int DistBetPtsOnBound = DistBetPtsOnCircBound(totalPts, i, context->tailIndex);

		// 确保距离远离尾部
		if (DistBetPtsOnBound > (totalPts / 4)) {
			if (DotProdVal < SecondMostCurvy && CrossProdVal > 0) {
				SecondMostCurvy = static_cast<float>(DotProdVal);
				SecondMostCurvyIndex = i;
			}
		}
	}

	context->curHead = context->contour[SecondMostCurvyIndex];
	context->headIndex = SecondMostCurvyIndex;
}
