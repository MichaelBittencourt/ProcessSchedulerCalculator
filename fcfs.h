#ifndef FCFS_H
#define FCFS_H

#include "process.h"
#include "rr.h"
#include <list>

class Fcfs : public RoundRobin {
  protected:
    virtual string classString();

  public:
    Fcfs(std::list<Process> processList);
};

#endif
