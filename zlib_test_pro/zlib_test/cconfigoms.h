#ifndef CCONFIGOMS_H
#define CCONFIGOMS_H

#include "cPublicCCS.h"
#include <QVector>

struct _CONGIG_OMS
{
public:
    enum MODEL_GAUGE{NULL_GAUGE,PFEIFFER_GAUGE,INSTRUE_GAUGE};
    struct _CONGIG_MAINWINDOW{
        bool superMode=false;
        //bool showPressure=true;
        double gainPressure= 2.1507;
        double offsetPressure= -1.3921;
        MODEL_GAUGE ModelGauge= PFEIFFER_GAUGE;
    };

    struct _CONGIG_METHOD{
        double MassExtension=5;
        QString LimitInjectTime;
        QString ScaleRangeAGC;
        QString FunctionAGC;
    };

    struct _CONGIG_ACQUISITION{
        double Period= 1000;
        int maxiHeighMassChart= 16777215;
    };

    struct _CONGIG_ANALYSIS{
        double Period= 1000;
        int maxiHeighMassChart= 16777215;
    };

    struct _CONGIG_STATE_SYS{
        //double MinDriver= 0.1;
        //double MinSpeed= 1;
    };

    struct _CONGIG_SYSTEM{
        float LimitPressLYO=0.05;//bar
    };

    struct _CONGIG_MANUAL_TUNING{
        double MassExtension=5;
        bool showFit= false;
    };

    struct _CONGIG_AUTO_TUNING{
        double MassExtension=5;
    };

    struct _STRUCT_DATA{
        uint32_t uEvtValidPoint=0,//uPrePoint+ uEventPoint+ uPostPoint
        uPrePoint=0,
        uEventPoint=0,//without pre post
        uPostPoint=0;
    };

    struct _PARAM_FIT{
        uint enable= 1;
        uint ployD=3;
        QVector<QString> expect;//std::vector<double> expect;
        QVector<QString> current;//std::vector<double> current;
        std::vector<double> coefF;
        std::vector<double> coefB;
    };

    static QString comboCalibrat(_CONGIG_OMS::_PARAM_FIT& pPARAM_FIT){
        auto tempFunctionStr = [&](QVector<QString>& tempVec)->QString{
            QStringList tempList;
            for(int i=0; i< tempVec.size(); i++)
                tempList.append(tempVec[i]);
            return tempList.join('@');
        };
        auto tempFunctionDouble = [&](std::vector<double>& tempVec)->QString{
            QStringList tempList;
            for(int i=0; i< tempVec.size(); i++)
                tempList.append(QString::number(tempVec[i]));
            return tempList.join('@');
        };
        QStringList tempListRoot;
        tempListRoot.append(QString::number(pPARAM_FIT.enable));
        tempListRoot.append(QString::number(pPARAM_FIT.ployD));
        tempListRoot.append(tempFunctionStr(pPARAM_FIT.current));
        tempListRoot.append(tempFunctionStr(pPARAM_FIT.expect));
        tempListRoot.append(tempFunctionDouble(pPARAM_FIT.coefF));
        tempListRoot.append(tempFunctionDouble(pPARAM_FIT.coefB));
        return tempListRoot.join('&');
    }

    static bool splitCalibrat(QString strFIT, _CONGIG_OMS::_PARAM_FIT& pPARAM_FIT){
        QStringList tmpList= strFIT.split("&");
        if(tmpList.size()== 6){
            pPARAM_FIT.enable= tmpList[0].toUInt();
            pPARAM_FIT.ployD= tmpList[1].toUInt();
            QStringList tempCurrent= tmpList[2].split("@");
            QStringList tempExpect= tmpList[3].split("@");
            QStringList tempCF= tmpList[4].split("@");
            QStringList tempCB= tmpList[5].split("@");
            if((tempCurrent.size()==6)&& (tempExpect.size()==6)){
                //pCALIBRATE.lock();
                pPARAM_FIT.current.clear();
                pPARAM_FIT.expect.clear();
                pPARAM_FIT.coefF.clear();
                pPARAM_FIT.coefB.clear();
                foreach (QString var, tempCurrent)
                    pPARAM_FIT.current.push_back(var);
                foreach (QString var, tempExpect)
                    pPARAM_FIT.expect.push_back(var);
                foreach (QString var, tempCF)
                    pPARAM_FIT.coefF.push_back(var.toDouble());
                foreach (QString var, tempCB)
                    pPARAM_FIT.coefB.push_back(var.toDouble());
                //updateParam(pCALIBRATE.mPARAM_FIT, MassExtension);
                //pCALIBRATE.unlock();
            }else
                return false;
        }else
            return false;
        return true;
    }

