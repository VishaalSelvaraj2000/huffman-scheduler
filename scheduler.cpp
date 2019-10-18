
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

int Scheduler::getQuantum(int proc_id) {
    return max_q / getDepth(proc_id);
}

void Scheduler::setContextSwitchingTime(int time) {
    ctx_time = time;
	max_q = alpha * time;
}

void Scheduler::loadProcesses(proc_t *procs, int n) {
    for(int i = 0; i < n; i++) {
        procs[i].btcopy = procs[i].burst_time;
    }
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
            } else if((proc_arr[i].ar_time == proc_arr[i+1].ar_time) && (proc_arr[i].priority < proc_arr[i+1].priority)) {
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
    //now we calculate total-burst-time
    int total_burst = 0;
    for(int i = 0; i < nprocs; i++) {
        total_burst += proc_arr[i].burst_time;
        perf_map[proc_arr[i].id] = perf_t{proc_arr[i].ar_time,0, 0, 0};
    }
    // now we start our performance-analysis
    int time = 0;
    int cv_burst = 0;
    int ncp = 0;
    int proc_index = 0;
    int rri = 0;
    while(cv_burst < total_burst) {
        for(int i = proc_index; i < nprocs; i++) {
            if(proc_arr[i].ar_time <= time) {
                rrbuf.push_back(proc_arr[i]);
                placeInTree(proc_arr[i]);
            } else {
                proc_index = i;
                break;
            }
            if(i == nprocs - 1)
                proc_index = nprocs;
        }

        if((ncp == rrbuf.size()) && (ncp < nprocs)) {
            time += 1;
            continue;
        }
        if(rrbuf[rri].cpflag) {
            rri = (rri + 1) % rrbuf.size();
            continue;
        }
        int qtm = getQuantum(rrbuf[rri].id);
        if(qtm >= rrbuf[rri].burst_time) {
            qtm = rrbuf[rri].burst_time;
            rrbuf[rri].burst_time = 0;

            perf_map[rrbuf[rri].id].comp_time = time > 0 ? time : qtm;
            tree.remove(rrbuf[rri].id);
            rrbuf[rri].cpflag = 1;
            ncp++;
            std::cout << rrbuf[rri].id << "->";
        } else {
            rrbuf[rri].burst_time -= qtm;
            std::cout << rrbuf[rri].id << "->";
        }
        cv_burst += qtm;
        time += qtm + ctx_time;
        rri = (rri + 1) % rrbuf.size();

    }
}

void Scheduler::evaluatePerf() {
    for(int i = 0; i < nprocs; i++) {
        perf_map[proc_arr[i].id].turn_around_time = perf_map[proc_arr[i].id].comp_time - perf_map[proc_arr[i].id].ar_time;
        perf_map[proc_arr[i].id].wait_time = perf_map[proc_arr[i].id].turn_around_time - proc_arr[i].btcopy;
    }
}

std::map<int, perf_t> Scheduler::getPerfMap() {
    return perf_map;
}

void Scheduler::displayPerf() {
    std::cout << std::setw(60) << " ---- Huffman-Scheduler Performance Analytics ---- " << std::endl;
    float avwt,avtt;
    avwt = avtt = 0;
    for(int i = 0; i < nprocs; i++) {
        std::cout << std::setw(30) << "Pid: " << proc_arr[i].id << std::setw(30) << "Arrival Time: " << proc_arr[i].ar_time << std::endl;
        std::cout << std::setw(30) << "Waiting Time: " << perf_map[proc_arr[i].id].wait_time <<
        std::setw(30) << "Turnaround Time: "
        << perf_map[proc_arr[i].id].turn_around_time << std::endl << std::endl;

        avwt += perf_map[proc_arr[i].id].wait_time;
        avtt += perf_map[proc_arr[i].id].turn_around_time;
    }

    std::cout << "Average Waiting Time: " << avwt / nprocs << std::endl;
    std::cout << "Average Turn-around Time: " << avtt / nprocs << std::endl;
}





