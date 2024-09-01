/*
 *@file     Experiment.h
 *@brief    控制系统实验类
 *@author   yangshuhao
 *@date     2024/8/31
 *@remarks
 *@version  1.1
 */

#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "hello.h"
#include "CameraBase.h"
#include "CameraMoment.h"

class Experiment
{
public:
	Experiment();
	~Experiment();

	void print();
	void matTest();
	void pvcamTest(int argc, char* argv[]);
	void CamErrOccr(CameraStatus status);

private:

};