#include "cFileData.h"

//bool cFileData::loadFileTIC(const char* pFilePath, const int lengthPath,
//                            double** pDataTIC, long& lengthTIC,
//                            double** pDataMass, long& lengthMass)
//{
//    QString filePath(QString::fromUtf8(QByteArray(pFilePath, lengthPath)));
//    if(!filePath.isEmpty()){
//        QFile tempFileTIC(filePath);
//        try{
//            if(!tempFileTIC.open(QIODevice::ReadOnly | QIODevice::Text))
//                return false;
//            else{
//                QByteArray tempDataTIC=tempFileTIC.readAll();
//                QList<QByteArray> tmpList=tempDataTIC.split('\n');
//                long listSize=tmpList.size();
//                mDataTIC_X.resize(listSize);
//                mDataTIC_Y.resize(listSize);
//                QList<QByteArray> tmpList1;
//                --listSize;
//                for(int i=0;i<listSize;++i){
//                    tmpList1= tmpList[i].split('\t');
//                    mDataTIC_X[i]=tmpList1[0].toDouble();
//                    mDataTIC_Y[i]=tmpList1[1].toDouble();
//                }
//            }
//        }catch(...){ return false; }
//    }
//}

//bool cFileData::loadFileTIC(QVector<double>& pDataTIC_X,QVector<double>& pDataTIC_Y, QString pFilePath)
//{
//    if(pFilePath.isEmpty())
//        pFilePath= QCoreApplication::applicationDirPath()+"/data/tmp.T";
//    QFile tempFileTIC(pFilePath);
//    QByteArray tempDataTIC;
//    try{
//        if(!tempFileTIC.open(QIODevice::ReadOnly | QIODevice::Text))
//            return false;
//        else{
//            tempDataTIC=tempFileTIC.readAll();
//            tempFileTIC.close();
//        }
//    }catch(...){ return false; }
//    QList<QByteArray> tmpList= tempDataTIC.split('\n');
//    long listSize= tmpList.size();
//    if(listSize<=0)
//        return false;
//    pDataTIC_X.resize(listSize);
//    pDataTIC_Y.resize(listSize);
//    QList<QByteArray> tmpList1;
//    --listSize;
//    for(int i=0;i<listSize;++i){
//        tmpList1= tmpList[i].split('\t');
//        pDataTIC_X[i]=tmpList1[0].toDouble();
//        pDataTIC_Y[i]=tmpList1[1].toDouble();
//    }
//    return true;
//}

//qint64 endLine(QFile& tempFileTIC, double& x, double& y){
//    QByteArray tempDataTIC;
//    int lineB=-1, lineE=-1;
//    int i= tempFileTIC.size();
//    do{
//        if(!tempFileTIC.seek(--i))
//            return -1;
//        tempDataTIC= tempFileTIC.read(1);
//        if(tempDataTIC.isEmpty())
//            return -1;
//        if(tempDataTIC[0]!='\n'){
//            if(lineE== -1)
//                lineE= i;
//        }else{
//            if(lineE!= -1){
//                lineB= ++i;
//                tempFileTIC.seek(lineB);
//                tempDataTIC= tempFileTIC.readLine();
//                QList<QByteArray>tmpList= tempDataTIC.split('\t');
//                if(tmpList.size()!= 2)
//                    return 0;
//                x= tmpList[0].toDouble();
//                y= tmpList[1].toDouble();
//                return lineB;
//            }
//        }
//    }while(i>0);
//    return 0;
//}

//bool cFileData::loadFileTIC(std::vector<double>& pDataTIC_X, std::vector<double>& pDataTIC_Y,
//                            double Period, QString pFilePath)// qint64 currentF,
//{
////    if(seedBegin< seedEnd)
////        return false;
//    if(pFilePath.isEmpty())
//        pFilePath= QCoreApplication::applicationDirPath()+"/data/tmp.T";
//    QFile tempFileTIC(pFilePath);
//    //QList<QByteArray> tmpList1;
//    QByteArray tempDataTIC;
//    double xEnd=0,yEnd=0;
//    //QList<QByteArray> tmpList1;
//    QList<QByteArray> tmpList;
//    QList<double> tempX, tempY;
//    try{
//        if(!tempFileTIC.open(QIODevice::ReadOnly | QIODevice::Text))
//            return false;
//        else{
//            if(endLine(tempFileTIC, xEnd, yEnd)>0){
//                tempFileTIC.seek(0);
//                if(xEnd<= Period){
//                    tempDataTIC= tempFileTIC.readAll();
//                    tmpList= tempDataTIC.split('\n');
//                }else{
////                    while(!tempFileTIC.atEnd()){
////                        tmpList= tempFileTIC.readLine().split('\t');
////                        if()
////                    }
//                }
//            }else{
//                tempFileTIC.close();
//                return false;
//            }
//        }
//        tempFileTIC.close();

//    }catch(...){ return false; }
//    //QList<QByteArray> tmpList= tempDataTIC.split('\n');
//    long listSize=tmpList.size()-1;//last is empty
//    if(listSize<=0)
//        return false;
//    pDataTIC_X.resize(listSize);
//    pDataTIC_Y.resize(listSize);
//    QList<QByteArray> tmpList1;
//    //--listSize;
//    for(int i=0;i<listSize;++i){
//        tmpList1= tmpList[i].split('\t');
//        pDataTIC_X[i]=tmpList1[0].toDouble();
//        pDataTIC_Y[i]=tmpList1[1].toDouble();
//    }
//    return true;
//}

