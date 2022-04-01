#include "fcfs.h"
#include "process.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <unistd.h>

void fcfs(std::list<Process> processList) {
    double finishTimeAverage = 0.0, waitTimeAverage = 0.0,
           responseTimeAverage = 0.0;
    int qtdProcess = processList.size();
    std::queue<Process> processQueue;
    bool processRunning = false;
    int actualQuantum = 0;
    bool addProcessOnNextInteraction = false;

    Process running;
    std::list<Process>::iterator it = processList.begin();
    for (int clock = 0; clock < std::numeric_limits<int>::max(); clock++) {

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
        if (addProcessOnNextInteraction) {
#ifdef VERBOSE
            std::cout << "Process: " << running.id << " added on queue again!"
                      << std::endl;
#endif
            running.arrivalTime = clock;
            processQueue.push(running);
            addProcessOnNextInteraction = false;
        }
        if (!processRunning) {
            if (!processQueue.empty()) {
                running = processQueue.front();
                processQueue.pop();
                processRunning = true;
                actualQuantum = std::numeric_limits<int>::max();
                runProcess(&running, clock);
#ifdef VERBOSE
                std::cout << "Start running!" << std::endl;
                showProcessInfo(&running);
                std::cout << "Quantum: " << actualQuantum << std::endl;
#endif
            } else {
                if (it == processList.end()) {
                    break;
                }
            }
        }
        // I change to not use else because after set processRunning to true the
        // first if also need run this code block
        if (processRunning) {
#ifdef VERBOSE
            std::cout << "Running!" << std::endl;
            showProcessInfo(&running);
            std::cout << "Quantum: " << actualQuantum << std::endl;
#endif
            runningOneTime(&running);
            actualQuantum--;
            if (running.duration == 0) {
                processRunning = false;
                finishTimeAverage += running.finishTime;
                responseTimeAverage += running.responseTime;
                waitTimeAverage += running.waitTime;
#ifdef VERBOSE
                std::cout << "Finish process!" << std::endl;
                showProcessInfo(&running);
#endif
            } else {
                if (actualQuantum == 0) {
#ifdef VERBOSE
                    std::cout << "Mark to add process on Queue again!"
                              << std::endl;
                    showProcessInfo(&running);
                    std::cout << "Quantum: " << actualQuantum << std::endl;
#endif
                    addProcessOnNextInteraction = true;
                    processRunning = false;
                }
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
