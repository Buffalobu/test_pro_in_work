#ifndef cFileData_H
#define cFileData_H
#include <QFile>
#include <QString>
#include <QVector>
#include "cPublicCCS.h"
#include <QCoreApplication>

class cFileData
{
public:
    cFileData(){}
//    bool loadFileTIC(const char* pFilePath, const int lengthPath, double** pDataTIC, long& lengthTIC,
//                     double** pDataMass, long& lengthMass);
//    static bool loadFileTIC(QVector<double> &pDataTIC_X, QVector<double> &pDataTIC_Y, QString pFilePath= QString());
//    static bool loadFileTIC(std::vector<double> &pDataTIC_X, std::vector<double> &pDataTIC_Y,
//                            double Period, QString pFilePath= QString());
    static bool loadFileTIC(double Period, std::vector<qint64>& pIndexArray, std::vector<double>& pTicX, std::vector<double>& pTicY,
                            QByteArray& pStreamHead, QVector<qint64>& pPageTIC, QString pFilePath= QString()){
        if(pFilePath.isEmpty())
            pFilePath= QCoreApplication::applicationDirPath()+"/data/tmp.P";
        return loadDataHead(pFilePath, Period, pIndexArray, pTicX, pTicY, pStreamHead, pPageTIC);
    }
    static bool loadFileTIC(qint64 page, std::vector<qint64>& pIndexArray, std::vector<double>& pTicX, std::vector<double>& pTicY,
                            qint64 sizeHead, QVector<qint64>& pPageTIC, QString pFilePath= QString()){
        if(pFilePath.isEmpty())
            pFilePath= QCoreApplication::applicationDirPath()+"/data/tmp.P";
        return loadDataHead(pFilePath, page, pIndexArray, pTicX, pTicY, sizeHead, pPageTIC);
    }
//    static bool loadFileMass(int index, std::vector<double>& pData, QByteArray& pStreamHead,QByteArray& pStreamBody,
//                             QString pFilePathP= QString(), QString pFilePathD= QString());
    static bool loadFileMass(int index, const std::vector<qint64>& pIndexArray, QByteArray& pData,
                             QByteArray& pStreamBody, QString pFilePathD= QString());
    static bool loadFileMass(int nFrameB, int nFrameE, const std::vector<qint64>& pIndexArray, QByteArray& pData,
                             QByteArray& pStreamBody, QString pFilePathD= QString());

//    static bool loadDataHead(QString pFilePath, QByteArray& pIndexArray, QByteArray& pStreamHead);
//    static bool loadDataHead(QString pFilePath, QByteArray& pIndexArray,
//                                 std::vector<double>& pTicX, std::vector<double>& pTicY, QByteArray& pStreamHead);
    static bool loadEndFrameHead(QString pFilePath, std::vector<qint64>& pIndexArray, QByteArray& pStreamHead);
    static bool loadDataHead(QString pFilePath, double Period, std::vector<qint64>& pIndexArray,
                                 std::vector<double>& pTicX, std::vector<double>& pTicY,
                             QByteArray& pStreamHead, QVector<qint64>& pPageTIC);

    static bool loadDataHead(QString pFilePath, qint64 page, std::vector<qint64>& pIndexArray,
                             std::vector<double>& pTicX, std::vector<double>& pTicY,
                         qint64 sizeHead, QVector<qint64>& pPageTIC);
//    static bool loadDataBody(QString pFilePath, const QByteArray& pIndexArray, qint64 index,
//                      std::vector<double>& pDataX, std::vector<double>& pDataY, QByteArray& pStreamBody);
//    static bool loadDataBody(QString pFilePath, const QByteArray& pIndexArray, qint64 index,
//                      std::vector<double>& pDataY, QByteArray& pStreamBody);
    static bool loadDataBody(QString pFilePath, const std::vector<qint64>& pIndexArray, qint64 index,
                      std::vector<double>& pDataY, QByteArray& pStreamBody);
    static bool loadDataBody(QString pFilePath, const std::vector<qint64>& pIndexArray, qint64 index,
                      QByteArray& pDataY, QByteArray& pStreamBody);
    static bool loadDataBody(QString pFilePath, const std::vector<qint64>& pIndexArray, int nFrameB, int nFrameE,
                      QByteArray& pDataY, QByteArray& pStreamBody);
private:
    QVector<double> mDataTIC_X;
    QVector<double> mDataTIC_Y;

};

#endif // cFileData_H
