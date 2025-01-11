#include "systemInterface.h"
#include "ui_systemInterface.h"
#include <iostream>
#include <QDebug>

systemInterface::systemInterface()
{
	
}

systemInterface::systemInterface(int argc, char* argv[]) : interface_argc(argc), interface_argv(argv), deviceStatus(false)
{
	ui = std::make_shared<Ui::systemInterface>();
	ui->setupUi(this);

	// 确保窗口部件可以接收到键盘事件
	setFocusPolicy(Qt::StrongFocus);

	shiftButtonTimer();
	spinBoxConnect();

	//开启定时器事件 - 显示图像
	startTimer(50);
}

systemInterface::~systemInterface()
{
	deleteButtonTimer();
}

void systemInterface::timerEvent(QTimerEvent* event)
{
	if (deviceStatus == false) return;

	cv::Mat origin = m_exp->getCurImage();
	cv::Mat prcImage = m_exp->getCurPrcImageWithIndicate();

	QSize labelSize0 = ui->SrcImage->size();
	QSize labelSize1 = ui->PrcImage->size();
	cv::resize(origin, origin, cv::Size(labelSize0.width(), labelSize0.height()));
	cv::resize(prcImage, prcImage, cv::Size(labelSize0.width(), labelSize0.height()));
	QImage qImage = MatToImage(origin);
	QImage prc = MatToImage(prcImage);

	ui->SrcImage->setPixmap(QPixmap::fromImage(qImage));
	ui->PrcImage->setPixmap(QPixmap::fromImage(prc));
}

QImage systemInterface::MatToImage(const cv::Mat& mat)
{
	if (mat.empty()) {
		return QImage();
	}

	switch (mat.type()) {
	case CV_8UC1: {
		QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8);
		return image;
	}
	case CV_8UC3: {
		QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	case CV_8UC4: {
		QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_ARGB32);
		return image;
	}
	default:
		break;
	}

	return QImage();
}

void systemInterface::on_LedSlider_valueChanged(int value)
{
	ui->LedSpin->setValue(value);
}

void systemInterface::on_AmpSlider_valueChanged(int value)
{
	ui->AmpSpin->setValue(value);
}

void systemInterface::on_FreSlider_valueChanged(int value)
{
	ui->FreSpin->setValue(value);
}

void systemInterface::on_DutySlider_valueChanged(int value)
{
	ui->DutySpin->setValue(value);
}

void systemInterface::on_RadiusSlider_valueChanged(int value)
{
	ui->RadiusSpin->setValue(value);
}

void systemInterface::on_CenterLineSlider_valueChanged(int value)
{
	ui->CenterLineSpin->setValue(value);
}

void systemInterface::on_BinSlider_valueChanged(int value)
{
	ui->BinSpin->setValue(value);
}

void systemInterface::on_DenoiseSlider_valueChanged(int value)
{
	ui->DenoiseSpin->setValue(value);
}

void systemInterface::on_LedButton_clicked()
{

}

void systemInterface::on_DcButton_clicked()
{

}

void systemInterface::on_SwButton_clicked()
{

}

void systemInterface::on_ElecStopButton_clicked()
{

}

void systemInterface::on_BeginPrcButton_clicked()
{

}

void systemInterface::on_ContrastButton_clicked()
{

}

void systemInterface::on_SaveButton_clicked()
{

}

void systemInterface::on_ChgLanButton_clicked()
{
	auto text = ui->ChgLanButton->text();
	const QString chineseText = QString::fromLocal8Bit("切换中文");
	if (text == chineseText)
	{
		setLanguage(LanguageType::Chinese);
		ui->ChgLanButton->setText(QString::fromUtf8("English"));
	}
	else
	{
		setLanguage(LanguageType::English);
		ui->ChgLanButton->setText(chineseText);
	}
}

void systemInterface::on_ConnectButton_clicked()
{

}

void systemInterface::on_RemoteStopButton_clicked()
{

}

void systemInterface::on_RemoteLeftButton_clicked()
{

}

void systemInterface::on_RemoteRightButton_clicked()
{

}

void systemInterface::on_UpButton_clicked()
{

}

void systemInterface::on_DownButton_clicked()
{

}

void systemInterface::on_LeftButton_clicked()
{

}

void systemInterface::on_RightButton_clicked()
{

}

void systemInterface::on_ResetButton_clicked()
{

}

void systemInterface::on_YLockButton_clicked()
{

}

void systemInterface::on_TrackButton_clicked()
{

}

void systemInterface::on_OpenDeviceButton_clicked()
{
	if (!deviceStatus)
	{
		m_exp = std::make_unique<Experiment>(interface_argc, interface_argv);
		m_exp->AutoDo();

		if(m_exp->checkDeviceStatus())
			deviceStatus = true;
	}
}

void systemInterface::on_OpenLogButton_clicked()
{

}

