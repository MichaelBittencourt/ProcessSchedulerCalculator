#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "process.h"
#include <list>

void round_robin(std::list<Process> processList, int quantum);

#endif
