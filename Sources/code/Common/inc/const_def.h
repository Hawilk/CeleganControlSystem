/*
 *@file     const_def.h
 *@brief    ���������ĵ�
 *@author   yangshuhao
 *@date     2024/9/1
 *@remarks
 *@version  1.1
 */

#pragma once
#include <string>
#include <map>

#define  picWidth       1600      //ͼƬ���
#define  picHeight      1100      //ͼƬ�߶�
#define  picDepthBit    16        //ͼƬλ���

#define  CAM_ERR        false     //���������ʾ
#define  CAM_SUC        true

#define  axisX          255       //λ��̨������
#define  axisY          254

#define  STAGE_ERR      false     //λ��̨������ʾ
#define  STAGE_SUC      true

#define  EXP_ERR        false     //ʵ�������ʾ
#define  EXP_SUC        true

#define  MAX_QUEUE_SIZE 10        //ͼƬ���е�����

//���״̬
enum class CameraStatus
{
	Normal,                  //������ʼ��״̬
	ShowInfoFailed,          //SDK��Ϣ��ѯ״̬
	InitCamFailed,           //��ʼ��״̬
	BeginGrabFrameFailed,    //��ʼץȡͼ��ש״̬
	GrabFrameFailed          //ץȡͼ��״̬
};

//���״̬
enum class StageStatus
{
	Normal,                  //����״̬
	Initializing             //��ʼ����
};

//λ��̨�ƶ��ķ�λ
enum class Direction
{
	Up,                      //��
	Down,                    //��
	Left,                    //��
	Right                    //��
};

//ͼ����Ĥ����
enum class MaskType
{
	Rectangle,               //����
	Circle                   //Բ��
};

//��������
enum class LanguageType
{
	Chinese,                 //����
	English					 //Ӣ��
};

typedef const std::map<LanguageType, std::string> textName;

/**************** �ַ����������� ********************/
const std::string configName = "../../config/PanelParameters.ini";

/************* Group�ı� *************/
textName ImageDisplaygroup = {
	{LanguageType::Chinese, "ͼ����ʾ����"},
	{LanguageType::English, "Image Display"}
};

textName OptoParamgroup = {
	{LanguageType::Chinese, "���Ŵ�����ģ��"},
	{LanguageType::English, "Optoelectronic Module Parameters"}
};

textName ElecParamgroup = {
	{LanguageType::Chinese, "�糡����ģ��"},
	{LanguageType::English, "Electric Field Stimulation Module"}
};

textName Processgroup = {
	{LanguageType::Chinese, "ͼ����ģ��"},
	{LanguageType::English, "Image Process Parameters"}
};

textName DataSavegroup = {
	{LanguageType::Chinese, "���ݴ洢"},
	{LanguageType::English, "Data Save Parameters"}
};

textName RemoteConnectgroup = {
	{LanguageType::Chinese, "Զ������ģ��"},
	{LanguageType::English, "Remote Connection Panel"}
};

textName StageParamgroup = {
	{LanguageType::Chinese, "λ��̨����ģ��"},
	{LanguageType::English, "Stage Control Parameters"}
};

/************* Label�ı� *************/

textName srcImagetext = {
	{LanguageType::Chinese, "ԭʼͼ��"},
	{LanguageType::English, "Source Image"}
};

textName prcImagetext = {
	{LanguageType::Chinese, "����ͼ��"},
	{LanguageType::English, "Processed Image"}
};

textName ledtext = {
	{LanguageType::Chinese, "��ǿ ��"},
	{LanguageType::English, "LED ��"}
};

textName amptext = {
	{LanguageType::Chinese, "��ֵ ��"},
	{LanguageType::English, "Amplitude ��"}
};

textName fretext = {
	{LanguageType::Chinese, "Ƶ�� ��"},
	{LanguageType::English, "Frequency ��"}
};

textName dutytext = {
	{LanguageType::Chinese, "ռ�ձ� ��"},
	{LanguageType::English, "Duty ��"}
};

textName frametext = {
	{LanguageType::Chinese, "֡�� ��"},
	{LanguageType::English, "Frame ��"}
};

textName fpstext = {
	{LanguageType::Chinese, "֡�� ��"},
	{LanguageType::English, "Frame Rate ��"}
};

textName masktext = {
	{LanguageType::Chinese, "��Ĥ ��"},
	{LanguageType::English, "Mask ��"}
};

textName radiustext = {
	{LanguageType::Chinese, "�뾶 ��"},
	{LanguageType::English, "Radius ��"}
};

textName centerlinetext = {
	{LanguageType::Chinese, "������ ��"},
	{LanguageType::English, "CenterLine ��"}
};

textName bintext = {
	{LanguageType::Chinese, "��ֵ ��"},
	{LanguageType::English, "Bin Thresh ��"}
};