void systemInterface::shiftButtonTimer()
{
	//初始化定时器
	m_upTimer    = new QTimer(this);
	m_downTimer  = new QTimer(this);
	m_leftTimer  = new QTimer(this);
	m_rightTimer = new QTimer(this);

	connectButtonTimer();
}

void systemInterface::deleteButtonTimer()
{
	deleteTimer(m_upTimer);
	deleteTimer(m_downTimer);
	deleteTimer(m_leftTimer);
	deleteTimer(m_rightTimer);
}

void systemInterface::connectButtonTimer()
{
	connect(m_upTimer, &QTimer::timeout, this, &systemInterface::onUpButtonTimeout);
	connect(m_downTimer, &QTimer::timeout, this, &systemInterface::onDownButtonTimeout);
	connect(m_leftTimer, &QTimer::timeout, this, &systemInterface::onLeftButtonTimeout);
	connect(m_rightTimer, &QTimer::timeout, this, &systemInterface::onRightButtonTimeout);

	connect(ui->UpButton, &QPushButton::pressed, this, &systemInterface::onUpButtonPressed);
	connect(ui->UpButton, &QPushButton::released, this, &systemInterface::onUpButtonReleased);
	connect(ui->DownButton, &QPushButton::pressed, this, &systemInterface::onDownButtonPressed);
	connect(ui->DownButton, &QPushButton::released, this, &systemInterface::onDownButtonReleased);
	connect(ui->LeftButton, &QPushButton::pressed, this, &systemInterface::onLeftButtonPressed);
	connect(ui->LeftButton, &QPushButton::released, this, &systemInterface::onLeftButtonReleased);
	connect(ui->RightButton, &QPushButton::pressed, this, &systemInterface::onRightButtonPressed);
	connect(ui->RightButton, &QPushButton::released, this, &systemInterface::onRightButtonReleased);
}

void systemInterface::deleteTimer(QTimer* timer)
{
	if (timer != nullptr)
	{
		delete timer;
		timer = nullptr;
	}
}

void systemInterface::spinBoxConnect()
{
	connect(ui->LedSpin, &QSpinBox::editingFinished, this, &systemInterface::LedSpin_valueChanged);
	connect(ui->AmpSpin, &QSpinBox::editingFinished, this, &systemInterface::AmpSpin_valueChanged);
	connect(ui->FreSpin, &QSpinBox::editingFinished, this, &systemInterface::FreSpin_valueChanged);
	connect(ui->DutySpin, &QSpinBox::editingFinished, this, &systemInterface::DutySpin_valueChanged);
	connect(ui->RadiusSpin, &QSpinBox::editingFinished, this, &systemInterface::RadiusSpin_valueChanged);
	connect(ui->CenterLineSpin, &QSpinBox::editingFinished, this, &systemInterface::CenterLineSpin_valueChanged);
	connect(ui->BinSpin, &QSpinBox::editingFinished, this, &systemInterface::BinSpin_valueChanged);
	connect(ui->DenoiseSpin, &QSpinBox::editingFinished, this, &systemInterface::DenoiseSpin_valueChanged);
	connect(ui->SpeedSpin, &QSpinBox::editingFinished, this, &systemInterface::SpeedSpin_valueChanged);
	connect(ui->AccelerationSpin, &QSpinBox::editingFinished, this, &systemInterface::AccelerationSpin_valueChanged);
}

