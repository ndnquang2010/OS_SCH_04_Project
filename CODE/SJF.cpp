#include "SJF.h"
#include <iostream>
#include <iomanip>
#include <climits>
#include <algorithm>

void sjfScheduling(std::vector<Process>& processes) {
    int n = processes.size();
    if (n == 0) return;

    int currentTime = 0;
    int completedCount = 0;

    // Reset trạng thái (tránh lỗi nếu chạy lại)
    for (auto &p : processes) {
        p.completed = false;
    }

    while (completedCount < n) {
        int selected = -1;

        // Tìm process có burstTime nhỏ nhất
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
                if (selected == -1 ||
                    processes[i].burstTime < processes[selected].burstTime ||
                    (processes[i].burstTime == processes[selected].burstTime &&
                     processes[i].arrivalTime < processes[selected].arrivalTime) ||
                    (processes[i].burstTime == processes[selected].burstTime &&
                     processes[i].arrivalTime == processes[selected].arrivalTime &&
                     processes[i].id < processes[selected].id)) {
                    selected = i;
                }
            }
        }

        // Nếu chưa có process nào đến → nhảy tới process gần nhất
        if (selected == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!processes[i].completed) {
                    nextArrival = std::min(nextArrival, processes[i].arrivalTime);
                }
            }
            currentTime = nextArrival;
            continue;
        }

        // Thực thi process
        processes[selected].startTime = currentTime;
        processes[selected].finishTime =
            processes[selected].startTime + processes[selected].burstTime;

        processes[selected].turnaroundTime =
            processes[selected].finishTime - processes[selected].arrivalTime;

        processes[selected].waitingTime =
            processes[selected].turnaroundTime - processes[selected].burstTime;

        currentTime = processes[selected].finishTime;
        processes[selected].completed = true;
        completedCount++;
    }
}

void printSJFResults(const std::vector<Process>& processes) {
    std::cout << "ID\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\n";
    for (const auto& p : processes) {
        std::cout << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime
                  << "\t" << p.startTime << "\t" << p.finishTime
                  << "\t" << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }
}

void printGanttSJF(std::vector<Process> p) {
    // Sắp xếp theo startTime để in Gantt
    std::sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.startTime < b.startTime;
    });

    std::cout << "Gantt Chart (SJF):\n";
    for (const auto& proc : p) {
        std::cout << "[" << proc.id << ": " << proc.startTime << " - " << proc.finishTime << "] ";
    }
    std::cout << "\n";
}
