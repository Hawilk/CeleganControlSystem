#include "picInfo.h"

picInfo::picInfo()
{
	curHead = cv::Point(-1, -1);
	curTail = cv::Point(-1, -1);
	nematode_center = cv::Point(-1, -1);
	DataStatus = false;
}

void picInfo::DataIntegrityCheck()
{
	if (contour.empty() || left_contour.empty() || right_contour.empty() || centerLine.empty())
	{
		DataStatus = false;
		return;
	}

	auto temp = cv::Point(-1, -1);
	if (curHead == temp || curTail == temp || nematode_center == temp)
	{
		DataStatus = false;
		return;
	}

	DataStatus = true;
}