    static void calibrationB(_CONGIG_OMS::_PARAM_FIT& pPARAM_FIT, double& pValue){
        if(pPARAM_FIT.enable==1){
            switch (pPARAM_FIT.coefB.size()) {
            case 6:
                pValue= pow(pValue, 5) * pPARAM_FIT.coefB[5]
                        + pow(pValue, 4) * pPARAM_FIT.coefB[4]
                        + pow(pValue, 3) * pPARAM_FIT.coefB[3]
                        + pow(pValue, 2) * pPARAM_FIT.coefB[2]
                        + pValue * pPARAM_FIT.coefB[1]
                        + pPARAM_FIT.coefB[0]; break;
            case 5:
                pValue= pow(pValue, 4) * pPARAM_FIT.coefB[4]
                        + pow(pValue, 3) * pPARAM_FIT.coefB[3]
                        + pow(pValue, 2) * pPARAM_FIT.coefB[2]
                        + pValue * pPARAM_FIT.coefB[1]
                        + pPARAM_FIT.coefB[0]; break;
            case 4:
                pValue= pow(pValue, 3) * pPARAM_FIT.coefB[3]
                        + pow(pValue, 2) * pPARAM_FIT.coefB[2]
                        + pValue * pPARAM_FIT.coefB[1]
                        + pPARAM_FIT.coefB[0]; break;
            case 3:
                pValue= pow(pValue, 2) * pPARAM_FIT.coefB[2]
                        + pValue * pPARAM_FIT.coefB[1]
                        + pPARAM_FIT.coefB[0]; break;
            default: break;
            }
        }
    }

    static void calibrationF(_CONGIG_OMS::_PARAM_FIT& pPARAM_FIT, double* pFirst, double* pLast,
                     cParamValue::_EventLIT* pEventLIT, _STRUCT_DATA* tempSTRUCT_DATA){
        double tempStart= pEventLIT->msStart- pEventLIT->msPrecursor;
        double tempEnd=pEventLIT->msEnd+ pEventLIT->msPrecursor;
        double dbStep= (tempEnd - tempStart) / tempSTRUCT_DATA->uEvtValidPoint;
        //double* pIndex= pFirst;
        tempSTRUCT_DATA->uPrePoint= 0;
        tempSTRUCT_DATA->uPostPoint= tempSTRUCT_DATA->uEvtValidPoint;

        if(pPARAM_FIT.enable==1){
            switch (pPARAM_FIT.coefF.size()) {
            case 6:
                while(pFirst<= pLast){
                    *pFirst= pow(tempStart, 5) * pPARAM_FIT.coefF[5]
                            + pow(tempStart, 4) * pPARAM_FIT.coefF[4]
                            + pow(tempStart, 3) * pPARAM_FIT.coefF[3]
                            + pow(tempStart, 2) * pPARAM_FIT.coefF[2]
                            + tempStart * pPARAM_FIT.coefF[1]
                            + pPARAM_FIT.coefF[0];
                    if(*pFirst< pEventLIT->msStartOrig)
                        ++tempSTRUCT_DATA->uPrePoint;
                    if(*pFirst< pEventLIT->msEndOrig)
                        --tempSTRUCT_DATA->uPostPoint;
                    tempStart += dbStep;
                    pFirst++;
                }break;
            case 5:
                while(pFirst<= pLast){
                    *pFirst= pow(tempStart, 4) * pPARAM_FIT.coefF[4]
                            + pow(tempStart, 3) * pPARAM_FIT.coefF[3]
                            + pow(tempStart, 2) * pPARAM_FIT.coefF[2]
                            + tempStart * pPARAM_FIT.coefF[1]
                            + pPARAM_FIT.coefF[0];
                    if(*pFirst< pEventLIT->msStartOrig)
                        ++tempSTRUCT_DATA->uPrePoint;
                    if(*pFirst< pEventLIT->msEndOrig)
                        --tempSTRUCT_DATA->uPostPoint;
                    tempStart += dbStep;
                    pFirst++;
                }break;
            case 4:
                while(pFirst<= pLast){
                    *pFirst= pow(tempStart, 3) * pPARAM_FIT.coefF[3]
                            + pow(tempStart, 2) * pPARAM_FIT.coefF[2]
                            + tempStart * pPARAM_FIT.coefF[1]
                            + pPARAM_FIT.coefF[0];
                    if(*pFirst< pEventLIT->msStartOrig)
                        ++tempSTRUCT_DATA->uPrePoint;
                    if(*pFirst< pEventLIT->msEndOrig)
                        --tempSTRUCT_DATA->uPostPoint;
                    tempStart += dbStep;
                    pFirst++;
                }break;
            case 3:
                while(pFirst<= pLast){
                    *pFirst= pow(tempStart, 2) * pPARAM_FIT.coefF[2]
                            + tempStart * pPARAM_FIT.coefF[1]
                            + pPARAM_FIT.coefF[0];
                    if(*pFirst< pEventLIT->msStartOrig)
                        ++tempSTRUCT_DATA->uPrePoint;
                    if(*pFirst< pEventLIT->msEndOrig)
                        --tempSTRUCT_DATA->uPostPoint;
                    tempStart += dbStep;
                    pFirst++;
                }break;
            default:
                while(pFirst<= pLast){
                    *pFirst= tempStart;
                    if(*pFirst< pEventLIT->msStartOrig)
                        ++tempSTRUCT_DATA->uPrePoint;
                    if(*pFirst< pEventLIT->msEndOrig)
                        --tempSTRUCT_DATA->uPostPoint;
                    tempStart += dbStep;
                    pFirst++;
                }
                break;
            }
        }else{
            while(pFirst<= pLast){
                *pFirst= tempStart;
                if(*pFirst< pEventLIT->msStartOrig)
                    ++tempSTRUCT_DATA->uPrePoint;
                if(*pFirst< pEventLIT->msEndOrig)
                    --tempSTRUCT_DATA->uPostPoint;
                tempStart += dbStep;
                pFirst++;
            }
        }
    }

