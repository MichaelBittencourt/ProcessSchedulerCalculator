#include "fcfs.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <unistd.h>

void round_robin(std::list<Process> processList, int quantum) {
    double finishTimeAverage = 0.0, waitTimeAverage = 0.0,
           responseTimeAverage = 0.0;
    int qtdProcess = processList.size();
    std::queue<Process *> processQueue;
    bool processRunning = false;
    bool addProcessOnNextInteraction = false;

    Process *running = nullptr;
    std::list<Process>::iterator it = processList.begin();
    for (int clock = 0; clock < std::numeric_limits<int>::max(); clock++) {

#ifdef VERBOSE
        sleep(1);
        std::cout << "clock: " << clock << std::endl;
#endif
        while (it != processList.end() && clock == (*it).getArrivalTime()) {
#ifdef VERBOSE
            std::cout << "Process: " << (*it).id << " added on queue!"
                      << std::endl;
#endif
            processQueue.push(&(*it));
            it++;
        }
        if (addProcessOnNextInteraction) {
#ifdef VERBOSE
            std::cout << "Process: " << running->getId()
                      << " added on queue again!" << std::endl;
#endif
            running->setArrivalTime(clock);
            processQueue.push(running);
            addProcessOnNextInteraction = false;
        }
        if (!processRunning) {
            if (!processQueue.empty()) {
                running = processQueue.front();
                processQueue.pop();
                processRunning = true;
                running->run(clock, quantum);
#ifdef VERBOSE
                std::cout << "Start running!" << std::endl;
                std::cout << (*running) << std::endl;
                std::cout << "Quantum: " << running->getQuantum() << std::endl;
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
            std::cout << (*running) << std::endl;
            std::cout << "Quantum: " << running->getQuantum() << std::endl;
#endif
            running->runningOneTime();
            if (running->isFinish()) {
                processRunning = false;
                finishTimeAverage += running->getFinishTime();
                responseTimeAverage += running->getResponseTime();
                waitTimeAverage += running->getWaitTime();
#ifdef VERBOSE
                std::cout << "Finish process!" << std::endl;
                showProcessInfo(&running);
#endif
            } else {
                if (running->isFinishQuantum()) {
#ifdef VERBOSE
                    std::cout << "Mark to add process on Queue again!"
                              << std::endl;
                    std::cout << (*running) << std::endl;
                    std::cout << "Quantum: " << running->getQuantum()
                              << std::endl;
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
