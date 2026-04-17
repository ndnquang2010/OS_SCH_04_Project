#include "gantt.h"
#include <algorithm>

vector<GanttBlock> generateGantt(const vector<Process>& processes) {
    vector<GanttBlock> gantt;

    // copy để sort
    vector<Process> temp = processes;

    sort(temp.begin(), temp.end(), [](Process a, Process b) {
        return a.startTime < b.startTime;
    });

    for (auto &p : temp) {
        gantt.push_back({p.name, p.startTime, p.finishTime});
    }

    return gantt;
}