#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <algorithm>
#include "SJF.h"
#include "Priority.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->comboAlgo->addItems({"SJF","Priority"});

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
    in.readLine(); 
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

int MainWindow::safeGetInt(int row, int col, int defaultVal)
{
    QTableWidgetItem* item = ui->tableInput->item(row, col);
    if(!item || item->text().trimmed().isEmpty())
        return defaultVal;
    return item->text().toInt();
}

void MainWindow::on_btnRun_clicked()
{
    QString algo = ui->comboAlgo->currentText();

    int n = ui->tableInput->rowCount();

    vector<int> waiting, turnaround, order, timeline;

    if(algo == "SJF")
    {
        vector<ProcessSJF> p;

        for(int i=0;i<n;i++){
            ProcessSJF pr;
            pr.nameSjf = "P" + to_string(i+1);
            pr.arrivalTimeSjf = safeGetInt(i, 1);
            pr.burstTimeSjf   = safeGetInt(i, 2);
            pr.originalIndexSjf  = i;
            p.push_back(pr);
        }

        sjfScheduling(p);

        // convert sang GUI
        for(int i=0;i<n;i++){
            waiting.push_back(p[i].waitingTimeSjf);
            turnaround.push_back(p[i].turnaroundTimeSjf);
            order.push_back(p[i].originalIndexSjf);
            timeline.push_back(p[i].startTimeSjf);
        }

        int lastFinish = 0;
        for(auto& pr : p){
            lastFinish = max(lastFinish, pr.finishTimeSjf);
        }
        timeline.push_back(lastFinish);

        showResult(waiting, turnaround, "SJF", order, timeline);
    }

    else if(algo == "Priority")
    {
        vector<ProcessPrio> p;

        for(int i=0;i<n;i++){
            ProcessPrio pr;
            pr.name = "P" + to_string(i+1);
            pr.arrivalTime = safeGetInt(i, 1);
            pr.burstTime   = safeGetInt(i, 2);
            pr.priority    = safeGetInt(i, 3);
            pr.originalIndex  = i;
            p.push_back(pr);
        }

        priorityScheduling(p);

        for(int i=0;i<n;i++){
            waiting.push_back(p[i].waitingTime);
            turnaround.push_back(p[i].turnaroundTime);
            order.push_back(p[i].originalIndex);
            timeline.push_back(p[i].startTime);
        }

        int lastFinish = 0;
        for(auto& pr : p){
            lastFinish = max(lastFinish, pr.finishTime);
        }
        timeline.push_back(lastFinish);

        showResult(waiting, turnaround, "Priority", order, timeline);
    }
}

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

    // Build Gantt với idle time
    QString gantt = "";
    QString timeLine = "";

    int currentTime = 0;

    for(int i = 0; i < (int)order.size(); i++){
        int start = timeline[i];

        //có khoảng trống chèn IDLE
        if(start > currentTime){
            gantt    += "| IDLE ";
            timeLine += QString::number(currentTime) + "    ";
        }

        gantt    += "| P" + QString::number(order[i]+1) + " ";
        timeLine += QString::number(start) + "    ";

        currentTime = timeline[i+1]; // finish time của process hiện tại
    }

    // Thêm dấu | điểm kết thúc
    gantt    += "|";
    timeLine += QString::number(timeline.back());

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
