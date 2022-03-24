#include "sjf.h"
#include <iomanip>
#include <iostream>
#include <queue>
#include <unistd.h>

void sjf(std::list<Process> processList) {
    double finishTimeAverage = 0.0, waitTimeAverage = 0.0,
           responseTimeAverage = 0.0;
    int qtdProcess = processList.size();
    std::priority_queue<Process> processQueue;
    bool processRunning = false;

    Process running;
    int finishTime = 0;
    int responseTime = 0;
    int waitTime = 0;
    std::list<Process>::iterator it = processList.begin();
    for (int clock = 0; true; clock++) {
        sleep(1);

#ifdef VERBOSE
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
                running = processQueue.top();
                processQueue.pop();
                processRunning = true;
                responseTime = clock - running.arrivalTime;
                waitTime = responseTime;
                finishTime = responseTime;
#ifdef VERBOSE
                std::cout << "Process " << running.id << ": ["
                          << running.duration << "] Start running!"
                          << std::endl;
                std::cout << "Process: " << finishTime << " " << responseTime
                          << " " << waitTime << std::endl;
#endif
                finishTime++;
                running.duration--;
            } else {
                if (it == processList.end()) {
                    break;
                }
            }
        } else {
#ifdef VERBOSE
            std::cout << "Process " << running.id << ": [" << running.duration
                      << "] running!" << std::endl;
            std::cout << "Process: " << finishTime << " " << responseTime << " "
                      << waitTime << std::endl;
#endif
            running.duration--;
            finishTime++;
            if (running.duration == 0) {
                processRunning = false;
                finishTimeAverage += finishTime;
                responseTimeAverage += responseTime;
                waitTimeAverage += waitTime;
#ifdef VERBOSE
                std::cout << "Process " << running.id << ": ["
                          << running.duration << "] finish!" << std::endl;
                std::cout << "Process: " << finishTime << " " << responseTime
                          << " " << waitTime << std::endl;
#endif
                finishTime = 0;
                responseTime = 0;
                waitTime = 0;
                continue;
            }
        }
    }

    finishTimeAverage /= qtdProcess;
    responseTimeAverage /= qtdProcess;
    waitTimeAverage /= qtdProcess;

    std::cout << std::setprecision(1) << std::fixed;

    std::cout << "SJF: " << finishTimeAverage << " " << responseTimeAverage
              << " " << waitTimeAverage << std::endl;
}
