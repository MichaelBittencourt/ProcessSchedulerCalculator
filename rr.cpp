#include "rr.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <unistd.h>

RoundRobin::RoundRobin(std::list<Process> processList, int quantum)
    : _processList(processList), _quantum(quantum), finishTime(0.0),
      responseTime(0.0), waitTime(0.0), processRunning(false),
      running(nullptr) {}

RoundRobin::~RoundRobin() { running = nullptr; }

void RoundRobin::cleanMetrics() { finishTime = waitTime = responseTime = 0.0; }

int RoundRobin::getQtdProcess() { return _processList.size(); }

vector<double> RoundRobin::getAverageMetrics() {
    vector<double> ret(3);
    ret[0] = (this->finishTime /= this->getQtdProcess());
    ret[1] = (this->responseTime /= this->getQtdProcess());
    ret[2] = (this->waitTime /= this->getQtdProcess());
    return ret;
}

void RoundRobin::showAverageMetrics() {
    vector<double> metrics = getAverageMetrics();

    std::cout << std::setprecision(1) << std::fixed;

    std::cout << "RR:";
    for (vector<double>::iterator it = metrics.begin(); it != metrics.end();
         it++) {
        cout << " " << (*it);
    }
    cout << std::endl;
}

void RoundRobin::run() {
    std::queue<Process *> processQueue;
    bool addProcessOnNextInteraction = false;

    std::list<Process>::iterator it = _processList.begin();
    for (int clock = 0; clock < std::numeric_limits<int>::max(); clock++) {

#ifdef VERBOSE
        sleep(1);
        std::cout << "clock: " << clock << std::endl;
#endif
        while (it != _processList.end() && clock == (*it).getArrivalTime()) {
#ifdef VERBOSE
            std::cout << "Process: " << (*it).getId() << " added on queue!"
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
                running->run(clock, _quantum);
#ifdef VERBOSE
                std::cout << "Start running!" << std::endl;
                std::cout << (*running) << std::endl;
                std::cout << "Quantum: " << running->getQuantum() << std::endl;
#endif
            } else {
                if (it == _processList.end()) {
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
                finishTime += running->getFinishTime();
                responseTime += running->getResponseTime();
                waitTime += running->getWaitTime();
#ifdef VERBOSE
                std::cout << "Finish process!" << std::endl;
                std::cout << (*running) << std::endl;
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
}
