#include "fcfs.h"
#include <iomanip>
#include <iostream>
#include <queue>
#include <unistd.h>

void round_robin(std::list<Process> processList, int quantum) {
    double finishTimeAverage = 0.0, waitTimeAverage = 0.0,
           responseTimeAverage = 0.0;
    int qtdProcess = processList.size();
    std::queue<Process> processQueue;
    bool processRunning = false;
    int actualQuantum = 0;
    bool addProcessOnNextInteraction = false;

    Process running;
    std::list<Process>::iterator it = processList.begin();
    for (int clock = 0; true; clock++) {

#ifdef VERBOSE1
        // sleep(1);
        std::cout << "clock: " << clock << std::endl;
#endif
        while (it != processList.end() && clock == (*it).arrivalTime) {
#ifdef VERBOSE1
            std::cout << "Process: " << (*it).id << " added on queue!"
                      << std::endl;
#endif
            processQueue.push((*it));
            it++;
        }
        if (addProcessOnNextInteraction) {
#ifdef VERBOSE1
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
                actualQuantum = quantum;
                runProcess(&running, clock);
#ifdef VERBOSE1
                std::cout << "Start running!" << std::endl;
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
#ifdef VERBOSE1
                    std::cout << "Finish process!" << std::endl;
                    showProcessInfo(&running);
#endif
                } else {
                    if (actualQuantum == 0) {
#ifdef VERBOSE1
                        std::cout << "Mark to add process on Queue again!"
                                  << std::endl;
                        showProcessInfo(&running);
                        std::cout << "Quantum: " << actualQuantum << std::endl;
#endif
                        addProcessOnNextInteraction = true;
                        processRunning = false;
                    }
                }
            } else {
                if (it == processList.end()) {
                    break;
                }
            }
        } else {
#ifdef VERBOSE1
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
#ifdef VERBOSE1
                std::cout << "Finish process!" << std::endl;
                showProcessInfo(&running);
#endif
            } else {
                if (actualQuantum == 0) {
#ifdef VERBOSE1
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

    std::cout << "RR: " << finishTimeAverage << " " << responseTimeAverage
              << " " << waitTimeAverage << std::endl;
}
