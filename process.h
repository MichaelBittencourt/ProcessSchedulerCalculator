#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int arrivalTime;
    int duration;
    int id;
    bool response;
    int responseTime;
    int waitTime;
    int finishTime;

    bool operator<(const Process &process) const;
};

Process createProcess(int arrivalTime, int duration, int id);

void runProcess(Process *process, int clock);

void runningOneTime(Process *process);

void showProcessInfo(const Process *process);

#endif
