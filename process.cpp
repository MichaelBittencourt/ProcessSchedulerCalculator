#include "process.h"

bool Process::operator<(const Process &process) const {
    return !(duration < process.duration);
}

Process createProcess(int arrivalTime, int duration, int id) {
    Process ret;
    ret.arrivalTime = arrivalTime;
    ret.duration = duration;
    ret.id = id;
    return ret;
}
