#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboAlgo->addItems({"FCFS","SJF","Priority"});

    ui->tableInput->setColumnCount(4);
    ui->tableInput->setHorizontalHeaderLabels({"Process","Arrival","Burst","Priority"});

    ui->tableOutput->setColumnCount(2);
    ui->tableOutput->setHorizontalHeaderLabels({"Waiting","Turnaround"});
}

MainWindow::~MainWindow()
{
    delete ui;
}

// LOAD CSV (NHẬN FILE DỮ LIỆU ĐẦU VÀO)
void MainWindow::on_btnLoad_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open CSV", "", "*.csv");

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) return;

    QTextStream in(&file);
    ui->tableInput->setRowCount(0);

    int row = 0;
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList data = line.split(",");

        ui->tableInput->insertRow(row);
        for(int i=0;i<data.size();i++){
            ui->tableInput->setItem(row,i,new QTableWidgetItem(data[i]));
        }
        row++;
    }
    file.close();
}

// RUN CHẠY THUẬT TOÁN
void MainWindow::on_btnRun_clicked()
{
    QString algo = ui->comboAlgo->currentText();

    if(algo == "FCFS") runFCFS();
    else if(algo == "SJF") runSJF();
    else runPriority();
}

// FCFS THUẬT TOÁN
void MainWindow::runFCFS()
{
    int n = ui->tableInput->rowCount();

    vector<int> arrival(n), burst(n), waiting(n), turnaround(n);
    vector<int> order, timeline, idx(n);

    for(int i=0;i<n;i++){
        arrival[i] = ui->tableInput->item(i,1)->text().toInt();
        burst[i] = ui->tableInput->item(i,2)->text().toInt();
        idx[i] = i;
    }

    sort(idx.begin(), idx.end(), [&](int a,int b){
        return arrival[a] < arrival[b];
    });

    int time = 0;

    for(int i=0;i<n;i++){
        int id = idx[i];

        if(time < arrival[id]) time = arrival[id];

        order.push_back(id);
        timeline.push_back(time);

        waiting[id] = time - arrival[id];
        time += burst[id];
        turnaround[id] = waiting[id] + burst[id];
    }

    timeline.push_back(time);
    showResult(waiting, turnaround, "FCFS", order, timeline);
}

// SJF THUẬT TOÁN
void MainWindow::runSJF()
{
    int n = ui->tableInput->rowCount();

    vector<int> arrival(n), burst(n), waiting(n,0), turnaround(n,0);
    vector<bool> done(n,false);

    vector<int> order, timeline;

    for(int i=0;i<n;i++){
        arrival[i] = ui->tableInput->item(i,1)->text().toInt();
        burst[i] = ui->tableInput->item(i,2)->text().toInt();
    }

    int time = 0, completed = 0;

    while(completed < n){
        int idx = -1, minBurst = 1e9;

        for(int i=0;i<n;i++){
            if(!done[i] && arrival[i] <= time){
                if(burst[i] < minBurst){
                    minBurst = burst[i];
                    idx = i;
                }
            }
        }

        if(idx == -1){
            time++;
            continue;
        }

        order.push_back(idx);
        timeline.push_back(time);

        waiting[idx] = time - arrival[idx];
        time += burst[idx];
        turnaround[idx] = waiting[idx] + burst[idx];

        done[idx] = true;
        completed++;
    }

    timeline.push_back(time);
    showResult(waiting, turnaround, "SJF", order, timeline);
}

// PRIORITY THUẬT TOÁN
void MainWindow::runPriority()
{
    int n = ui->tableInput->rowCount();

    vector<int> arrival(n), burst(n), priority(n);
    vector<int> waiting(n,0), turnaround(n,0);
    vector<bool> done(n,false);

    vector<int> order, timeline;

    for(int i=0;i<n;i++){
        arrival[i] = ui->tableInput->item(i,1)->text().toInt();
        burst[i] = ui->tableInput->item(i,2)->text().toInt();
        priority[i] = ui->tableInput->item(i,3)->text().toInt();
    }

    int time = 0, completed = 0;

    while(completed < n){
        int idx = -1, best = 1e9;

        for(int i=0;i<n;i++){
            if(!done[i] && arrival[i] <= time){
                if(priority[i] < best){
                    best = priority[i];
                    idx = i;
                }
            }
        }

        if(idx == -1){
            time++;
            continue;
        }

        order.push_back(idx);
        timeline.push_back(time);

        waiting[idx] = time - arrival[idx];
        time += burst[idx];
        turnaround[idx] = waiting[idx] + burst[idx];

        done[idx] = true;
        completed++;
    }

    timeline.push_back(time);
    showResult(waiting, turnaround, "Priority", order, timeline);
}

// HIỂN THỊ
void MainWindow::showResult(vector<int> waiting, vector<int> turnaround,
                           QString name,
                           vector<int> order,
                           vector<int> timeline)
{
    int n = waiting.size();
    ui->tableOutput->setRowCount(n);

    for(int i=0;i<n;i++){
        ui->tableOutput->setItem(i,0,new QTableWidgetItem(QString::number(waiting[i])));
        ui->tableOutput->setItem(i,1,new QTableWidgetItem(QString::number(turnaround[i])));
    }

    QString gantt = "";
    QString timeLine = "";

    for(int t : timeline){
        timeLine += QString::number(t) + "    ";
    }

    for(int i=0;i<order.size();i++){
        gantt += "| P" + QString::number(order[i]+1) + " ";
    }
    gantt += "|";

    ui->labelResult->setText(name + " done!");
    ui->labelGantt->setText(gantt + "\n" + timeLine);
}

// EXPORT XUẤT FILE
void MainWindow::on_btnExport_clicked()
{
    QFile file("output.csv");
    if(!file.open(QIODevice::WriteOnly)) return;

    QTextStream out(&file);

    int n = ui->tableOutput->rowCount();

    for(int i=0;i<n;i++){
        QString w = ui->tableOutput->item(i,0)->text();
        QString t = ui->tableOutput->item(i,1)->text();

        out << w << "," << t << "\n";
    }
    file.close();
}