//bool cFileData::loadDataHead(QString pFilePath, QByteArray& pIndexArray, QByteArray& pStreamHead)
//{
//    if(!pFilePath.isEmpty()){
//        qint64 sizeHead=sizeof(_StreamHead);
//        QFile tmpFile(pFilePath);
//        pStreamHead.resize(sizeHead);
//        try{
//            if(!tmpFile.open(QIODevice::ReadOnly)) return false;
//        }catch(...){ return false; }
//        try{
//            if(sizeHead!= tmpFile.read(pStreamHead.data(), sizeHead)){
//                tmpFile.close(); return false;
//            }else{
//                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
//                sizeHead= tmpStreamHead->length;
//                pStreamHead.resize(sizeHead);
//                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
//                tmpFile.seek(0);
//                if(sizeHead!= tmpFile.read(pStreamHead.data(), sizeHead)){
//                    tmpFile.close(); return false;
//                }
//            }
//        }catch(...){ return false; }
//        qint64 sizeData= tmpFile.size()- sizeHead;
//        if(sizeData<= 0){
//            pIndexArray.clear(); return true;
//        }
//        pIndexArray.resize(sizeData);
//        try{
//            tmpFile.seek(sizeHead);
//            if(sizeData!= tmpFile.read(pIndexArray.data(),sizeData)){
//                tmpFile.close(); return false;
//            }
//        }catch(...){}
//        try{ tmpFile.close(); }catch(...){ return false; }
//        return true;
//    }
//    return false;
//}

//bool cFileData::loadDataHead(QString pFilePath, QByteArray& pIndexArray,
//                             std::vector<double>& pTicX, std::vector<double>& pTicY, QByteArray& pStreamHead)
//{
//    if(!pFilePath.isEmpty()){
//        qint64 sizeHead=sizeof(_StreamHead);
//        QFile tmpFile(pFilePath);
//        pStreamHead.resize(sizeHead);
//        try{
//            if(!tmpFile.open(QIODevice::ReadOnly)) return false;
//        }catch(...){ return false; }
//        try{
//            if(sizeHead!= tmpFile.read(pStreamHead.data(), sizeHead)){
//                tmpFile.close(); return false;
//            }else{
//                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
//                sizeHead= tmpStreamHead->length;
//                pStreamHead.resize(sizeHead);
//                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
//                tmpFile.seek(0);
//                if(sizeHead!= tmpFile.read(pStreamHead.data(), sizeHead)){
//                    tmpFile.close(); return false;
//                }
//            }
//        }catch(...){ return false; }
//        qint64 sizeData= tmpFile.size()- sizeHead;
//        if(sizeData<= 0){
//            pIndexArray.clear();
//            pTicX.clear();
//            pTicY.clear();
//            return true;
//        }
//        int sizeI64= sizeof(qint64), sizeD= sizeof(double);
//        int offsetI= sizeI64+ sizeD* 2, offsetY= sizeI64+ sizeD;
//        qint64 lineData= sizeData/(offsetI);
//        QByteArray tempArray;
//        tempArray.resize(sizeData);
//        try{
//            tmpFile.seek(sizeHead);
//            if(sizeData!= tmpFile.read(tempArray.data(),sizeData)){
//                tmpFile.close(); return false;
//            }
//        }catch(...){}
//        try{ tmpFile.close(); }catch(...){ return false; }

//        int offsetLine=0;

//        pIndexArray.resize(lineData* sizeI64);
//        pTicX.resize(lineData);
//        pTicY.resize(lineData);
//        for(qint64 i=0; i<lineData; ++i){
//            offsetLine= i* offsetI;
//            memcpy(pIndexArray.data()+ i* sizeI64, tempArray.data()+ offsetLine, sizeI64);
//            memcpy(pTicX.data()+ i, tempArray.data()+ offsetLine+ sizeI64, sizeD);
//            memcpy(pTicY.data()+ i, tempArray.data()+ offsetLine+ offsetY, sizeD);
//        }
//        return true;
//    }
//    return false;
//}

