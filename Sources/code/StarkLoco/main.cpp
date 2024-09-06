#include "Experiment.h"

int main(int argc, char* argv[])
{
    Experiment exp(argc, argv);

    exp.stageTest(3);

    return 0;
}