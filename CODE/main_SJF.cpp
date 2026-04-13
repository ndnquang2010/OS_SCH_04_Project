#include <iostream>
#include "sjf.h"
#include "csv.h"

using namespace std;

int main() {
    //B1: Đọc file CSV
    vector<Process> p = readCSV("input.csv");

    //kiểm tra đọc có thành công không
    if (p.empty()) {
        cout << "Khong doc duoc file CSV!\n";
        return 1;
    }

    //B2: Chạy thuật toán SJF
    vector<Process> result = sjf(p);

    //B3: In kết quả
    cout << "Result:\n";
    for (auto &x : result) {
        cout << x.id << "\t"
             << "ST=" << x.st << "\t"
             << "CT=" << x.ct << "\t"
             << "WT=" << x.wt << "\t"
             << "TAT=" << x.tat << endl;
    }
    return 0;
}