#include "fcfs.h"
#include <iomanip>
#include <iostream>

void fcfs(std::queue<Process> processStack) {
    double finishTimeAverage = 0.0, waitTimeAverage = 0.0,
           responseTimeAverage = 0.0;
    int qtdProcess = processStack.size();
    int clock = 0;

    while (!processStack.empty()) {
        Process process = processStack.front();
        processStack.pop();
        clock = clock == 0 ? process.arrivalTime : clock;
        int responseTime = clock - process.arrivalTime;
        int waitTime = responseTime;
        int finishTime = responseTime + process.duration;
#ifdef VERBOSE
        std::cout << "Process: " << processFinishTime << " "
                  << processResponseTime << " " << processWaitTime << std::endl;
#endif
        clock += process.duration;

        finishTimeAverage += finishTime;
        responseTimeAverage += responseTime;
        waitTimeAverage += waitTime;
    }
    finishTimeAverage /= qtdProcess;
    responseTimeAverage /= qtdProcess;
    waitTimeAverage /= qtdProcess;

    std::cout << std::setprecision(1) << std::fixed;

    std::cout << "FCFS: " << finishTimeAverage << " " << responseTimeAverage
              << " " << waitTimeAverage << std::endl;
}
