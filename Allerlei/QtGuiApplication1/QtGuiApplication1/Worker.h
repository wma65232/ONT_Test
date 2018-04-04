#ifndef Worker_H
#define Worker_H

#include <QThread>
#include <QFile>
#include <QTextStream>

class Worker : public QObject {
  Q_OBJECT

public:
  Worker();
  Worker(int number, qint64 numberOfBytesToBeWritten = 500000);
  ~Worker();

  int number() { return m_number; }

public slots:
  void process();

signals:
  void finished();
  void finished(int numberOfWorker);
  void error(QString err);

private:
  QFile *m_file = nullptr;
  //QTextStream *m_out(QFile *file);

  void initialize();
  int m_number = -1;

  qint64 m_numberOfCharactersToBeWritten;
};

#endif
