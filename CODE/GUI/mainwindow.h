#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnLoad_clicked();
    void on_btnRun_clicked();
    void on_btnExport_clicked();

private:
    Ui::MainWindow *ui;

    void runFCFS();
    void runSJF();
    void runPriority();

    void showResult(vector<int> waiting, vector<int> turnaround,
                    QString name,
                    vector<int> order,
                    vector<int> timeline);
};

#endif // MAINWINDOW_H
