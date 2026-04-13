#ifndef SJF_H
#define SJF_H

#include <vector>
#include <string>
using namespace std;

struct Process {
    string id;
    int at, bt;
    int st, ct, wt, tat;
};

vector<Process> sjf(vector<Process> p);

#endif