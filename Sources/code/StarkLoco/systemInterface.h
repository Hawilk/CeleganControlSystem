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

QT_BEGIN_NAMESPACE
namespace Ui {
	class systemInterface;
}
QT_END_NAMESPACE

class systemInterface : public QWidget
{
	Q_OBJECT

public:
	systemInterface();
	~systemInterface();

public:
	Ui::systemInterface *ui;

private:

};


#endif