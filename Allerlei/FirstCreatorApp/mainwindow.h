#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QMainWindow>
#include <QXmlStreamReader>

#include <QtCore>
#include <QtXml/QtXml>
#include <QtXml/QDomElement>


namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonOpenFile_clicked();

private:
    Ui::MainWindow *ui;

    //void ListElements(QDomElement root, QString tagname, QString attribute);

    QFile* xmlFile = nullptr;

    const QString filePath = "c:\\Users\\mathes\\AppData\\Roaming\\Scienta Omicron\\MATRIX\\default\\Experiments\\test.expp";

};

#endif // MAINWINDOW_H
