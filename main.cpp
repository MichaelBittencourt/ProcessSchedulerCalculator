#include "fcfs.h"
#include "process.h"
#include "rr.h"
#include "sjf.h"
#include <iostream>
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
        processList.push_back(createProcess(arrivalTime, duration, i));
    }
#ifdef VERBOSE
    cout << "Starting fcfs" << endl;
#endif
    fcfs(processList);
#ifdef VERBOSE
    cout << "Starting sjf: " << endl;
#endif
    sjf(processList);
#ifdef VERBOSE1
    cout << "Starting round_robin: " << endl;
#endif
    round_robin(processList, quantum);
}