bool cFileData::loadDataHead(QString pFilePath, double Period, std::vector<qint64>& pIndexArray,
                             std::vector<double>& pTicX, std::vector<double>& pTicY, QByteArray& pStreamHead, QVector<qint64>& pPageTIC)//
{
    if(!pFilePath.isEmpty()){
        qint64 sizeHead=sizeof(_StreamHead);
        QFile tmpFile(pFilePath);
        pStreamHead.resize(sizeHead);
        try{
            if(!tmpFile.open(QIODevice::ReadOnly)) return false;
        }catch(...){ return false; }
        try{
            if(sizeHead!= tmpFile.read(pStreamHead.data(), sizeHead)){
                tmpFile.close(); return false;
            }else{
                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                sizeHead= tmpStreamHead->length;
                pStreamHead.resize(sizeHead);
                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                tmpFile.seek(0);
                if(sizeHead!= tmpFile.read(pStreamHead.data(), sizeHead)){
                    tmpFile.close(); return false;
                }
            }
        }catch(...){ return false; }
        qint64 sizeData= tmpFile.size()- sizeHead;
        if(sizeData<= 0){
            pIndexArray.clear();
            pTicX.clear();
            pTicY.clear();
            return true;
        }
        int sizeI64= sizeof(qint64), sizeD= sizeof(double);
        int offsetI= sizeI64+ sizeD* 2, offsetY= sizeI64+ sizeD;
        qint64 lineData= sizeData/(offsetI);
        QByteArray tempArray;
        tempArray.resize(offsetI* 3);
        try{
            if(offsetI* 3!= tmpFile.read(tempArray.data(), offsetI* 3)){
                tmpFile.close(); return false;
            }
        }catch(...){tmpFile.close(); return false;}
        double interval= *((double*)(tempArray.data()+ offsetI* 2+ sizeI64))-
                *((double*)(tempArray.data()+ offsetI+ sizeI64));
        double allTime= ((double)sizeData)/ ((double)offsetI)* interval;
        if(allTime< Period){
            pPageTIC.resize(1);
            pPageTIC[0]= sizeHead;
            tempArray.resize(sizeData);
            try{
                tmpFile.seek(sizeHead);
                if(sizeData!= tmpFile.read(tempArray.data(),sizeData)){
                    tmpFile.close(); return false;
                }
            }catch(...){}
            try{ tmpFile.close(); }catch(...){ return false; }
            int offsetLine=0;
            pIndexArray.resize(lineData);
            pTicX.resize(lineData);
            pTicY.resize(lineData);
            for(qint64 i=0; i<lineData; ++i){
                offsetLine= i* offsetI;
                memcpy(pIndexArray.data()+ i, tempArray.data()+ offsetLine, sizeI64);
                memcpy(pTicX.data()+ i, tempArray.data()+ offsetLine+ sizeI64, sizeD);
                memcpy(pTicY.data()+ i, tempArray.data()+ offsetLine+ offsetY, sizeD);
            }
            return true;
        }else{
            qint64 sizeSpread= qint64(Period/ interval)* offsetI;
            qint64 sizeSpread1= sizeData% sizeSpread;
            qint64 sizePage= (sizeData)/ sizeSpread;
            if(sizeSpread1==0){
                sizeSpread1= sizeSpread;
                sizePage+= sizePage-1;
            }else if(sizeSpread1<= qint64(Period/ interval)/2* offsetI){//<=sizeSpread/2
                sizePage+= sizePage;
            }else{//>sizeSpread/2
                sizePage+= sizePage+1;
            }
            pPageTIC.resize(sizePage);
            for(int i=0; i<sizePage ;i++)
                pPageTIC[i]= sizeHead+ qint64(Period/ interval)/2* offsetI* i;

            tempArray.resize(sizeSpread1);
            try{
                tmpFile.seek(pPageTIC.last());//tmpFile.seek(tmpFile.size()- sizeSpread1);
                if(sizeSpread1!= tmpFile.read(tempArray.data(),sizeSpread1)){
                    tmpFile.close(); return false;
                }
            }catch(...){}
            try{ tmpFile.close(); }catch(...){ return false; }

            int offsetLine=0;
            lineData= sizeSpread1/ offsetI;
            pIndexArray.resize(lineData);
            pTicX.resize(lineData);
            pTicY.resize(lineData);
            for(qint64 i=0; i<lineData; ++i){
                offsetLine= i* offsetI;
                memcpy(pIndexArray.data()+ i, tempArray.data()+ offsetLine, sizeI64);
                memcpy(pTicX.data()+ i, tempArray.data()+ offsetLine+ sizeI64, sizeD);
                memcpy(pTicY.data()+ i, tempArray.data()+ offsetLine+ offsetY, sizeD);
            }
            return true;
        }
    }
    return false;
}

bool cFileData::loadEndFrameHead(QString pFilePath, std::vector<qint64>& pIndexArray, QByteArray& pStreamHead)//
{
    if(!pFilePath.isEmpty()){
        qint64 sizeHead=sizeof(_StreamHead);
        QFile tmpFile(pFilePath);
        pStreamHead.resize(sizeHead);
        try{
            if(!tmpFile.open(QIODevice::ReadOnly)) return false;
        }catch(...){ return false; }
        try{
            if(sizeHead!= tmpFile.read(pStreamHead.data(), sizeHead)){
                tmpFile.close(); return false;
            }else{
                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                sizeHead= tmpStreamHead->length;
                pStreamHead.resize(sizeHead);
                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
                tmpFile.seek(0);
                if(sizeHead!= tmpFile.read(pStreamHead.data(), sizeHead)){
                    tmpFile.close(); return false;
                }
            }
        }catch(...){ return false; }
        qint64 sizeData= tmpFile.size()- sizeHead;
        if(sizeData<= 0){
            pIndexArray.clear();
            //pTicX.clear();
            //pTicY.clear();
            return true;
        }
        int sizeI64= sizeof(qint64), sizeD= sizeof(double);
        int offsetI= sizeI64+ sizeD* 2, offsetY= sizeI64+ sizeD;
        qint64 lineData= sizeData/(offsetI);
        sizeData= (lineData- 2)* offsetI;
        QByteArray tempArray;
        tempArray.resize(offsetI);
        try{
            tmpFile.seek(sizeHead+ sizeData);
            if(offsetI!= tmpFile.read(tempArray.data(), offsetI)){
                tmpFile.close(); return false;
            }
        }catch(...){tmpFile.close(); return false;}
        pIndexArray.resize(sizeI64);
        memcpy(pIndexArray.data(), tempArray.data(), sizeI64);
        return true;
    }
    return false;
}

