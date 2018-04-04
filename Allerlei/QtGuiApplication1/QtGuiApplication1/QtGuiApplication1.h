/*
  https://wiki.qt.io/QThreads_general_usage

*/

#pragma once

#include <QtWidgets/QMainWindow>
#include <chrono>

#include "Worker.h"
#include "ui_QtGuiApplication1.h"

class QtGuiApplication1 : public QMainWindow
{
    Q_OBJECT

public:
  QtGuiApplication1(QWidget *parent = Q_NULLPTR);
  ~QtGuiApplication1();

public slots:
    void on_pushButtonStartWorkers_clicked();

private slots:
    void onFinishedReceived(int numberOfWorker);
    void errorString(QString errorString);

private:
    Ui::QtGuiApplication1Class *ui;

    void initialize();
    void setupWorkers();
    void startAllWorkers();
    bool allWorkersAreFinished();
    void displayStatusMessage(QString str);

    std::chrono::steady_clock::time_point m_benchmarkStart;
    std::chrono::steady_clock::time_point m_benchmarkEnd;

    class WorkerData
    {
      public:
        Worker *pWorker = nullptr;
        QThread *pThread = nullptr;
        bool isWorking() { return working; }
        void setWorking() { working = true; }
        void resetWorking() { working = false; }
    private:
        bool working = false;
    };

    int m_doubleSpinValue = 0;

    std::vector<WorkerData> m_workerFarm;

    std::vector<int> myVector;
    std::vector<int> myBackupVector;

    int m_numberOfThreads;
};
