#include "fcfs.h"
#include "process.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <unistd.h>

Fcfs::Fcfs(std::list<Process> processList)
    : RoundRobin::RoundRobin(processList, std::numeric_limits<int>::max()) {}

string Fcfs::classString() { return "FCFS"; }
