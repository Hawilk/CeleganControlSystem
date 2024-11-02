#include "Experiment.h"
#include "systemInterface.h"
#include <QApplication>

int main(int argc, char* argv[])
{

#if 1
	QApplication a(argc, argv);

	systemInterface w(argc, argv);
	w.show();

    return QApplication::exec();

#else
	ExperimentPtr exp = std::make_unique<Experiment>(argc, argv);
	exp->AutoDo();

	return 0;
#endif
}