    static void calibrationF(_CONGIG_OMS::_PARAM_FIT& pPARAM_FIT, double* pFirst, double* pLast,
                                      double dbVal, double dbStep){
        if(pPARAM_FIT.enable==1){
            switch (pPARAM_FIT.coefF.size()) {
            case 6:
                while(pFirst<= pLast){
                    *pFirst= pow(dbVal, 5) * pPARAM_FIT.coefF[5]
                            + pow(dbVal, 4) * pPARAM_FIT.coefF[4]
                            + pow(dbVal, 3) * pPARAM_FIT.coefF[3]
                            + pow(dbVal, 2) * pPARAM_FIT.coefF[2]
                            + dbVal * pPARAM_FIT.coefF[1]
                            + pPARAM_FIT.coefF[0];
                    dbVal += dbStep;
                    pFirst++;
                }break;
            case 5:
                while(pFirst<= pLast){
                    *pFirst= pow(dbVal, 4) * pPARAM_FIT.coefF[4]
                            + pow(dbVal, 3) * pPARAM_FIT.coefF[3]
                            + pow(dbVal, 2) * pPARAM_FIT.coefF[2]
                            + dbVal * pPARAM_FIT.coefF[1]
                            + pPARAM_FIT.coefF[0];
                    dbVal += dbStep;
                    pFirst++;
                }break;
            case 4:
                while(pFirst<= pLast){
                    *pFirst= pow(dbVal, 3) * pPARAM_FIT.coefF[3]
                            + pow(dbVal, 2) * pPARAM_FIT.coefF[2]
                            + dbVal * pPARAM_FIT.coefF[1]
                            + pPARAM_FIT.coefF[0];
                    dbVal += dbStep;
                    pFirst++;
                }break;
            case 3:
                while(pFirst<= pLast){
                    *pFirst= pow(dbVal, 2) * pPARAM_FIT.coefF[2]
                            + dbVal * pPARAM_FIT.coefF[1]
                            + pPARAM_FIT.coefF[0];
                    dbVal += dbStep;
                    pFirst++;
                }break;
            default:
                while(pFirst<= pLast){
                    *pFirst= dbVal;
                    dbVal += dbStep;
                    pFirst++;
                }
                break;
            }
        }else{
            while(pFirst<= pLast){
                *pFirst= dbVal;
                dbVal += dbStep;
                pFirst++;
            }
        }
    }
};

#endif // CCONFIGOMS_H