bool cFileData::loadDataHead(QString pFilePath, qint64 page, std::vector<qint64>& pIndexArray,
                         std::vector<double>& pTicX, std::vector<double>& pTicY,
                     qint64 sizeHead, QVector<qint64>& pPageTIC)
{
    if(!pFilePath.isEmpty()){
        //qint64 sizeHead=sizeof(_StreamHead);
        QFile tmpFile(pFilePath);
        //pStreamHead.resize(sizeHead);
        try{
            if(!tmpFile.open(QIODevice::ReadOnly)) return false;
        }catch(...){ return false; }
//        try{
//            if(sizeHead!= tmpFile.read(pStreamHead.data(), sizeHead)){
//                tmpFile.close(); return false;
//            }else{
//                _StreamHead* tmpStreamHead= (_StreamHead*)(pStreamHead.data());
//                sizeHead= tmpStreamHead->length;
//                pStreamHead.resize(sizeHead);
//                tmpStreamHead= (_StreamHead*)(pStreamHead.data());
//                tmpFile.seek(0);
//                if(sizeHead!= tmpFile.read(pStreamHead.data(), sizeHead)){
//                    tmpFile.close(); return false;
//                }
//            }
//        }catch(...){ return false; }
        qint64 sizeData= tmpFile.size()- sizeHead;
        if((sizeData<= pPageTIC.last())|| (page>= pPageTIC.size())){
            pIndexArray.clear();
            pTicX.clear();
            pTicY.clear();
            return true;
        }

        int sizeI64= sizeof(qint64), sizeD= sizeof(double);
        int offsetI= sizeI64+ sizeD* 2, offsetY= sizeI64+ sizeD;

        qint64 endOffset= 0;
        if(page+2>= pPageTIC.size()){
            endOffset= tmpFile.size();
        }else
            endOffset= pPageTIC[page+2];
        sizeData= endOffset- pPageTIC[page];
        qint64 lineData= sizeData/(offsetI);
        QByteArray tempArray;
        tempArray.resize(sizeData);
        try{
            tmpFile.seek(pPageTIC[page]);
            if(sizeData!= tmpFile.read(tempArray.data(),sizeData)){
                tmpFile.close(); return false;
            }
        }catch(...){}
        try{ tmpFile.close(); }catch(...){ return false; }
        int offsetLine=0;
        pIndexArray.resize(lineData);
        pTicX.resize(lineData);
        pTicY.resize(lineData);
        for(qint64 i=0; i<lineData; ++i){
            offsetLine= i* offsetI;
            memcpy(pIndexArray.data()+ i, tempArray.data()+ offsetLine, sizeI64);
            memcpy(pTicX.data()+ i, tempArray.data()+ offsetLine+ sizeI64, sizeD);
            memcpy(pTicY.data()+ i, tempArray.data()+ offsetLine+ offsetY, sizeD);
        }
        return true;



//        qint64 lineData= sizeData/(offsetI);
//        QByteArray tempArray;
//        tempArray.resize(offsetI* 3);
//        try{
//            if(offsetI* 3!= tmpFile.read(tempArray.data(), offsetI* 3)){
//                tmpFile.close(); return false;
//            }
//        }catch(...){tmpFile.close(); return false;}
//        double interval= *((double*)(tempArray.data()+ offsetI* 2+ sizeI64))-
//                *((double*)(tempArray.data()+ offsetI+ sizeI64));
//        double allTime= ((double)sizeData)/ ((double)offsetI)* interval;
//        if(allTime< Period){
//            pPageTIC.resize(1);
//            pPageTIC[0]= sizeHead;
//            tempArray.resize(sizeData);
//            try{
//                tmpFile.seek(sizeHead);
//                if(sizeData!= tmpFile.read(tempArray.data(),sizeData)){
//                    tmpFile.close(); return false;
//                }
//            }catch(...){}
//            try{ tmpFile.close(); }catch(...){ return false; }
//            int offsetLine=0;
//            pIndexArray.resize(lineData);
//            pTicX.resize(lineData);
//            pTicY.resize(lineData);
//            for(qint64 i=0; i<lineData; ++i){
//                offsetLine= i* offsetI;
//                memcpy(pIndexArray.data()+ i, tempArray.data()+ offsetLine, sizeI64);
//                memcpy(pTicX.data()+ i, tempArray.data()+ offsetLine+ sizeI64, sizeD);
//                memcpy(pTicY.data()+ i, tempArray.data()+ offsetLine+ offsetY, sizeD);
//            }
//            return true;
//        }else{
//            qint64 sizeSpread= qint64(Period/ interval)* offsetI;
//            qint64 sizeSpread1= sizeData% sizeSpread;
//            qint64 sizePage= (sizeData)/ sizeSpread;
//            if(sizeSpread1==0){
//                sizeSpread1= sizeSpread;
//                sizePage+= sizePage-1;
//            }else if(sizeSpread1<= sizeSpread/2){
//                sizePage+= sizePage;
//            }else{//>sizeSpread/2
//                sizePage+= sizePage+1;
//            }
//            pPageTIC.resize(sizePage);
//            for(int i=0; i<sizePage ;i++)
//                pPageTIC[i]= sizeHead+ sizeSpread/ 2* i;

//            tempArray.resize(sizeSpread1);
//            try{
//                tmpFile.seek(pPageTIC[sizePage-1]);//tmpFile.seek(tmpFile.size()- sizeSpread1);
//                if(sizeSpread1!= tmpFile.read(tempArray.data(),sizeSpread1)){
//                    tmpFile.close(); return false;
//                }
//            }catch(...){}
//            try{ tmpFile.close(); }catch(...){ return false; }

//            int offsetLine=0;
//            lineData= sizeSpread1/ offsetI;
//            pIndexArray.resize(lineData);
//            pTicX.resize(lineData);
//            pTicY.resize(lineData);
//            for(qint64 i=0; i<lineData; ++i){
//                offsetLine= i* offsetI;
//                memcpy(pIndexArray.data()+ i, tempArray.data()+ offsetLine, sizeI64);
//                memcpy(pTicX.data()+ i, tempArray.data()+ offsetLine+ sizeI64, sizeD);
//                memcpy(pTicY.data()+ i, tempArray.data()+ offsetLine+ offsetY, sizeD);
//            }
//            return true;
//        }
    }
    return false;
}
//bool cFileData::loadDataBody(QString pFilePath, const QByteArray& pIndexArray, qint64 index,
//                             std::vector<double>& pDataX, std::vector<double>& pDataY, QByteArray& pStreamBody)
//{
//    if((pIndexArray.size()/ sizeof(uint64_t))<= index)
//        return false;
//    if(!pFilePath.isEmpty()){
//        const qint64* pIndex= (qint64*)(pIndexArray.data());
//        qint64 offset= pIndex[index];
//        qint64 sizeBody=0;
//        qint64 sizeStreamBody=sizeof(_StreamBody);
//        QFile tmpDataFileMass(pFilePath);
//        if(offset>= tmpDataFileMass.size())
//            return false;
//        pStreamBody.resize(sizeStreamBody);
//        try{
//            if(!tmpDataFileMass.open(QIODevice::ReadOnly)) return false;
//        }catch(...){return false;}
//        try{
//            if(!tmpDataFileMass.seek(offset)){
//                tmpDataFileMass.close(); return false;
//            }
//            if(sizeStreamBody!= tmpDataFileMass.read(pStreamBody.data(), sizeStreamBody)){
//                tmpDataFileMass.close(); return false;
//            }else{
//                _StreamBody* tmpStreamBody= (_StreamBody*)(pStreamBody.data());
//                sizeBody= tmpStreamBody->length- sizeStreamBody;
//                QByteArray tmpArray;
//                tmpArray.resize(sizeBody);
//                if(sizeBody!= tmpDataFileMass.read(tmpArray.data(), sizeBody)){
//                    tmpDataFileMass.close(); return false;
//                }else{
//                    qint64 sizeData= sizeBody/ sizeof(double)/2;
//                    pDataX.resize(sizeData);
//                    pDataY.resize(sizeData);
//                    memcpy(pDataX.data(), tmpArray.data(), sizeData* sizeof(double));
//                    memcpy(pDataY.data(), tmpArray.data()+sizeData* sizeof(double), sizeData* sizeof(double));
//                }
//            }
//        }catch(...){return false;}
//    }
//    return false;
//}

