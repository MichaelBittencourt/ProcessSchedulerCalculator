#include "fcfs.h"
#include "process.h"
#include "rr.h"
//#include "sjf.h"
#include <iostream>
#include <limits>
#include <list>

using namespace std;

int main() {
    int qtdProcess = 0;
    int quantum = 0;
    list<Process> processList;
#ifdef VERBOSE
    cout << "Reading Process Quantity" << endl;
#endif
    cin >> qtdProcess >> quantum;
    for (int i = 0; i < qtdProcess; i++) {
#ifdef VERBOSE
        cout << "Reading process: " << i << endl;
#endif
        int arrivalTime = 0;
        int duration = 0;
        cin >> arrivalTime >> duration;
        processList.push_back(Process(arrivalTime, duration));
    }
#ifdef VERBOSE
    cout << "Starting fcfs" << endl;
#endif
    // fcfs(processList);
    Fcfs fcfs(processList);
    fcfs.run();
    fcfs.showAverageMetrics();
#ifdef VERBOSE
    cout << "Starting sjf: " << endl;
#endif
    // sjf(processList);
#ifdef VERBOSE
    cout << "Starting round_robin: " << endl;
#endif
    // To do round_robin work equal the fcfs you only need set quantum to
    // infinity, that in integer we can set as max integer
    // round_robin(processList, std::numeric_limits<int>::max());
    RoundRobin rr(processList, quantum);
    rr.run();
    rr.showAverageMetrics();
}
