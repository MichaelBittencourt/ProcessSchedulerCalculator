#include "sjf.h"
#include <iomanip>
#include <iostream>
#include <queue>
#include <unistd.h>

Sjf::Sjf(std::list<Process> processList) : Fcfs::Fcfs(processList) {}

void Sjf::push(Process *process) { processQueue.push(*process); }

string Sjf::classString() { return "SJF"; }

Process *Sjf::pop() {
    topQueue = processQueue.top();
    processQueue.pop();
    return &topQueue;
}

bool Sjf::isQueueEmpty() { return processQueue.empty(); }