//bool cFileData::loadDataBody(QString pFilePath, const QByteArray& pIndexArray, qint64 index,
//                             std::vector<double>& pDataY, QByteArray& pStreamBody)
//{
//    if((pIndexArray.size()/ sizeof(uint64_t))<= index)
//        return false;
//    if(!pFilePath.isEmpty()){
//        const qint64* pIndex= (qint64*)(pIndexArray.data());
//        qint64 offset= pIndex[index];
//        qint64 sizeBody=0;
//        qint64 sizeStreamBody=sizeof(_StreamBody);
//        QFile tmpDataFileMass(pFilePath);
//        if(offset>= tmpDataFileMass.size())
//            return false;
//        pStreamBody.resize(sizeStreamBody);
//        try{
//            if(!tmpDataFileMass.open(QIODevice::ReadOnly))
//                return false;
//        }catch(...){
//            return false;
//        }
//        try{
//            if(!tmpDataFileMass.seek(offset)){
//                tmpDataFileMass.close();
//                return false;
//            }
//            if(sizeStreamBody!= tmpDataFileMass.read(pStreamBody.data(), sizeStreamBody)){
//                tmpDataFileMass.close();
//                return false;
//            }else{
//                _StreamBody* tmpStreamBody= (_StreamBody*)(pStreamBody.data());
//                sizeBody= tmpStreamBody->length- sizeStreamBody;
//                QByteArray tmpArray;
//                tmpArray.resize(sizeBody);
//                if(sizeBody!= tmpDataFileMass.read(tmpArray.data(), sizeBody)){
//                    tmpDataFileMass.close();
//                    return false;
//                }else{
//                    if(tmpStreamBody->typeParam== _StreamBody::Type_Double){
//                        qint64 sizeData= sizeBody/ sizeof(double);
//                        pDataY.resize(sizeData);
//                        memcpy(pDataY.data(), tmpArray.data(), sizeData* sizeof(double));
//                    }else if(tmpStreamBody->typeParam== _StreamBody::Type_Original){
//                        qint64 sizeData= sizeBody/ sizeof(quint16);
//                        pDataY.resize(sizeData);
//                        double dbRawScale = 2 * 4.197 / (uint32_t(0xffff));
//                        quint16* puVal= (quint16*)(tmpArray.data());
//                        for(int uIndex = 0; uIndex < sizeData; ++uIndex){
//                            pDataY[uIndex] =puVal[uIndex]* dbRawScale - 4.197;
//                        }
//                    }else if(tmpStreamBody->typeParam== _StreamBody::Type_OrigCompress){
//                        QByteArray uncompressBuff = qUncompress(tmpArray);
//                        qint64 sizeData= uncompressBuff.size()/ sizeof(quint16);
//                        pDataY.resize(sizeData);
//                        double dbRawScale = 2 * 4.197 / (uint32_t(0xffff));
//                        quint16* puVal= (quint16*)(uncompressBuff.data());
//                        for(int uIndex = 0; uIndex < sizeData; ++uIndex){
//                            pDataY[uIndex] =puVal[uIndex]* dbRawScale - 4.197;
//                        }
//                    }else{
//                        qint64 sizeData= sizeBody/ sizeof(double);
//                        pDataY.resize(sizeData);
//                        memcpy(pDataY.data(), tmpArray.data(), sizeData* sizeof(double));
//                    }
//                    return true;
//                }
//            }
//        }catch(...){ return false; }
//    }
//    return false;
//}
bool cFileData::loadDataBody(QString pFilePath, const std::vector<qint64>& pIndexArray, qint64 index,
                  std::vector<double>& pDataY, QByteArray& pStreamBody)
{
    if(pIndexArray.size()<= index)
        return false;
    if(!pFilePath.isEmpty()){
        qint64 offset= pIndexArray[index];
        qint64 sizeBody=0;
        qint64 sizeStreamBody=sizeof(_StreamBody);
        QFile tmpDataFileMass(pFilePath);
        if(offset>= tmpDataFileMass.size())
            return false;
        pStreamBody.resize(sizeStreamBody);
        try{
            if(!tmpDataFileMass.open(QIODevice::ReadOnly))
                return false;
        }catch(...){ return false; }
        try{
            if(!tmpDataFileMass.seek(offset)){
                tmpDataFileMass.close(); return false;
            }
            if(sizeStreamBody!= tmpDataFileMass.read(pStreamBody.data(), sizeStreamBody)){
                tmpDataFileMass.close(); return false;
            }else{
                _StreamBody* tmpStreamBody= (_StreamBody*)(pStreamBody.data());
                if(tmpStreamBody->lengthParam>0){
                    ulong lengthParam= tmpStreamBody->lengthParam;
                    pStreamBody.resize(sizeStreamBody+ lengthParam);
                    tmpDataFileMass.read(pStreamBody.data()+ sizeStreamBody, lengthParam);
                    tmpStreamBody= (_StreamBody*)(pStreamBody.data());
                }
                sizeBody= tmpStreamBody->length- sizeStreamBody- tmpStreamBody->lengthParam;
                QByteArray tmpArray;
                tmpArray.resize(sizeBody);
                if(sizeBody!= tmpDataFileMass.read(tmpArray.data(), sizeBody)){
                    tmpDataFileMass.close(); return false;
                }else{
                    if(tmpStreamBody->typeParam== _StreamBody::Type_Double){
                        pDataY.resize(sizeBody/sizeof(double));
                        memcpy(pDataY.data(), tmpArray.data(), sizeBody);
                    }else if(tmpStreamBody->typeParam== _StreamBody::Type_FloatCompress){
                        QByteArray uncompressBuff = qUncompress(tmpArray);
                        qint64 sizeData= uncompressBuff.size()/ sizeof(float);
                        pDataY.resize(sizeData);
                        double* pY=(double*)pDataY.data();
                        double dbRawScale = 2 * 4.197 / (uint32_t(0xffff));
                        float* pfVal= (float*)(uncompressBuff.data());
                        for(int uIndex = 0; uIndex < sizeData; ++uIndex){
                            pY[uIndex] =pfVal[uIndex];//pY[uIndex] =puVal[uIndex]* dbRawScale - 4.197;
                        }
                    }else if(tmpStreamBody->typeParam== _StreamBody::Type_Uint16){
                        qint64 sizeData= sizeBody/ sizeof(quint16);
                        pDataY.resize(sizeData);
                        double* pY=(double*)pDataY.data();
                        double dbRawScale = 2 * 4.197 / (uint32_t(0xffff));
                        quint16* puVal= (quint16*)(tmpArray.data());
                        for(int uIndex = 0; uIndex < sizeData; ++uIndex){
                            pY[uIndex] =puVal[uIndex]* dbRawScale - 4.197;
                        }
                    }else if(tmpStreamBody->typeParam== _StreamBody::Type_Uint16Compress){
                        QByteArray uncompressBuff = qUncompress(tmpArray);
                        qint64 sizeData= uncompressBuff.size()/ sizeof(quint16);
                        pDataY.resize(sizeData);
                        double* pY=(double*)pDataY.data();
                        double dbRawScale = 2 * 4.197 / (uint32_t(0xffff));
                        quint16* puVal= (quint16*)(uncompressBuff.data());
                        for(int uIndex = 0; uIndex < sizeData; ++uIndex){
                            pY[uIndex] =puVal[uIndex];//pY[uIndex] =puVal[uIndex]* dbRawScale - 4.197;
                        }
                    }else{
                        pDataY.resize(sizeBody/sizeof(double));
                        memcpy(pDataY.data(), tmpArray.data(), sizeBody* sizeof(double));
                    }
                    return true;
                }
            }
        }catch(...){ return false; }
    }
    return false;
}

