#include "systemInterface.h"
#include "ui_systemInterface.h"

systemInterface::systemInterface():
	ui(new Ui::systemInterface)
{
	ui->setupUi(this);
}

systemInterface::~systemInterface()
{

}
