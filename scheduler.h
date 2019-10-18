#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include "fgk.h"


struct perf_t {
    int ar_time;
    int wait_time;
    int turn_around_time;
    int comp_time;
};

struct proc_t {
	int id;
	int ar_time;
	int burst_time;
	int priority;
	int cpflag;
	int btcopy;
};



class Scheduler {
private:
	FGK::FGKTree tree;
	proc_t* proc_arr;
	int nprocs;
	int ctx_time;
    std::vector<proc_t> rrbuf;
    std::map<int, perf_t> perf_map;

	void sortProcesses();

public:
	int max_q;

	//hyper-parameters
	int alpha;

	Scheduler();
	Scheduler(int max_processes);
	int getDepth(int proc_id);
	int getQuantum(int proc_id);
	void loadProcesses(proc_t* procs, int n);
	void placeInTree(proc_t proc);
	void run();
	void setContextSwitchingTime(int time);
	void evaluatePerf();
	void displayPerf();
	std::map<int, perf_t> getPerfMap();
};