bool cFileData::loadDataBody(QString pFilePath, const std::vector<qint64>& pIndexArray, qint64 index,
                             QByteArray& pDataY, QByteArray& pStreamBody)
{
    if(pIndexArray.size()<= index)
        return false;
    if(!pFilePath.isEmpty()){
        qint64 offset= pIndexArray[index];
        qint64 sizeBody=0;
        qint64 sizeStreamBody=sizeof(_StreamBody);
        QFile tmpDataFileMass(pFilePath);
        if(offset>= tmpDataFileMass.size())
            return false;
        pStreamBody.resize(sizeStreamBody);
        try{
            if(!tmpDataFileMass.open(QIODevice::ReadOnly))
                return false;
        }catch(...){ return false; }
        try{
            if(!tmpDataFileMass.seek(offset)){
                tmpDataFileMass.close(); return false;
            }
            if(sizeStreamBody!= tmpDataFileMass.read(pStreamBody.data(), sizeStreamBody)){
                tmpDataFileMass.close(); return false;
            }else{
                _StreamBody* tmpStreamBody= (_StreamBody*)(pStreamBody.data());
                if((tmpStreamBody->typeParam>_StreamBody::Type_Double)||(tmpStreamBody->typeParam<_StreamBody::Type_Null)){
                    tmpDataFileMass.close(); return false;
                }
                if(tmpStreamBody->lengthParam>0){
                    ulong lengthParam= tmpStreamBody->lengthParam;
                    pStreamBody.resize(sizeStreamBody+ lengthParam);
                    tmpDataFileMass.read(pStreamBody.data()+ sizeStreamBody, lengthParam);
                    tmpStreamBody= (_StreamBody*)(pStreamBody.data());
                }
                sizeBody= tmpStreamBody->length- sizeStreamBody- tmpStreamBody->lengthParam;
                QByteArray tmpArray;
                tmpArray.resize(sizeBody);
                if(sizeBody!= tmpDataFileMass.read(tmpArray.data(), sizeBody)){
                    tmpDataFileMass.close(); return false;
                }else{
                    if(tmpStreamBody->typeParam== _StreamBody::Type_Double){
                        pDataY.resize(sizeBody);
                        memcpy(pDataY.data(), tmpArray.data(), sizeBody);
                    }else if(tmpStreamBody->typeParam== _StreamBody::Type_FloatCompress){
                        QByteArray uncompressBuff = qUncompress(tmpArray);
                        qint64 sizeData= uncompressBuff.size()/ sizeof(float);
                        pDataY.resize(sizeData* sizeof(double));
                        double* pY=(double*)pDataY.data();
                        double dbRawScale = 2 * 4.197 / (uint32_t(0xffff));
                        float* pfVal= (float*)(uncompressBuff.data());
                        for(int uIndex = 0; uIndex < sizeData; ++uIndex){
                            pY[uIndex] =pfVal[uIndex];//pY[uIndex] =puVal[uIndex]* dbRawScale - 4.197;
                        }
                        sizeData=sizeData;
                    }else if(tmpStreamBody->typeParam== _StreamBody::Type_Uint16){
                        qint64 sizeData= sizeBody/ sizeof(quint16);
                        pDataY.resize(sizeData* sizeof(double));
                        double* pY=(double*)pDataY.data();
                        double dbRawScale = 2 * 4.197 / (uint32_t(0xffff));
                        quint16* puVal= (quint16*)(tmpArray.data());
                        for(int uIndex = 0; uIndex < sizeData; ++uIndex){
                            pY[uIndex] =puVal[uIndex]* dbRawScale - 4.197;
                        }
                    }else if(tmpStreamBody->typeParam== _StreamBody::Type_Uint16Compress){
                        QByteArray uncompressBuff = qUncompress(tmpArray);
                        qint64 sizeData= uncompressBuff.size()/ sizeof(quint16);
                        pDataY.resize(sizeData* sizeof(double));
                        double* pY=(double*)pDataY.data();
                        double dbRawScale = 2 * 4.197 / (uint32_t(0xffff));
                        quint16* puVal= (quint16*)(uncompressBuff.data());
                        for(int uIndex = 0; uIndex < sizeData; ++uIndex){
                            pY[uIndex] =puVal[uIndex];//pY[uIndex] =puVal[uIndex]* dbRawScale - 4.197;
                        }
                    }else{
                        pDataY.resize(sizeBody);
                        memcpy(pDataY.data(), tmpArray.data(), sizeBody* sizeof(double));
                    }
                    return true;
                }
            }
        }catch(...){ return false; }
    }
    return false;
}

