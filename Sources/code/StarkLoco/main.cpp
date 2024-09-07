#include "Experiment.h"

int main(int argc, char* argv[])
{
    ExperimentPtr exp = std::make_unique<Experiment>(argc, argv);

    //exp->pvcamTest();

    return 0;
}