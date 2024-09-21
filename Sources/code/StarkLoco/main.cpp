#include "Experiment.h"
#include "systemInterface.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	systemInterface w;
	w.show();

    return QApplication::exec();
}