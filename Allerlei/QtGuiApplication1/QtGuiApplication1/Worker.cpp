#include "Worker.h"

Worker::Worker()
{ // Standard Constructor
}

Worker::Worker(int number, qint64 numberOfCharactersToBeWritten) : 
  m_number(number), 
  m_numberOfCharactersToBeWritten(numberOfCharactersToBeWritten)
{
  initialize();
}

void Worker::initialize()
{
  //QString fileName = QString("d:\\CMake\\temp\\") + QString("ThreadTest_") + QString::number(m_number) + QString(".txt");
  QString fileName = QString(".\\") + QString("ThreadTest_") + QString::number(m_number) + QString(".txt");
  m_file = new QFile(fileName);
  bool success = m_file->open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);

  //m_out = new QTextStream(&m_file);
  QTextStream m_out(m_file);
  m_out.setCodec("ISO 8859-1");
  m_out << "Worker-File : " << m_number << endl;
}

Worker::~Worker() 
{
  if (m_file)
  {
    delete m_file;
  }
}

void Worker::process()
{ // Process. Start processing data.
  for (int i = 0; i != m_numberOfCharactersToBeWritten; ++i)
  {
    QString str = QString(QString::number(qrand()*9/RAND_MAX));
    m_file->write(str.toStdString().c_str());
  }
  m_file->flush();
  m_file->close();

  emit finished();
  emit finished(m_number);
}