bool cFileData::loadDataBody(QString pFilePath, const std::vector<qint64>& pIndexArray, int nFrameB, int nFrameE,
                             QByteArray& pDataY, QByteArray& pStreamBody)
{
    if((pIndexArray.size()<= nFrameB)|| (pIndexArray.size()<= nFrameE))
        return false;
    if(!pFilePath.isEmpty()){
        QFile tmpDataFileMass(pFilePath);
        try{
            if(!tmpDataFileMass.open(QIODevice::ReadOnly)) return false;
        }catch(...){ return false; }
        int tmpACC = 0;
        do{
            qint64 offset= pIndexArray[nFrameB+ tmpACC];
            qint64 sizeBody=0;
            qint64 sizeStreamBody=sizeof(_StreamBody);
            if(offset>= tmpDataFileMass.size()) return false;
            pStreamBody.resize(sizeStreamBody);
            try{
                if(!tmpDataFileMass.seek(offset)){
                    tmpDataFileMass.close(); return false;
                }
                if(sizeStreamBody!= tmpDataFileMass.read(pStreamBody.data(), sizeStreamBody)){
                    tmpDataFileMass.close(); return false;
                }else{
                    _StreamBody* tmpStreamBody= (_StreamBody*)(pStreamBody.data());
                    if(tmpStreamBody->lengthParam>0){
                        ulong lengthParam= tmpStreamBody->lengthParam;
                        pStreamBody.resize(sizeStreamBody+ lengthParam);
                        tmpDataFileMass.read(pStreamBody.data()+ sizeStreamBody, lengthParam);
                        tmpStreamBody= (_StreamBody*)(pStreamBody.data());
                    }
                    sizeBody= tmpStreamBody->length- sizeStreamBody- tmpStreamBody->lengthParam;
                    QByteArray tmpArray;
                    tmpArray.resize(sizeBody);
                    if(sizeBody!= tmpDataFileMass.read(tmpArray.data(), sizeBody)){
                        tmpDataFileMass.close(); return false;
                    }else{
                        if(tmpStreamBody->typeParam== _StreamBody::Type_Double){
                            if(tmpACC== 0){
                                pDataY.resize(sizeBody);
                                memcpy(pDataY.data(), tmpArray.data(), sizeBody);
                            }else{
                                qint64 sizeData= sizeBody/ sizeof(double);
                                double* pDstY=(double*)pDataY.data();
                                double* pSrcY=(double*)tmpArray.data();
                                for(int uIndex = 0; uIndex < sizeData; ++uIndex){
                                    pDstY[uIndex]= (double)(tmpACC-1) / (double)(tmpACC) * pDstY[uIndex]+ pSrcY[uIndex]/ (tmpACC);
                                }
                            }
                        }else if(tmpStreamBody->typeParam== _StreamBody::Type_FloatCompress){
                            QByteArray uncompressBuff= qUncompress(tmpArray);
                            qint64 sizeData= uncompressBuff.size()/ sizeof(float);
                            double dbRawScale= 2* 4.197/ (uint32_t(0xffff));
                            float* pSrcY= (float*)(uncompressBuff.data());
                            if(tmpACC== 0){
                                pDataY.resize(sizeData* sizeof(double));
                                double* pDstY=(double*)pDataY.data();
                                for(int uIndex= 0; uIndex< sizeData; ++uIndex){
                                    pDstY[uIndex]= (double)(pSrcY[uIndex]);
                                }
                            }else if(tmpACC+nFrameB== nFrameE){
                                double* pDstY=(double*)pDataY.data();
                                for(int uIndex= 0; uIndex< sizeData; ++uIndex){
                                    pDstY[uIndex]= (double)(tmpACC-1)/ (double)(tmpACC)* pDstY[uIndex]+
                                            (double)(pSrcY[uIndex])/ (double)(tmpACC);
                                    pDstY[uIndex]= pDstY[uIndex];//pDstY[uIndex]= pDstY[uIndex]* dbRawScale- 4.197;
                                }
                            }else{
                                double* pDstY=(double*)pDataY.data();
                                for(int uIndex= 0; uIndex< sizeData; ++uIndex){
                                    pDstY[uIndex]= (double)(tmpACC-1)/ (double)(tmpACC)* pDstY[uIndex]+
                                            (double)(pSrcY[uIndex])/ (double)(tmpACC);
                                }
                            }
                        }else if(tmpStreamBody->typeParam== _StreamBody::Type_Uint16){
                            qint64 sizeData= sizeBody/ sizeof(quint16);
                            double dbRawScale = 2 * 4.197 / (uint32_t(0xffff));
                            quint16* pSrcY= (quint16*)(tmpArray.data());
                            if(tmpACC== 0){
                                pDataY.resize(sizeData* sizeof(double));
                                double* pDstY= (double*)pDataY.data();
                                for(int uIndex= 0; uIndex< sizeData; ++uIndex){
                                    pDstY[uIndex]= (double)(pSrcY[uIndex]);
                                }
                            }else if(tmpACC==nFrameE){
                                double* pDstY=(double*)pDataY.data();
                                for(int uIndex = 0; uIndex < sizeData; ++uIndex){
                                    pDstY[uIndex]= (double)(tmpACC-1)/ (double)(tmpACC)* pDstY[uIndex]+
                                            (double)(pSrcY[uIndex])/ (double)(tmpACC);
                                    pDstY[uIndex]= pDstY[uIndex]* dbRawScale- 4.197;
                                }
                            }else{
                                double* pDstY=(double*)pDataY.data();
                                for(int uIndex= 0; uIndex < sizeData; ++uIndex){
                                    pDstY[uIndex]= (double)(tmpACC-1)/ (double)(tmpACC)* pDstY[uIndex]+
                                            (double)(pSrcY[uIndex])/ (double)(tmpACC);
                                }
                            }
                        }else if(tmpStreamBody->typeParam== _StreamBody::Type_Uint16Compress){
                            QByteArray uncompressBuff= qUncompress(tmpArray);
                            qint64 sizeData= uncompressBuff.size()/ sizeof(quint16);
                            double dbRawScale= 2* 4.197/ (uint32_t(0xffff));
                            quint16* pSrcY= (quint16*)(uncompressBuff.data());
                            if(tmpACC== 0){
                                pDataY.resize(sizeData* sizeof(double));
                                double* pDstY=(double*)pDataY.data();
                                for(int uIndex= 0; uIndex< sizeData; ++uIndex){
                                    pDstY[uIndex]= (double)(pSrcY[uIndex]);
                                }
                            }else if(tmpACC+nFrameB== nFrameE){
                                double* pDstY=(double*)pDataY.data();
                                for(int uIndex= 0; uIndex< sizeData; ++uIndex){
                                    pDstY[uIndex]= (double)(tmpACC-1)/ (double)(tmpACC)* pDstY[uIndex]+
                                            (double)(pSrcY[uIndex])/ (double)(tmpACC);
                                    pDstY[uIndex]= pDstY[uIndex];//pDstY[uIndex]= pDstY[uIndex]* dbRawScale- 4.197;
                                }
                            }else{
                                double* pDstY=(double*)pDataY.data();
                                for(int uIndex= 0; uIndex< sizeData; ++uIndex){
                                    pDstY[uIndex]= (double)(tmpACC-1)/ (double)(tmpACC)* pDstY[uIndex]+
                                            (double)(pSrcY[uIndex])/ (double)(tmpACC);
                                }
                            }
                        }else{
                            pDataY.resize(sizeBody);
                            memcpy(pDataY.data(), tmpArray.data(), sizeBody* sizeof(double));
                        }
                    }
                }
            }catch(...){ return false; }
        }while(++tmpACC+nFrameB<= nFrameE);
        return true;
    }
    return false;
}

bool cFileData::loadFileMass(int index, const std::vector<qint64>& pIndexArray,
                             QByteArray& pData, QByteArray& pStreamBody, QString pFilePathD)
{
    if(pFilePathD.isEmpty())
        pFilePathD= QCoreApplication::applicationDirPath()+"/data/tmp.D";
    if(!loadDataBody(pFilePathD, pIndexArray, index, pData, pStreamBody))
        return false;
    return true;
}

bool cFileData::loadFileMass(int nFrameB, int nFrameE, const std::vector<qint64>& pIndexArray, QByteArray& pData,
                             QByteArray& pStreamBody, QString pFilePathD)
{
    if(pFilePathD.isEmpty())
        pFilePathD= QCoreApplication::applicationDirPath()+"/data/tmp.D";
    if(!loadDataBody(pFilePathD, pIndexArray, nFrameB, nFrameE, pData, pStreamBody))
        return false;
    return true;
}
