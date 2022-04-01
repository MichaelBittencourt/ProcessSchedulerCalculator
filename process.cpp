#include "process.h"
#include <iostream>

bool Process::operator<(const Process &process) const {
    return !(duration < process.duration);
}

Process createProcess(int arrivalTime, int duration, int id) {
    Process ret;
    ret.arrivalTime = arrivalTime;
    ret.duration = duration;
    ret.id = id;
    ret.response = false;
    ret.responseTime = 0;
    ret.waitTime = 0;
    ret.finishTime = 0;
    return ret;
}

void runProcess(Process *process, int clock) {
    int lastWaitTime = clock - process->arrivalTime;
    process->waitTime += lastWaitTime;
    if (!process->response) {
        process->responseTime = lastWaitTime;
        process->response = true;
    }
    process->finishTime += lastWaitTime;
}

void runningOneTime(Process *process) {
    process->finishTime++;
    process->duration--;
}

void showProcessInfo(const Process *process) {
    std::cout << "Process " << process->id << " response(" << process->response
              << "): [" << process->arrivalTime << " " << process->duration
              << " " << process->responseTime << " " << process->waitTime << " "
              << process->finishTime << "]" << std::endl;
}
