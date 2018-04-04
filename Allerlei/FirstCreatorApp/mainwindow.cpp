#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>


/* https://www.youtube.com/watch?v=NzQwJdcdRKE */


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    xmlFile = new QFile(filePath);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete xmlFile;
    delete ui;
}


//void MainWindow::ListElements(QDomElement root, QString tagname, QString attribute)
//{
    //QDomNodeList items  = root.elementsByTagName(tagname);

//}



void MainWindow::on_pushButtonOpenFile_clicked()
{
    bool success = xmlFile->open(QIODevice::ReadOnly | QIODevice::Text);
    if (!success)
    {
        QMessageBox::critical(this,"Load XML File Problem",
        "Couldn't open xmlfile.xml to load settings for download",
        QMessageBox::Ok);
        return;
    }

    QXmlStreamReader xmlReader(xmlFile);



    int totalCnt = 0;
    ui->listWidgetFound->clear();
    while(!xmlReader.atEnd() && !xmlReader.hasError())
    {
        totalCnt++;
        if(xmlReader.readNext() == QXmlStreamReader::StartElement)
        {
            if(xmlReader.name() == "Cardinal")
            {

                QString element = xmlReader.readElementText();
                int lineNumber = xmlReader.lineNumber();

                ui->listWidgetFound->addItem(QString::number(lineNumber) + " : " + element);
            }
        }
    }


    ui->labelTest->setText(QString::number(totalCnt));
    xmlReader.clear();
    xmlFile->close();

}





/*

    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError())
    {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument) {
                continue;
        }
        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement)
        {
            if(xmlReader->name() == "ZI_Tu_Lu0_Source_Channel")
            {
                continue;
            }

            if(xmlReader->name() == "ZI_Tu_Lu2_Source_Type")
            {
                qDebug() << xmlReader->readElementText();
            }
        }
    }

    if(xmlReader->hasError())
    {
        QMessageBox::critical(this,
        "xmlFile.xml Parse Error",xmlReader->errorString(),
        QMessageBox::Ok);
    }

*/
