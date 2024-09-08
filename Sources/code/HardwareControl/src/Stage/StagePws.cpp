#include "StagePws.h"
#include <thread>

StagePws::StagePws(int com)
{
	portNum = com;
	handle = InitCom(portNum);

	Pos = std::make_pair(0, 0);
	axisVelocity = std::make_pair(static_cast <float>(10), static_cast <float>(10));
	axisAcceleration = std::make_pair(static_cast <float>(100), static_cast <float>(100));

	m_Status = StageStatus::Initializing;

	if (!InitStage(handle, axisX, new float[3]{ 10000, 10, 0.01f }) ||
		!InitStage(handle, axisY, new float[3]{ 10000, 10, 0.01f }))
	{//位移台的该语句即使初始化失败也不会触发 - 位移台自身缺陷
		std::cout << "init failed" << std::endl;
	}

	setStageVelocity(axisVelocity);
	setStageAcceleration(axisAcceleration);
}

StagePws::~StagePws()
{
	UnInitStage(handle, axisX);
	UnInitStage(handle, axisY);

	UnInitCom(portNum);
}

void StagePws::AutoDo(std::pair<double, double>& disp)
{
	InitCoordinates();
	moveStageAxisXandY(disp);
	waitStageMove();

	//Bug - 此处设为原点会导致外部无法查询位移台实际准确状态
	//setPointZero();

	m_Status = StageStatus::Normal;
}

void StagePws::InitCoordinates()
{
	HomeNew(handle, axisX);
	HomeNew(handle, axisY);
	waitStageMove();

	getPos();
	std::cout << Pos.first << " : " << Pos.second << std::endl;
}

void StagePws::moveStageByDirection(Direction dir, double& disp)
{
	int axis = axisX;
	double displacement = 0;

	switch (dir)
	{
	case Direction::Up :
	{
		displacement = disp;
		axis = axisY;
		break;
	}
	case Direction::Down:
	{
		displacement = 0 - disp;
		axis = axisY;
		break;
	}
	case Direction::Left:
	{
		displacement = 0 - disp;
		axis = axisX;
		break;
	}
	case Direction::Right:
	{
		displacement = disp;
		axis = axisX;
		break;
	}
	default:
		break;
	}

	MoveRelativeWait(handle, displacement, axis);
}

void StagePws::moveStageAxisXandY(std::pair<double, double>& disp)
{
	MoveRelative(handle, disp.first, axisX);
	MoveRelative(handle, disp.second, axisY);
}

void StagePws::setStageVelocity(std::pair<float, float>& vel)
{
	SpeedSet(handle, vel.first, axisX);
	SpeedSet(handle, vel.second, axisY);
}

void StagePws::setStageAcceleration(std::pair<float, float>& acc)
{
	AcDecSet(handle, acc.first, axisX);
	AcDecSet(handle, acc.second, axisY);
}

void StagePws::getPos()
{
	double pos_x, pos_y;

	if (!GetPosition(handle, axisX, &pos_x) ||
		!GetPosition(handle, axisY, &pos_y))
	{

	}
	
	Pos = std::make_pair(pos_x, pos_y);
}

std::pair<double, double> StagePws::getStagePosition()
{
	getPos();
	return this->Pos;
}

StageStatus StagePws::getStageStatus()
{
	return this->m_Status;
}

void StagePws::waitStageMove()
{
	bool status_x, status_y;
	while (true)
	{
		auto res_x = GetStation(handle, axisX, &status_x);
		auto res_y = GetStation(handle, axisY, &status_y);
		if (res_x && res_y && !status_x && !status_y)
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void StagePws::setPointZero()
{
	SetPosition(handle, 0, axisX);
	SetPosition(handle, 0, axisY);
}
