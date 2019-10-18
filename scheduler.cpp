
#include <iostream>
#include "fgk.h"
#include "scheduler.h"

Scheduler::Scheduler() {
	//default-constructor
}

Scheduler::Scheduler(int max_processes) {
	tree = FGK::FGKTree(max_processes);
}

void Scheduler::placeInTree(proc_t proc) {
	for (int i = 0; i < proc.priority; i++) {
		tree.update(proc.id);
	}
}

int Scheduler::getDepth(int proc_id) {
	return tree.getDepth(proc_id);
}

void Scheduler::setContextSwitchingTime(int time) {
	max_q = alpha * time;
}

void Scheduler::loadProcesses(proc_t *procs, int n) {
    proc_arr = procs;
	nprocs = n;
}

void Scheduler::sortProcesses() {
    while(true) {
        int sw = 1;
        for(int i = 0; i < nprocs - 1; i++) {
            if(proc_arr[i].ar_time > proc_arr[i+1].ar_time) {
                proc_t temp = proc_arr[i];
                proc_arr[i] = proc_arr[i+1];
                proc_arr[i+1] = temp;
                sw = 0;
            }
        }
        if(sw)
            break;
    }
}

void Scheduler::run() {
    //first we sort processes by arrival time
    sortProcesses();
    // now we start our performance-analysis
    int time = 0;
}





