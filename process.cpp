#include "process.h"

#include <iostream>
#include <limits>

int Process::GLOBAL_ID = 1;

int Process::getGlobalId() { return GLOBAL_ID++; }

bool Process::operator<(const Process &process) const {
    return !(this->getDuration() < process.getDuration());
}

Process::Process(int arrivalTime, int duration, int quantum)
    : _arrivalTime(arrivalTime), _duration(duration), _quantum(quantum),
      responseTime(-1), waitTime(0), finishTime(0), id(Process::getGlobalId()) {
}

Process::~Process() {}

Process::Process(int arrivalTime, int duration)
    : Process(arrivalTime, duration, numeric_limits<int>::max()) {}

int Process::getDuration() const { return _duration; }

void Process::run(int clock, int quantum) {
    int lastWaitTime = clock - this->getArrivalTime();
    this->addWaitTime(lastWaitTime);
    if (!this->alreadyResponse()) {
        this->setResponseTime(lastWaitTime);
    }
    this->addFinishTime(lastWaitTime);
    this->setQuantum(quantum);
}

void Process::run(int clock) { run(clock, numeric_limits<int>::max()); }

void Process::addWaitTime(int lastWaitTime) { this->waitTime += lastWaitTime; }

void Process::setResponseTime(int timeAmount) { responseTime = timeAmount; }

void Process::addFinishTime(int timeAmount) { this->finishTime += timeAmount; }

bool Process::alreadyResponse() const {
    return !(this->getResponseTime() == -1);
}

int Process::getArrivalTime() const { return _arrivalTime; }
int Process::getId() const { return id; }
int Process::getResponseTime() const { return responseTime; }

void Process::runningOneTime() {
    this->addFinishTime(1);
    this->subDuration(1);
    this->subQuantum(1);
}

void Process::subDuration(int timeAmount) { this->_duration -= timeAmount; }
void Process::subQuantum(int timeAmount) { this->_quantum -= timeAmount; }

ostream &operator<<(ostream &os, const Process &process) {
    os << "Process " << process.getId() << " response("
       << process.alreadyResponse() << "): [" << process.getArrivalTime() << " "
       << process.getDuration() << " " << process.getResponseTime() << " "
       << process.getWaitTime() << " " << process.getFinishTime() << "]"
       << std::endl;
    return os;
}

int Process::getWaitTime() const { return waitTime; }
int Process::getFinishTime() const { return finishTime; }
void Process::setArrivalTime(int arrivalTime) { _arrivalTime = arrivalTime; }
int Process::getQuantum() const { return _quantum; }
void Process::setQuantum(int quantum) { _quantum = quantum; }
bool Process::isFinish() { return getDuration() <= 0; }
bool Process::isFinishQuantum() { return getQuantum() <= 0; }
