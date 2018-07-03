#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>
#include <QMainWindow>
#include <chrono>
#include <ctime>


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
    void on_pushButtonStart_clicked();

private:

    Ui::MainWindow *ui;


    void testFunction();


    class testClass
    {
    public:
        testClass(bool cokState) { m_cok = cokState; }
        bool m_cok = false;
        bool operator !() { return m_cok; }
        int  operator ~() { return rand(); }
    };


    class timeMeasure
    {
    public:
        void start();
        void end();
        double timeElapsed_inMilliseconds();
        double timeElapsed_inNanoseconds();
    private:
        std::chrono::steady_clock::time_point   m_start;
        std::chrono::steady_clock::time_point   m_end;
        std::chrono::duration<double>           m_difference;
    };

    testClass* m_classTester = nullptr;

    timeMeasure  m_tm;
};

#endif // MAINWINDOW_H
