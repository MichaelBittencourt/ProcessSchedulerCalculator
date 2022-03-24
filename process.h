#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int arrivalTime;
    int duration;
    int id;

    bool operator<(const Process &process) const;
};

Process createProcess(int arrivalTime, int duration, int id);

#endif
