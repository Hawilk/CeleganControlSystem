#include "Experiment.h"

int main(int argc, char* argv[])
{
    Experiment exp;
    exp.print();

    exp.pvcamTest(argc, argv);

    return 0;
}