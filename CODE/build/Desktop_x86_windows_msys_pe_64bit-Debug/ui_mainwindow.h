/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTableWidget *tableInput;
    QTableWidget *tableOutput;
    QComboBox *comboAlgo;
    QPushButton *btnLoad;
    QPushButton *btnRun;
    QPushButton *btnExport;
    QLabel *labelResult;
    QLabel *labelGantt;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1317, 679);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        tableInput = new QTableWidget(centralWidget);
        if (tableInput->columnCount() < 4)
            tableInput->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableInput->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableInput->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableInput->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableInput->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableInput->setObjectName("tableInput");
        tableInput->setGeometry(QRect(230, 80, 401, 291));
        tableOutput = new QTableWidget(centralWidget);
        if (tableOutput->columnCount() < 2)
            tableOutput->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableOutput->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableOutput->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        tableOutput->setObjectName("tableOutput");
        tableOutput->setGeometry(QRect(770, 80, 201, 281));
        comboAlgo = new QComboBox(centralWidget);
        comboAlgo->addItem(QString());
        comboAlgo->addItem(QString());
        comboAlgo->setObjectName("comboAlgo");
        comboAlgo->setGeometry(QRect(30, 220, 161, 51));
        comboAlgo->setFrame(false);
        btnLoad = new QPushButton(centralWidget);
        btnLoad->setObjectName("btnLoad");
        btnLoad->setGeometry(QRect(30, 80, 161, 51));
        btnRun = new QPushButton(centralWidget);
        btnRun->setObjectName("btnRun");
        btnRun->setGeometry(QRect(30, 150, 161, 51));
        btnExport = new QPushButton(centralWidget);
        btnExport->setObjectName("btnExport");
        btnExport->setGeometry(QRect(40, 500, 141, 71));
        labelResult = new QLabel(centralWidget);
        labelResult->setObjectName("labelResult");
        labelResult->setGeometry(QRect(250, 30, 121, 31));
        labelGantt = new QLabel(centralWidget);
        labelGantt->setObjectName("labelGantt");
        labelGantt->setGeometry(QRect(210, 410, 881, 131));
        QFont font;
        font.setPointSize(20);
        labelGantt->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1317, 17));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableInput->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Process", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableInput->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Arrival", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableInput->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Burst", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableInput->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Priority", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableOutput->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Waiting", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableOutput->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Turnaround", nullptr));
        comboAlgo->setItemText(0, QCoreApplication::translate("MainWindow", "SJF", nullptr));
        comboAlgo->setItemText(1, QCoreApplication::translate("MainWindow", "Priority", nullptr));

        btnLoad->setText(QCoreApplication::translate("MainWindow", "Load CSV", nullptr));
        btnRun->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        btnExport->setText(QCoreApplication::translate("MainWindow", "Export CSV", nullptr));
        labelResult->setText(QCoreApplication::translate("MainWindow", "Result will be shown here", nullptr));
        labelGantt->setText(QCoreApplication::translate("MainWindow", "Gantt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