void systemInterface::setLanguage(LanguageType lanType)
{
	//设置GroupBox标题
	auto setGroupText = [=](QGroupBox* groupBox, textName& text) {
		groupBox->setTitle(QString::fromLocal8Bit(text.at(lanType).c_str()));
	};
	setGroupText(ui->Display, ImageDisplaygroup);
	setGroupText(ui->OptoParam, OptoParamgroup);
	setGroupText(ui->ElecParam, ElecParamgroup);
	setGroupText(ui->ProcessParam, Processgroup);
	setGroupText(ui->DataSave, DataSavegroup);
	setGroupText(ui->RemoteConnect, RemoteConnectgroup);
	setGroupText(ui->StageParam, StageParamgroup);

	//设置Label文本
	auto setLabelText = [=](QLabel* label, textName& text) {
		label->setText(QString::fromLocal8Bit(text.at(lanType).c_str()));
	};
	setLabelText(ui->SrcImageText, srcImagetext);
	setLabelText(ui->PrcImageText, prcImagetext);
	setLabelText(ui->LedText, ledtext);
	setLabelText(ui->AmpText, amptext);
	setLabelText(ui->FreText, fretext);
	setLabelText(ui->DutyText, dutytext);
	setLabelText(ui->FrameText, frametext);
	setLabelText(ui->FPSText, fpstext);
	setLabelText(ui->MaskText, masktext);
	setLabelText(ui->RadiusText, radiustext);
	setLabelText(ui->CenterLineText, centerlinetext);
	setLabelText(ui->BinText, bintext);
	setLabelText(ui->DenoiseText, denoisetext);
	setLabelText(ui->PathText, pathtext);
	setLabelText(ui->NameText, nametext);
	setLabelText(ui->IPText, iptext);
	setLabelText(ui->PortText, porttext);
	setLabelText(ui->ConnectStatusText, connectStatustext);
	setLabelText(ui->StopIndicate, stopIndicatetext);
	setLabelText(ui->LeftIndicate, leftIndicatetext);
	setLabelText(ui->RightIndicate, rightIndicatetext);
	setLabelText(ui->xPosText, xPostext);
	setLabelText(ui->yPosText, yPostext);
	setLabelText(ui->VelocityText, velocitytext);
	setLabelText(ui->StageSpeedText, stageSpeedtext);
	setLabelText(ui->AccelerationText, accelerationtext);

	//设置PushButton文本
	auto setButtonText = [=](QPushButton* button, textName& text) {
		button->setText(QString::fromLocal8Bit(text.at(lanType).c_str()));
	};
	setButtonText(ui->LedButton, ledButtontext);
	setButtonText(ui->DcButton, DCButtontext);
	setButtonText(ui->SwButton, SWButtontext);
	setButtonText(ui->ElecStopButton, StopButtontext);
	setButtonText(ui->BeginPrcButton, BeginPrcButtontext);
	setButtonText(ui->ContrastButton, CtrImpButtontext);
	setButtonText(ui->SaveButton, SaveButtontext);
	setButtonText(ui->ConnectButton, ConnectButtontext);
	setButtonText(ui->RemoteStopButton, CntStopButtontext);
	setButtonText(ui->RemoteLeftButton, CntLeftButtontext);
	setButtonText(ui->RemoteRightButton, CntRightButtontext);
	setButtonText(ui->ResetButton, ResetButtontext);
	setButtonText(ui->YLockButton, YLockButtontext);
	setButtonText(ui->TrackButton, StartTrackButtontext);
	setButtonText(ui->OpenDeviceButton, OpenDeviceButtontext);
	setButtonText(ui->OpenLogButton, OpenLogFileButtontext);

	//设置PushButton文本
	auto setRadioButtonText = [=](QRadioButton* button, textName& text) {
		button->setText(QString::fromLocal8Bit(text.at(lanType).c_str()));
	};
	setRadioButtonText(ui->CircleCheck, circleChecktext);
	setRadioButtonText(ui->RectCheck, rectChecktext);
	setRadioButtonText(ui->OperationStop, operationStoptext);
	setRadioButtonText(ui->OperationLeft, operationLefttext);
	setRadioButtonText(ui->OperationRight, operationRighttext);
}

void systemInterface::onUpButtonPressed()
{
	m_upTimer->start(100); // 启动定时器，间隔100毫秒
}

void systemInterface::onUpButtonReleased()
{
	m_upTimer->stop(); // 停止定时器
}

void systemInterface::onDownButtonPressed()
{
	m_downTimer->start(100);
}

void systemInterface::onDownButtonReleased()
{
	m_downTimer->stop();
}

void systemInterface::onLeftButtonPressed()
{
	m_leftTimer->start(100);
}

void systemInterface::onLeftButtonReleased()
{
	m_leftTimer->stop();
}

void systemInterface::onRightButtonPressed()
{
	m_rightTimer->start(100);
}

void systemInterface::onRightButtonReleased()
{
	m_rightTimer->stop();
}

void systemInterface::onUpButtonTimeout()
{
	//该部分待与实际功能连接
}

void systemInterface::onDownButtonTimeout()
{

}

void systemInterface::onLeftButtonTimeout()
{

}

void systemInterface::onRightButtonTimeout()
{

}

void systemInterface::LedSpin_valueChanged()
{
	auto value = ui->LedSpin->value();
	ui->LedSlider->setValue(value);
}

void systemInterface::AmpSpin_valueChanged()
{
	auto value = ui->AmpSpin->value();
	ui->AmpSlider->setValue(value);
}

void systemInterface::FreSpin_valueChanged()
{
	auto value = ui->FreSpin->value();
	ui->FreSlider->setValue(value);
}

void systemInterface::DutySpin_valueChanged()
{
	auto value = ui->DutySpin->value();
	ui->DutySlider->setValue(value);
}

void systemInterface::RadiusSpin_valueChanged()
{
	auto value = ui->RadiusSpin->value();
	ui->RadiusSlider->setValue(value);
}

void systemInterface::CenterLineSpin_valueChanged()
{
	auto value = ui->CenterLineSpin->value();
	ui->CenterLineSlider->setValue(value);
}

void systemInterface::BinSpin_valueChanged()
{
	auto value = ui->BinSpin->value();
	ui->BinSlider->setValue(value);
}

void systemInterface::DenoiseSpin_valueChanged()
{
	auto value = ui->DenoiseSpin->value();
	ui->DenoiseSlider->setValue(value);
}

void systemInterface::SpeedSpin_valueChanged()
{

}

void systemInterface::AccelerationSpin_valueChanged()
{

}
