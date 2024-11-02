/*
 *@file     const_def.h
 *@brief    常量定义文档
 *@author   yangshuhao
 *@date     2024/9/1
 *@remarks
 *@version  1.1
 */

#pragma once
#include <string>
#include <map>

#define  picWidth       1600      //图片宽度
#define  picHeight      1100      //图片高度
#define  picDepthBit    16        //图片位深度

#define  CAM_ERR        false     //相机错误提示
#define  CAM_SUC        true

#define  axisX          255       //位移台坐标轴
#define  axisY          254

#define  STAGE_ERR      false     //位移台错误提示
#define  STAGE_SUC      true

#define  EXP_ERR        false     //实验错误提示
#define  EXP_SUC        true

#define  MAX_QUEUE_SIZE 10        //图片队列的容量

//相机状态
enum class CameraStatus
{
	Normal,                  //正常初始化状态
	ShowInfoFailed,          //SDK信息查询状态
	InitCamFailed,           //初始化状态
	BeginGrabFrameFailed,    //开始抓取图像砖状态
	GrabFrameFailed          //抓取图像状态
};

//相机状态
enum class StageStatus
{
	Normal,                  //正常状态
	Initializing             //初始化中
};

//位移台移动的方位
enum class Direction
{
	Up,                      //上
	Down,                    //下
	Left,                    //左
	Right                    //右
};

//图像掩膜类型
enum class MaskType
{
	Rectangle,               //矩形
	Circle                   //圆形
};

//语言类型
enum class LanguageType
{
	Chinese,                 //中文
	English					 //英文
};

typedef const std::map<LanguageType, std::string> textName;

/**************** 字符常量定义区 ********************/
const std::string configName = "../../config/PanelParameters.ini";

/************* Group文本 *************/
textName ImageDisplaygroup = {
	{LanguageType::Chinese, "图像显示区域"},
	{LanguageType::English, "Image Display"}
};

textName OptoParamgroup = {
	{LanguageType::Chinese, "光遗传控制模块"},
	{LanguageType::English, "Optoelectronic Module Parameters"}
};

textName ElecParamgroup = {
	{LanguageType::Chinese, "电场控制模块"},
	{LanguageType::English, "Electric Field Stimulation Module"}
};

textName Processgroup = {
	{LanguageType::Chinese, "图像处理模块"},
	{LanguageType::English, "Image Process Parameters"}
};

textName DataSavegroup = {
	{LanguageType::Chinese, "数据存储"},
	{LanguageType::English, "Data Save Parameters"}
};

textName RemoteConnectgroup = {
	{LanguageType::Chinese, "远程连接模块"},
	{LanguageType::English, "Remote Connection Panel"}
};

textName StageParamgroup = {
	{LanguageType::Chinese, "位移台控制模块"},
	{LanguageType::English, "Stage Control Parameters"}
};

/************* Label文本 *************/

textName srcImagetext = {
	{LanguageType::Chinese, "原始图像"},
	{LanguageType::English, "Source Image"}
};

textName prcImagetext = {
	{LanguageType::Chinese, "处理图像"},
	{LanguageType::English, "Processed Image"}
};

textName ledtext = {
	{LanguageType::Chinese, "光强 ："},
	{LanguageType::English, "LED ："}
};

textName amptext = {
	{LanguageType::Chinese, "幅值 ："},
	{LanguageType::English, "Amplitude ："}
};

textName fretext = {
	{LanguageType::Chinese, "频率 ："},
	{LanguageType::English, "Frequency ："}
};

textName dutytext = {
	{LanguageType::Chinese, "占空比 ："},
	{LanguageType::English, "Duty ："}
};

textName frametext = {
	{LanguageType::Chinese, "帧数 ："},
	{LanguageType::English, "Frame ："}
};

textName fpstext = {
	{LanguageType::Chinese, "帧率 ："},
	{LanguageType::English, "Frame Rate ："}
};

textName masktext = {
	{LanguageType::Chinese, "掩膜 ："},
	{LanguageType::English, "Mask ："}
};

textName radiustext = {
	{LanguageType::Chinese, "半径 ："},
	{LanguageType::English, "Radius ："}
};

textName centerlinetext = {
	{LanguageType::Chinese, "中心线 ："},
	{LanguageType::English, "CenterLine ："}
};

textName bintext = {
	{LanguageType::Chinese, "阈值 ："},
	{LanguageType::English, "Bin Thresh ："}
};

textName denoisetext = {
	{LanguageType::Chinese, "去噪 ："},
	{LanguageType::English, "Denoise ："}
};

