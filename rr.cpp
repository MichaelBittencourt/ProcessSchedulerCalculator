#include "rr.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <unistd.h>

string RoundRobin::classString() { return "RR"; }

RoundRobin::RoundRobin(std::list<Process> processList, int quantum)
    : _processList(processList), _quantum(quantum), finishTime(0.0),
      responseTime(0.0), waitTime(0.0), processRunning(false), running(nullptr),
      newProcess(_processList.begin()) {}

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

    std::cout << classString() << ":";
    for (vector<double>::iterator it = metrics.begin(); it != metrics.end();
         it++) {
        cout << " " << (*it);
    }
    cout << std::endl;
}

void RoundRobin::run() {
    bool addProcessOnNextInteraction = false;

    for (setClock(0); getClock() < std::numeric_limits<int>::max();
         setClock(getClock() + 1)) {

#ifdef VERBOSE
        sleep(1);
        std::cout << "clock: " << getClock() << std::endl;
#endif
        while (!isFinishScheduler() && thereNewProcess()) {
            Process *process = getNextProcess();
#ifdef VERBOSE
            std::cout << "Process: " << process->getId() << " added on queue!"
                      << std::endl;
#endif
            this->push(process);
        }
        if (addProcessOnNextInteraction) {
#ifdef VERBOSE
            std::cout << "Process: " << running->getId()
                      << " added on queue again!" << std::endl;
#endif
            running->setArrivalTime(getClock());
            this->push(running);
            addProcessOnNextInteraction = false;
        }
        if (!processRunning) {
            if (!isQueueEmpty()) {
                running = this->pop();
                processRunning = true;
                running->run(getClock(), _quantum);
#ifdef VERBOSE
                std::cout << "Start running!" << std::endl;
                std::cout << (*running) << std::endl;
                std::cout << "Quantum: " << running->getQuantum() << std::endl;
#endif
            } else {
                if (isFinishScheduler()) {
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

void RoundRobin::push(Process *process) { processQueue.push(process); }

Process *RoundRobin::pop() {
    Process *ret = processQueue.front();
    processQueue.pop();
    return ret;
}

bool RoundRobin::isQueueEmpty() { return processQueue.empty(); }

bool RoundRobin::isFinishScheduler() {
    return newProcess == _processList.end();
}

int RoundRobin::getClock() { return _clock; }

void RoundRobin::setClock(int clock) { _clock = clock; }

bool RoundRobin::thereNewProcess() {
    return getClock() == (*newProcess).getArrivalTime();
}

Process *RoundRobin::getNextProcess() {
    Process *ret = &(*newProcess);
    newProcess++;
    return ret;
}
