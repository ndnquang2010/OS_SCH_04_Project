#ifndef GANTT_H
#define GANTT_H

#include <vector>
#include <string>
#include "scheduler.h"

using namespace std;

struct GanttBlock {
    string name;
    int start;
    int end;
};

// Tạo Gantt từ processes
vector<GanttBlock> generateGantt(const vector<Process>& processes);

// In Gantt ra console
void printGantt(const vector<GanttBlock>& gantt);

#endif