
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_tm()
{
    ui->setupUi(this);

    m_classTester = new testClass(true);
}

MainWindow::~MainWindow()
{
    delete ui;

    if(m_classTester != nullptr)
        delete m_classTester;

}

void MainWindow::on_pushButtonStart_clicked()
{
    m_tm.start();
    testFunction();
    m_tm.end();
    double timeElapsed = m_tm.timeElapsed_inMilliseconds();
    ui->lineEditDiff->setText(QString::number(timeElapsed));
}

void MainWindow::testFunction()
{
    bool flag = !(*m_classTester);
    if (flag)
    {
        int retVal = ~(*m_classTester);
        ui->lineEditStart->setText(QString::number(retVal));
    }
    Sleep(123);
}

void MainWindow::timeMeasure::start()
{
    m_start = std::chrono::steady_clock::now();
}

void MainWindow::timeMeasure::end()
{
    m_end = std::chrono::steady_clock::now();
}

double MainWindow::timeMeasure::timeElapsed_inMilliseconds()
{
    m_end = std::chrono::steady_clock::now();
    m_difference = m_end - m_start;
    return std::chrono::duration_cast<std::chrono::milliseconds>(m_difference).count();
}

double MainWindow::timeMeasure::timeElapsed_inNanoseconds()
{
    m_end = std::chrono::steady_clock::now();
    m_difference = m_end - m_start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(m_difference).count();
}
