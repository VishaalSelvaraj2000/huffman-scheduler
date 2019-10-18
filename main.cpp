#include <iostream>
#include "scheduler.h"

int main()
{
    Scheduler sh(100);
    sh.alpha = 7;
    sh.setContextSwitchingTime(1);

    int N = 5;
    proc_t* procs = new proc_t[N];
    procs[0] = proc_t{0, 1, 4, 3};
    procs[1] = proc_t{1, 0, 2, 2};
    procs[2] = proc_t{2, 2, 3, 3};
    procs[3] = proc_t{3, 20, 4, 50};
    procs[4] = proc_t{4, 0, 9, 7};
    sh.loadProcesses(procs, N);
    sh.run();
    std::cout << "Run completed.." << std::endl;
    sh.evaluatePerf();
    sh.displayPerf();
    return 0;
}