#include <iostream>
#include "fgk.h"
#include "scheduler.h"

int main()
{
    Scheduler sh(100);
    proc_t p;
    int arr[8];

    for (int i = 1; i < 7; i++) {
        p.id = i;
        p.priority = 1 + i*1.1;
        arr[i] = p.priority;
        sh.placeInTree(p);
    }

    for (int i = 1; i < 7; i++) {

        std::cout << "priority(" << arr[i] << ")" << " -> " << sh.getDepth(i) << std::endl;
    }


    return 0;
}