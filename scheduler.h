#pragma once
#include "fgk.h"


struct perf_t {
    int wait_time;
    int turn_around_time;
    int response_time;
};

struct proc_t {
	int id;
	int ar_time;
	int burst_time;
	int priority;
	perf_t performance;
};



class Scheduler {
private:
	FGK::FGKTree tree;
	proc_t* proc_arr;
	int nprocs;

	void sortProcesses();
public:
	int max_q;

	//hyper-parameters
	int alpha;
	int beta;

	Scheduler();
	Scheduler(int max_processes);
	int getDepth(int proc_id);
	void loadProcesses(proc_t* procs, int n);
	void placeInTree(proc_t proc);
	void run();
	void setContextSwitchingTime(int time);
};