textName denoisetext = {
	{LanguageType::Chinese, "ȥ�� ��"},
	{LanguageType::English, "Denoise ��"}
};

textName pathtext = {
	{LanguageType::Chinese, "·�� ��"},
	{LanguageType::English, "Path ��"}
};

textName nametext = {
	{LanguageType::Chinese, "���� ��"},
	{LanguageType::English, "Name ��"}
};

textName iptext = {
	{LanguageType::Chinese, "��ַ ��"},
	{LanguageType::English, "IP ��"}
};

textName porttext = {
	{LanguageType::Chinese, "�˿� ��"},
	{LanguageType::English, "Port ��"}
};

textName connectStatustext = {
	{LanguageType::Chinese, "����״̬ ��"},
	{LanguageType::English, "Connect Status ��"}
};

textName stopIndicatetext = {
	{LanguageType::Chinese, "ֹͣ"},
	{LanguageType::English, "STOP"}
};

textName leftIndicatetext = {
	{LanguageType::Chinese, "����"},
	{LanguageType::English, "LEFT"}
};

textName rightIndicatetext = {
	{LanguageType::Chinese, "����"},
	{LanguageType::English, "RIGHT"}
};

textName xPostext = {
	{LanguageType::Chinese, "������(um) ��"},
	{LanguageType::English, "X Pos(um) ��"}
};

textName yPostext = {
	{LanguageType::Chinese, "������(um) ��"},
	{LanguageType::English, "Y Pos(um) ��"}
};

textName velocitytext = {
	{LanguageType::Chinese, "�߳��ٶ�(um/s) ��"},
	{LanguageType::English, "Velocity(um/s) ��"}
};

textName stageSpeedtext = {
	{LanguageType::Chinese, "λ��̨�ٶ� ��"},
	{LanguageType::English, "StageSpeed ��"}
};

textName accelerationtext = {
	{LanguageType::Chinese, "λ��̨���ٶ� ��"},
	{LanguageType::English, "Acceleration ��"}
};

/************* pushbutton�ı� *************/

textName ledButtontext = {
	{LanguageType::Chinese, "��"},
	{LanguageType::English, "ON"}
};

textName DCButtontext = {
	{LanguageType::Chinese, "ֱ��"},
	{LanguageType::English, "DC Singal"}
};

textName SWButtontext = {
	{LanguageType::Chinese, "����"},
	{LanguageType::English, "Square Wave"}
};

textName StopButtontext = {
	{LanguageType::Chinese, "ֹͣ"},
	{LanguageType::English, "Stop"}
};

textName BeginPrcButtontext = {
	{LanguageType::Chinese, "��ʼ����"},
	{LanguageType::English, "Begin Process"}
};

textName CtrImpButtontext = {
	{LanguageType::Chinese, "�Աȶ���ǿ"},
	{LanguageType::English, "Constrast Improve"}
};

textName SaveButtontext = {
	{LanguageType::Chinese, "����"},
	{LanguageType::English, "Save"}
};

textName ConnectButtontext = {
	{LanguageType::Chinese, "����"},
	{LanguageType::English, "Connect"}
};

textName CntStopButtontext = {
	{LanguageType::Chinese, "ֹͣ"},
	{LanguageType::English, "Stop"}
};

textName CntLeftButtontext = {
	{LanguageType::Chinese, "����"},
	{LanguageType::English, "Left"}
};

textName CntRightButtontext = {
	{LanguageType::Chinese, "����"},
	{LanguageType::English, "Right"}
};

textName ResetButtontext = {
	{LanguageType::Chinese, "����"},
	{LanguageType::English, "Reset"}
};

textName YLockButtontext = {
	{LanguageType::Chinese, "Y������"},
	{LanguageType::English, "Y Move Lock"}
};

textName StartTrackButtontext = {
	{LanguageType::Chinese, "��ʼ����"},
	{LanguageType::English, "Start Track"}
};

textName OpenDeviceButtontext = {
	{LanguageType::Chinese, "���豸"},
	{LanguageType::English, "Open Device"}
};

textName OpenLogFileButtontext = {
	{LanguageType::Chinese, "����־"},
	{LanguageType::English, "Open Log File"}
};

/************* radiobutton�ı� *************/

textName circleChecktext = {
	{LanguageType::Chinese, "Բ��"},
	{LanguageType::English, "Circle"}
};

textName rectChecktext = {
	{LanguageType::Chinese, "����"},
	{LanguageType::English, "Rectan"}
};

textName operationStoptext = {
	{LanguageType::Chinese, "ָ��1"},
	{LanguageType::English, "Operation1"}
};

textName operationLefttext = {
	{LanguageType::Chinese, "ָ��2"},
	{LanguageType::English, "Operation2"}
};

textName operationRighttext = {
	{LanguageType::Chinese, "ָ��3"},
	{LanguageType::English, "Operation3"}
};