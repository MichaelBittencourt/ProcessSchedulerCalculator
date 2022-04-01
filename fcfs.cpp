#include "fcfs.h"
#include "process.h"
#include <iomanip>
#include <iostream>
#include <queue>
#include <unistd.h>

void fcfs(std::list<Process> processList) {
    double finishTimeAverage = 0.0, waitTimeAverage = 0.0,
           responseTimeAverage = 0.0;
    int qtdProcess = processList.size();
    std::queue<Process> processQueue;
    bool processRunning = false;

    Process running;
    std::list<Process>::iterator it = processList.begin();
    for (int clock = 0; true; clock++) {

#ifdef VERBOSE
        sleep(1);
        std::cout << "clock: " << clock << std::endl;
#endif
        while (it != processList.end() && clock == (*it).arrivalTime) {
#ifdef VERBOSE
            std::cout << "Process: " << (*it).id << " added on queue!"
                      << std::endl;
#endif
            processQueue.push((*it));
            it++;
        }
        if (!processRunning) {
            if (!processQueue.empty()) {
                running = processQueue.front();
                processQueue.pop();
                processRunning = true;
                runProcess(&running, clock);
#ifdef VERBOSE
                std::cout << "Start running!" << std::endl;
                showProcessInfo(&process);
#endif
                runningOneTime(&running);
            } else {
                if (it == processList.end()) {
                    break;
                }
            }
        } else {
#ifdef VERBOSE
            std::cout << "Running!" << std::endl;
            showProcessInfo(running;)
#endif
                runningOneTime(&running);
            if (running.duration == 0) {
                processRunning = false;
                finishTimeAverage += running.finishTime;
                responseTimeAverage += running.responseTime;
                waitTimeAverage += running.waitTime;
#ifdef VERBOSE
                std::cout << "Finish process!" << std::endl;
                showProcessInfo(&process);
#endif
            }
        }
    }

    finishTimeAverage /= qtdProcess;
    responseTimeAverage /= qtdProcess;
    waitTimeAverage /= qtdProcess;

    std::cout << std::setprecision(1) << std::fixed;

    std::cout << "FCFS: " << finishTimeAverage << " " << responseTimeAverage
              << " " << waitTimeAverage << std::endl;
}
