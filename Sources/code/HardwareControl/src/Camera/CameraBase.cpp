#include "CameraBase.h"
#include <corecrt_malloc.h>
#include "const_def.h"

CameraBase::CameraBase()
{
	//初始化各成员变量
	this->imageData = new uint16_t[picWidth * picHeight];
	this->exposureTime = 10;
	this->frameNum = 0;
	this->camOperaStatus = CameraStatus::Normal;
	this->imageSize = picHeight * picWidth * sizeof(uint16_t);
}

CameraBase::~CameraBase()
{
	if (this->imageData != nullptr)
		delete[] this->imageData;
}

CameraStatus CameraBase::getCamStatus()
{
	return this->camOperaStatus;
}

bool CameraBase::isNull()
{
	return this == nullptr;
}
