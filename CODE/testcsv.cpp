#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    ifstream file("input.csv");
    string line;

    // Bỏ dòng tiêu đề
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string process, arrival, burst, priority;

        getline(ss, process, ',');
        getline(ss, arrival, ',');
        getline(ss, burst, ',');
        getline(ss, priority, ',');

        cout << process << " | "
             << arrival << " | "
             << burst << " | "
             << priority << endl;
    }

    file.close();
    return 0;
}
