
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

void Scheduler::age(proc_t proc) {
	tree.update(proc.id);
}

void Scheduler::setContextSwitchingTime(int time) {
	max_q = alpha * time;
}

void Scheduler::loadProcesses(proc_t *procs, int n) {
	for (int i = 0; i < n; i++) {
		placeInTree(procs[i]);
	}
}



int main()
{
	Scheduler sh(100);
	proc_t p;
	int arr[8];
	
	for (int i = 1; i < 7; i++) {
		p.id = i;
		p.priority = 1 + rand() * 10 / RAND_MAX;
		arr[i] = p.priority;
		sh.placeInTree(p);
		
	}
	
	for (int i = 1; i < 7; i++) {
		
		std::cout << "priority(" << arr[i] << ")" << " -> " << sh.getDepth(i) << std::endl;
	}
	
	
	return 0;
}

