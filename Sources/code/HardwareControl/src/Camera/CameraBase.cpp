#include "CameraBase.h"
#include <corecrt_malloc.h>
#include "const_def.h"

CameraBase::CameraBase()
{
	//��ʼ������Ա����
	this->imageData = new uint16_t[picWidth * picHeight * sizeof(uint16_t)];
	this->exposureTime = 10;
	this->frameNum = 0;
	this->camOperaStatus = CameraStatus::Normal;
}

CameraBase::~CameraBase()
{
	if (this->imageData != nullptr)
		delete this->imageData;
}

CameraStatus CameraBase::getCamStatus()
{
	return this->camOperaStatus;
}
