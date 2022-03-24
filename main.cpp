#include "fcfs.h"
#include "process.h"
#include <iostream>
#include <list>

using namespace std;

int main() {
    int qtdProcess = 0;
    list<Process> processList;
    cin >> qtdProcess;
    for (int i = 0; i < qtdProcess; i++) {
        int arrivalTime = 0;
        int duration = 0;
        cin >> arrivalTime >> duration;
        processList.push_back(createProcess(arrivalTime, duration, i));
    }
    fcfs(processList);
}
