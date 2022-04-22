#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "process.h"
#include <list>
#include <queue>
#include <string>
#include <vector>

class RoundRobin {
  private:
    std::list<Process> _processList;
    std::queue<Process *> processQueue;
    std::list<Process>::iterator newProcess;
    int _quantum;
    int _clock;
    double finishTime;
    double responseTime;
    double waitTime;
    bool processRunning;
    Process *running;

  protected:
    virtual void push(Process *process);
    virtual Process *pop();
    virtual bool isQueueEmpty();
    virtual Process *getNextProcess();
    virtual bool isFinishScheduler();
    virtual bool thereNewProcess();
    virtual string classString();
    void setClock(int clock);
    int getClock();

  public:
    RoundRobin(std::list<Process> processList, int quantum);
    ~RoundRobin();

    void cleanMetrics();
    virtual void run();
    virtual void showAverageMetrics();
    virtual vector<double> getAverageMetrics();
    int getQtdProcess();
    bool isProcessRuning();
};

void round_robin(std::list<Process> processList, int quantum);

#endif
