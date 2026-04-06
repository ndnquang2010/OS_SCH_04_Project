#include <bits/stdc++.h>
using namespace std;

struct Process {
    string id;
    int at, bt;
    int st, ct, wt, tat;
    bool done = false;
};

vector<Process> sjf(vector<Process> p) {
    int n = p.size();
    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int min_bt = INT_MAX;

        // tìm process hợp lệ
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= current_time) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        // nếu không có process nào đến → nhảy thời gian
        if (idx == -1) {
            current_time++;
            continue;
        }

        // xử lý process được chọn
        p[idx].st = current_time;
        p[idx].ct = p[idx].st + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        current_time = p[idx].ct;
        p[idx].done = true;
        completed++;
    }

    return p;
}
