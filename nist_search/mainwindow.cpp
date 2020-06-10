#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <QProcess>
#include <QLibrary>
#include <QFileInfo>
#include <CII.GCMS.NISTSCH.h>
#include <list>

using namespace CII::GCMS::NISTSCH::NistSearch;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

typedef std::list<NistMSData> (*mySearch)(unsigned int mass[], unsigned int abund[], int hitNum);

//search
void MainWindow::on_UI_PB_SEARCH_clicked()
{
    QLibrary mydll("CII.GCMS.NISTSCH.dll");
        if(!mydll.load())
        {
            qDebug() << "load dll error";
        }else{
            qDebug() << "load dll success";
            NistPathHelper::IsUseMainLib = true;
            NistPathHelper::FULL_PATH_TO_MAIN_LIBRARY = "G:\\NIST11\\MSSEARCH\\mainlib";
            NistPathHelper::FULL_PATH_TO_WORK_DIR = "G:\\Nist11";
            NistPathHelper::FULL_PATH_TO_USER_LIBRARY = "G:\\Nist11\\MSSEARCH\\userlib1";
            NistPathHelper::FULL_PATH_TO_REPLICATE_LIBRARY = "G:\\Nist11\\MSSEARCH\\replib";
            NistPathHelper::FULL_PATH_TO_USER_LIBRARY2 = "G:\\Nist11\\MSSEARCH\\userlib2";

            mySearch m_mySearch = (mySearch)mydll.resolve("Search");

            if(m_mySearch){
                unsigned int mass[] = {91, 92, 78, 77};
                unsigned int abund[] = {100, 67, 34 ,30};
                std::list<NistMSData> nistSearchedDatas = m_mySearch(mass, abund, 2);
                if(nistSearchedDatas.size() > 0)
                    qDebug() << "search success";
                else
                    qDebug() << "search failed!";
            }
            else
            {
              qDebug() << "get Function address error";
            }

        }
        if(mydll.isLoaded())
        {
            mydll.unload();
        }
}

//search by starting process.
void MainWindow::on_UI_PB_SCH_PS_clicked()
{
//    QProcess* srcProcess = new QProcess();
//    QString proPath = "G:\\NIST11\\MSSEARCH\\nistms.exe";
//    if(!isFileExist(proPath))
//        qDebug() << "Error, path incorrect\n";
//    srcProcess->setProgram(proPath);
//    srcProcess->start(QIODevice::ReadWrite);
//    srcProcess->waitForStarted();
//    srcProcess->waitForFinished();
//    qDebug()<<QString::fromLocal8Bit(srcProcess->readAllStandardOutput());
//    srcProcess->close();
}

bool MainWindow::isFileExist(QString fullFilePath)
{
    QFileInfo fileInfo(fullFilePath);
    if(fileInfo.exists())
    {
        return true;
    }
    return false;
}
