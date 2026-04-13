#include "SJF.h"
#include <climits>

vector<Process> sjf(vector<Process> p) {
    int n = p.size();
    int current_time = 0;
    int completed = 0;

    vector<bool> done(n, false);

    while (completed < n) {
        int idx = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= current_time) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        p[idx].st = current_time;
        p[idx].ct = p[idx].st + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        current_time = p[idx].ct;
        done[idx] = true;
        completed++;
    }

    return p;
}
