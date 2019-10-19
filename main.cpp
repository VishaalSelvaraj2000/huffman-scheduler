#include <iostream>
#include "scheduler.h"

int main()
{
    Scheduler sh(100);
    sh.alpha = 19; // context-switching loss: 5%
    sh.setContextSwitchingTime(1);

    int N = 0;
    std::cout << "Enter the number of processes: " << std::endl;
    std::cin >> N;
    proc_t* procs = new proc_t[N];

    for(int i = 0; i < N; i++) {
        std::cout << "Enter process (id, arrival time, burst time, priority)" << std::endl;
        std::cin >> procs[i].id >> procs[i].ar_time >> procs[i].burst_time >> procs[i].priority;
    }

    sh.loadProcesses(procs, N);
    sh.run();
    std::cout << "Run completed.." << std::endl;
    sh.evaluatePerf();
    sh.displayPerf();
    return 0;
}