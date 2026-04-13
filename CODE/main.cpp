#include "SJF.h"
#include "priority.h"

int main() {
    string filename = "input.csv";

    vector<ProcessPrio> processes = readProcessesFromCSV(filename);

    if (processes.empty()) {
        cout << "No process data found!" << endl;
        return 1;
    }

    priorityScheduling(processes);
    //printResults(processes);

    return 0;
}