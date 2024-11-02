/*
 *@file     systemInterface.h
 *@brief    ϵͳ������
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
	systemInterfacePtr ui;    //����ʵ��

protected slots:
	void on_LedSlider_valueChanged(int value);
	void on_AmpSlider_valueChanged(int value);
	void on_FreSlider_valueChanged(int value);
	void on_DutySlider_valueChanged(int value);
	void on_RadiusSlider_valueChanged(int value);
	void on_CenterLineSlider_valueChanged(int value);
	void on_BinSlider_valueChanged(int value);
	void on_DenoiseSlider_valueChanged(int value);

	void on_LedButton_clicked();        //���Ŵ�����
	void on_DcButton_clicked();         //ֱ���źſ���
	void on_SwButton_clicked();		    //�����źſ���
	void on_ElecStopButton_clicked();   //�糡ֹͣ����
	void on_BeginPrcButton_clicked();   //ͼ������
	void on_ContrastButton_clicked();   //�Աȶ���ǿ����
	void on_SaveButton_clicked();	    //���ݱ��濪��
	void on_ChgLanButton_clicked();     //�����л�����
	void on_ConnectButton_clicked();    //Զ��ģ������
	void on_RemoteStopButton_clicked(); //Զ��ָֹͣ��
	void on_RemoteLeftButton_clicked(); //Զ������ָ��
	void on_RemoteRightButton_clicked();//Զ������ָ��
	void on_UpButton_clicked();			//λ��̨����
	void on_DownButton_clicked();		//λ��̨����
	void on_LeftButton_clicked();		//λ��̨����
	void on_RightButton_clicked();		//λ��̨����
	void on_ResetButton_clicked();		//λ����Ϣ����
	void on_YLockButton_clicked();		//����λ������
	void on_TrackButton_clicked();		//���ٰ�ť
	void on_OpenDeviceButton_clicked();         //���豸
	void on_OpenLogButton_clicked();            //����־

protected:
	void shiftButtonTimer();  //λ�ư�����������
	void deleteButtonTimer(); //�ͷ�λ�ư���
	void connectButtonTimer();//���Ӷ�ʱ��
	void deleteTimer(QTimer* timer);

	void spinBoxConnect();    //����QSpinBox�źźͲ�
	void setLanguage(LanguageType lanType);

protected:
	/* ���ڰ������������� */
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
	/* ����SpinBox���������� */
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
	//������ϵ������ʱ��
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