#ifndef SJF_H
#define SJF_H

#include "fcfs.h"
#include "process.h"
#include <list>
#include <queue>

class Sjf : public Fcfs {
  protected:
    std::priority_queue<Process> processQueue;
    virtual string classString();
    virtual void push(Process *process);
    virtual Process *pop();
    virtual bool isQueueEmpty();
    Process topQueue;

  public:
    Sjf(std::list<Process> processList);
};

#endif
