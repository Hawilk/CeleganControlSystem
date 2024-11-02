/*
 *@file     systemInterface.h
 *@brief    系统界面类
 *@author   yangshuhao
 *@date     2024/9/21
 *@remarks
 *@version  1.1
 */

#ifndef __SYSTEMINTERFACE_H__
#define __SYSTEMINTERFACE_H__

#pragma once
#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QSpinBox>
#include <memory>
#include <Experiment.h>
#include "const_def.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class systemInterface;
}
QT_END_NAMESPACE
typedef std::shared_ptr<Ui::systemInterface> systemInterfacePtr;

class systemInterface : public QWidget
{
	Q_OBJECT

public:
	systemInterface();
	systemInterface(int argc, char* argv[]);
	~systemInterface();

public:
	systemInterfacePtr ui;    //界面实例

protected slots:
	void on_LedSlider_valueChanged(int value);
	void on_AmpSlider_valueChanged(int value);
	void on_FreSlider_valueChanged(int value);
	void on_DutySlider_valueChanged(int value);
	void on_RadiusSlider_valueChanged(int value);
	void on_CenterLineSlider_valueChanged(int value);
	void on_BinSlider_valueChanged(int value);
	void on_DenoiseSlider_valueChanged(int value);

	void on_LedButton_clicked();        //光遗传开关
	void on_DcButton_clicked();         //直流信号开关
	void on_SwButton_clicked();		    //方波信号开关
	void on_ElecStopButton_clicked();   //电场停止开关
	void on_BeginPrcButton_clicked();   //图像处理开关
	void on_ContrastButton_clicked();   //对比度增强开关
	void on_SaveButton_clicked();	    //数据保存开关
	void on_ChgLanButton_clicked();     //语言切换开关
	void on_ConnectButton_clicked();    //远程模块连接
	void on_RemoteStopButton_clicked(); //远程停止指令
	void on_RemoteLeftButton_clicked(); //远程向左指令
	void on_RemoteRightButton_clicked();//远程向右指令
	void on_UpButton_clicked();			//位移台向上
	void on_DownButton_clicked();		//位移台向下
	void on_LeftButton_clicked();		//位移台向左
	void on_RightButton_clicked();		//位移台向右
	void on_ResetButton_clicked();		//位移信息重置
	void on_YLockButton_clicked();		//纵轴位移锁定
	void on_TrackButton_clicked();		//跟踪按钮
	void on_OpenDeviceButton_clicked();         //打开设备
	void on_OpenLogButton_clicked();            //打开日志

protected:
	void shiftButtonTimer();  //位移按键连续触发
	void deleteButtonTimer(); //释放位移按键
	void connectButtonTimer();//连接定时器
	void deleteTimer(QTimer* timer);

	void spinBoxConnect();    //连接QSpinBox信号和槽
	void setLanguage(LanguageType lanType);

protected:
	/* 用于按键的连续触发 */
	void onUpButtonPressed();
	void onUpButtonReleased();
	void onDownButtonPressed();
	void onDownButtonReleased();
	void onLeftButtonPressed();
	void onLeftButtonReleased();
	void onRightButtonPressed();
	void onRightButtonReleased();

	void onUpButtonTimeout();
	void onDownButtonTimeout();
	void onLeftButtonTimeout();
	void onRightButtonTimeout();

protected slots:
	/* 用于SpinBox的连续触发 */
	void LedSpin_valueChanged();
	void AmpSpin_valueChanged();
	void FreSpin_valueChanged();
	void DutySpin_valueChanged();
	void RadiusSpin_valueChanged();
	void CenterLineSpin_valueChanged();
	void BinSpin_valueChanged();
	void DenoiseSpin_valueChanged();
	void SpeedSpin_valueChanged();
	void AccelerationSpin_valueChanged();


protected:
	//按键联系触发定时器
	QTimer* m_upTimer;
	QTimer* m_downTimer;
	QTimer* m_leftTimer;
	QTimer* m_rightTimer;

private:
	int    interface_argc;
	char** interface_argv;
	ExperimentPtr   m_exp;

};


#endif