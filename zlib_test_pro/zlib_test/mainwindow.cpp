#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <zlib.h>
#include <qdebug.h>

#define MaxBufferSize 200
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


void MainWindow::on_pushButton_clicked()
{
    FILE* File_src;
    FILE* File_compress;
    FILE* File_uncompress;
    unsigned long len_src;
    unsigned long len_compress;
    unsigned long len_uncompress = MaxBufferSize;
    unsigned char *buffer_src  = new unsigned char[MaxBufferSize];
    unsigned char *buffer_compress  = new unsigned char[MaxBufferSize];
    unsigned char *buffer_uncompress = new unsigned char[MaxBufferSize];
    File_src = fopen("src.txt","r");//文件位置：G:\hello\zlib_test_pro\build-zlib_test-Desktop_Qt_5_12_5_MinGW_32_bit-Debug
    File_compress = fopen("compress.txt","w");
    File_uncompress = fopen("uncompress.txt","w");
    //compress
    len_src = fread(buffer_src,sizeof(char),MaxBufferSize-1,File_src);
    compress(buffer_compress, &len_compress, buffer_src, len_src);
    fwrite(buffer_compress, sizeof(char), len_compress, File_compress);
    qDebug() << "normal zlib:" ;
    qDebug() << "src:\n" << buffer_src << ",length:" << len_src ;
    qDebug() << "compress:\n" << buffer_compress << ",length:" << len_compress ;
    //uncompress
    uncompress(buffer_uncompress, &len_uncompress, buffer_compress, len_compress);
    fwrite(buffer_uncompress, sizeof(char), len_uncompress, File_uncompress);
    qDebug() << "uncompress:\n" << buffer_uncompress << ",length:" << len_uncompress;
    fclose(File_src);
    fclose(File_compress);
    fclose(File_uncompress);
}

void MainWindow::on_pushButton_2_clicked()
{
    QByteArray src;
    src.append("中华人民共和国,china mobile,123456 ");
    unsigned long len_compress;
    unsigned long len_uncompress;
    unsigned char *buffer_compress  = new unsigned char[MaxBufferSize];
    unsigned char *buffer_uncompress = new unsigned char[MaxBufferSize];
    compress(buffer_compress,&len_compress,(Bytef*)src.data(), src.length());
    uncompress(buffer_uncompress,&len_uncompress,buffer_compress,len_compress);
    qDebug() << "qt zlib:"  ;
    qDebug() << "src:\n" << src.data() << ",length:" << src.size() ;
    qDebug() << "compress:\n" << buffer_compress << ",length:" << len_compress ;
    qDebug() << "uncompress:\n" << buffer_uncompress << ",length:" << len_uncompress ;
}
