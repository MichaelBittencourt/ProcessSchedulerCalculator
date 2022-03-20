#include "process.h"

Process createProcess(int arrivalTime, int duration) {
    Process ret;
    ret.arrivalTime = arrivalTime;
    ret.duration = duration;
    return ret;
}