textName pathtext = {
	{LanguageType::Chinese, "路径 ："},
	{LanguageType::English, "Path ："}
};

textName nametext = {
	{LanguageType::Chinese, "名称 ："},
	{LanguageType::English, "Name ："}
};

textName iptext = {
	{LanguageType::Chinese, "地址 ："},
	{LanguageType::English, "IP ："}
};

textName porttext = {
	{LanguageType::Chinese, "端口 ："},
	{LanguageType::English, "Port ："}
};

textName connectStatustext = {
	{LanguageType::Chinese, "连接状态 ："},
	{LanguageType::English, "Connect Status ："}
};

textName stopIndicatetext = {
	{LanguageType::Chinese, "停止"},
	{LanguageType::English, "STOP"}
};

textName leftIndicatetext = {
	{LanguageType::Chinese, "向左"},
	{LanguageType::English, "LEFT"}
};

textName rightIndicatetext = {
	{LanguageType::Chinese, "向右"},
	{LanguageType::English, "RIGHT"}
};

textName xPostext = {
	{LanguageType::Chinese, "横坐标(um) ："},
	{LanguageType::English, "X Pos(um) ："}
};

textName yPostext = {
	{LanguageType::Chinese, "纵坐标(um) ："},
	{LanguageType::English, "Y Pos(um) ："}
};

textName velocitytext = {
	{LanguageType::Chinese, "线虫速度(um/s) ："},
	{LanguageType::English, "Velocity(um/s) ："}
};

textName stageSpeedtext = {
	{LanguageType::Chinese, "位移台速度 ："},
	{LanguageType::English, "StageSpeed ："}
};

textName accelerationtext = {
	{LanguageType::Chinese, "位移台加速度 ："},
	{LanguageType::English, "Acceleration ："}
};

/************* pushbutton文本 *************/

textName ledButtontext = {
	{LanguageType::Chinese, "打开"},
	{LanguageType::English, "ON"}
};

textName DCButtontext = {
	{LanguageType::Chinese, "直流"},
	{LanguageType::English, "DC Singal"}
};

textName SWButtontext = {
	{LanguageType::Chinese, "方波"},
	{LanguageType::English, "Square Wave"}
};

textName StopButtontext = {
	{LanguageType::Chinese, "停止"},
	{LanguageType::English, "Stop"}
};

textName BeginPrcButtontext = {
	{LanguageType::Chinese, "开始处理"},
	{LanguageType::English, "Begin Process"}
};

textName CtrImpButtontext = {
	{LanguageType::Chinese, "对比度增强"},
	{LanguageType::English, "Constrast Improve"}
};

textName SaveButtontext = {
	{LanguageType::Chinese, "保存"},
	{LanguageType::English, "Save"}
};

textName ConnectButtontext = {
	{LanguageType::Chinese, "连接"},
	{LanguageType::English, "Connect"}
};

textName CntStopButtontext = {
	{LanguageType::Chinese, "停止"},
	{LanguageType::English, "Stop"}
};

textName CntLeftButtontext = {
	{LanguageType::Chinese, "向左"},
	{LanguageType::English, "Left"}
};

textName CntRightButtontext = {
	{LanguageType::Chinese, "向右"},
	{LanguageType::English, "Right"}
};

textName ResetButtontext = {
	{LanguageType::Chinese, "重置"},
	{LanguageType::English, "Reset"}
};

textName YLockButtontext = {
	{LanguageType::Chinese, "Y轴锁定"},
	{LanguageType::English, "Y Move Lock"}
};

textName StartTrackButtontext = {
	{LanguageType::Chinese, "开始跟踪"},
	{LanguageType::English, "Start Track"}
};

textName OpenDeviceButtontext = {
	{LanguageType::Chinese, "打开设备"},
	{LanguageType::English, "Open Device"}
};

textName OpenLogFileButtontext = {
	{LanguageType::Chinese, "打开日志"},
	{LanguageType::English, "Open Log File"}
};

/************* radiobutton文本 *************/

textName circleChecktext = {
	{LanguageType::Chinese, "圆形"},
	{LanguageType::English, "Circle"}
};

textName rectChecktext = {
	{LanguageType::Chinese, "矩形"},
	{LanguageType::English, "Rectan"}
};

textName operationStoptext = {
	{LanguageType::Chinese, "指令1"},
	{LanguageType::English, "Operation1"}
};

textName operationLefttext = {
	{LanguageType::Chinese, "指令2"},
	{LanguageType::English, "Operation2"}
};

textName operationRighttext = {
	{LanguageType::Chinese, "指令3"},
	{LanguageType::English, "Operation3"}
};