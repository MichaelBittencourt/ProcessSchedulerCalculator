#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>

using namespace std;

class Process {
  private:
    int _arrivalTime;
    int _duration;
    int _quantum;
    int id;
    int responseTime;
    int waitTime;
    int finishTime;
    static int GLOBAL_ID;
    void addWaitTime(int lastWaitTime);
    void setResponseTime(int responseTime);
    void addFinishTime(int timeAmount);
    void subDuration(int timeAmount);
    void subQuantum(int timeAmount);

  public:
    Process(int arrivalTime, int duration);
    Process(int arrivalTime, int duration, int quantum);
    Process();
    ~Process();

    bool operator<(const Process &process) const;
    friend ostream &operator<<(ostream &os, const Process &process);
    void run(int clock);
    void run(int clock, int quantum);
    int getArrivalTime() const;
    int getDuration() const;
    int getId() const;
    bool alreadyResponse() const;
    int getResponseTime() const;
    void runningOneTime();
    int getWaitTime() const;
    int getFinishTime() const;
    int getQuantum() const;
    void setArrivalTime(int arrivalTime);
    void setQuantum(int quantum);
    bool isFinish();
    bool isFinishQuantum();

    static int getGlobalId();
};

#endif
