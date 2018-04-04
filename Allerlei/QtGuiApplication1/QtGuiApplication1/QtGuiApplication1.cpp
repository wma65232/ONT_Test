/*

Aus Beispiel : 
  http://doc.qt.io/qtvstools/qtvstools-managing-projects.html#importing-and-exporting-projects

*/

#include "QtGuiApplication1.h"

// ------------------------------------------------------------------------------------------
QtGuiApplication1::QtGuiApplication1(QWidget *parent) : 
  QMainWindow(parent), 
  ui(new Ui::QtGuiApplication1Class),
  m_doubleSpinValue(100)
{
  ui->setupUi(this);
  initialize();
}

// ------------------------------------------------------------------------------------------
void QtGuiApplication1::initialize()
{
  m_numberOfThreads = QThread::idealThreadCount();
  
  ui->spinBoxNumberOfThreads->setValue(m_numberOfThreads);
  ui->spinBoxNumberOfBytesPerFile->setMaximum(100000000);
  ui->spinBoxNumberOfBytesPerFile->setValue(10000);

  QString str = QString(QString("Ideal Thread-Count = ") + QString::number(m_numberOfThreads));
  displayStatusMessage(str);
}

// ------------------------------------------------------------------------------------------
void QtGuiApplication1::setupWorkers()
{
  int cnt = 0;
  bool success = true;
  m_workerFarm.clear();

  m_numberOfThreads = ui->spinBoxNumberOfThreads->value();

  for (int i = 0; i != m_numberOfThreads; ++i)
  {
    QString str = QString(QString("creating worker instance...:") + QString::number(i));
    displayStatusMessage(str);

    WorkerData wd;
    wd.pWorker = new Worker(cnt++, ui->spinBoxNumberOfBytesPerFile->value());
    wd.pThread = new QThread;
    m_workerFarm.push_back(wd);

    if (wd.pWorker)
    {
      wd.pWorker->moveToThread(wd.pThread);

      success = connect(wd.pThread, SIGNAL(started()), wd.pWorker, SLOT(process()));
      success = connect(wd.pWorker, SIGNAL(finished()), wd.pThread, SLOT(quit()));
      success = connect(wd.pWorker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));

      success = connect(wd.pThread, SIGNAL(finished()), wd.pThread, SLOT(deleteLater()));
      success = connect(wd.pWorker, SIGNAL(finished()), wd.pWorker, SLOT(deleteLater()));

      success = connect(wd.pWorker, SIGNAL(finished(int)), this, SLOT(onFinishedReceived(int)));
    }
  }

  bool test = true;
}

// ------------------------------------------------------------------------------------------
QtGuiApplication1::~QtGuiApplication1()
{
}

// ------------------------------------------------------------------------------------------
void QtGuiApplication1::on_pushButtonStartWorkers_clicked()
{
  setupWorkers(); 
  displayStatusMessage("----------------------------------------");
  startAllWorkers();
}

// ------------------------------------------------------------------------------------------
void QtGuiApplication1::startAllWorkers()
{
  m_benchmarkStart = std::chrono::steady_clock::now();
  
  displayStatusMessage("Start workers:");
  int workerCnt = 0;
  for (std::vector<WorkerData>::iterator it = m_workerFarm.begin(); it != m_workerFarm.end(); ++it)
  {
    if (QThread* tp = (*it).pThread)
    {
      /*
      0 : scheduled only when no other threads are running.     QThread::LowestPriority
      1 : scheduled less often than LowPriority.                QThread::LowPriority
      2 : scheduled less often than NormalPriority.             QThread::NormalPriority
      3 : the default priority of the operating system.         QThread::HighPriority
      4 : scheduled more often than NormalPriority.             QThread::HighestPriority
      5 : scheduled more often than HighPriority.               QThread::TimeCriticalPriority
      6 : scheduled as often as possible.                       QThread::InheritPriority
      7 : use the same priority as the creating thread. This is the default.
      */
      const int maxPriority = 3;
      int prio = (qrand() * maxPriority / RAND_MAX) + 1;
      tp->start(QThread::Priority(prio));
      (*it).setWorking();

      QString str = QString("Worker %1 started with priority %2").arg(workerCnt++).arg(prio);
      displayStatusMessage(str);
    }
  }
}

// ------------------------------------------------------------------------------------------
void QtGuiApplication1::onFinishedReceived(int numberOfWorker)
{
  qint64 lapTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_benchmarkStart).count();

  QString str = QString("Worker %1 has finished his work. (%2 ms)").arg(numberOfWorker).arg(lapTime);
  displayStatusMessage(str);
  m_workerFarm.at(numberOfWorker).resetWorking();

  if (allWorkersAreFinished())
  {
    m_benchmarkEnd = std::chrono::steady_clock::now();
    qint64 durationTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_benchmarkEnd - m_benchmarkStart).count();
    QString str = QString("==>> All Workers have finished working after %1 ms!").arg(durationTime);
    displayStatusMessage(str);
  }
}
// ------------------------------------------------------------------------------------------
bool QtGuiApplication1::allWorkersAreFinished()
{
  bool someAreStillWorking = false;
  for (std::vector<WorkerData>::iterator it = m_workerFarm.begin(); it != m_workerFarm.end(); ++it)
  {
    someAreStillWorking |= (*it).isWorking();
  }
  return !someAreStillWorking;
}

// ------------------------------------------------------------------------------------------
void QtGuiApplication1::errorString(QString errorString)
{
  QString str = QString("error : %1").arg(errorString); 
  displayStatusMessage(str);
}

// ------------------------------------------------------------------------------------------
void QtGuiApplication1::displayStatusMessage(QString str)
{
  ui->textEditStatus->append(str);
}

