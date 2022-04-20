#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "process.h"
#include <list>
#include <vector>

class RoundRobin {
  private:
    std::list<Process> _processList;
    int _quantum;
    double finishTime;
    double responseTime;
    double waitTime;
    bool processRunning;
    Process *running;

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
