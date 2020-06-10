#ifndef CTYPECCS_H
#define CTYPECCS_H
#include <QPluginLoader>
#include <math.h>

struct cTypeCCS
{
public:
    cTypeCCS(){}
};
struct cParamValue{
public:
    enum Type_Child_Param{Type_Child_Null, Type_Segment_Param, Type_Method_Param, Type_Process_Param};
    enum Type_Child_Body_Param{Type_Child_Body_Null, Type_Child_Body_TIC};
    enum Type_Event{Type_Event_Null, Type_LIT, Type_Profile, Type_Scan, Type_SIM, Type_Scan_RCT, Type_Static_RCT};
    enum Type_Segment{Type_Seg_Null, Type_LIT_TARGET, Type_LIT_FULL};

    struct _StreamHeadParam{
        uint32_t length = 0;
        Type_Child_Param type = Type_Child_Null;
        char param[0];
        static QByteArray toStreamArray(Type_Child_Param typeParam, QByteArray& pArray){
            int sizeArray= pArray.size();
            QByteArray tmpArray;
            tmpArray.resize(sizeof(_StreamHeadParam)+ sizeArray);
            _StreamHeadParam* pStreamParam= (_StreamHeadParam*)(tmpArray.data());
            pStreamParam->type= typeParam;
            pStreamParam->length= tmpArray.size();
            memcpy(pStreamParam->param, pArray.data(), sizeArray);
            return tmpArray;
        }
    };

    struct _Event{
        Type_Event type = Type_Event_Null;
        double holdTime = 0.0;//s阶段总时间，包含前后拓展
        double preReadyTime;//s
        double postReadyTime;//s
        double minTime;
        double msPrecursor;
        char title[30];
    };

    struct _Segment{//: public _StreamHeadParam
        //unsigned long length = 0;
        Type_Segment    type= Type_Seg_Null;           //if Tuning
        unsigned int    sumEvent;
        char    title[30];      //SegTitle
        _Event   fisrtEvent;
    };

    struct _EventScan:public _Event{
        double msStart;
        double msEnd;
        double msStartOrig;
        double msEndOrig;
    };

    typedef _EventScan _EventProfile;

    typedef _EventScan _EventLIT;

    struct _EventSIM:public _Event{
        double mass[64];
    };

    struct _StreamBodyParam{
        uint32_t length = 0;
        Type_Child_Body_Param type = Type_Child_Body_Null;
        char param[0];
        static QByteArray toStreamArray(Type_Child_Body_Param typeParam, QByteArray& pArray){
            int sizeArray= pArray.size();
            QByteArray tmpArray;
            tmpArray.resize(sizeof(_StreamBodyParam)+ sizeArray);
            _StreamBodyParam* pStreamBodyParam= (_StreamBodyParam*)(tmpArray.data());
            pStreamBodyParam->type= typeParam;
            pStreamBodyParam->length= tmpArray.size();
            memcpy(pStreamBodyParam->param, pArray.data(), sizeArray);
            return tmpArray;
        }
        static int size(){return sizeof(_StreamBodyParam);}
    };
    struct _StreamBodyTIC{
        double currentTime=0;
        double currentAcc=0;
        unsigned long dataFrame= 0;
        static uint size(){return sizeof(_StreamBodyParam)+ sizeof(_StreamBodyTIC);}
        static _StreamBodyTIC* p(_StreamBodyParam* pStreamBodyParam){
            return (_StreamBodyTIC*)((char*)pStreamBodyParam+ _StreamBodyParam::size());
        }
    };
    cParamValue(){}
};

struct _StreamHead{
    enum Type_Param{Type_Null, Type_Tuning, Type_Acquisition};
    unsigned long length = 0;
    Type_Param typeParam = Type_Null;
    unsigned long dateTime = 0;
    //cParamValue::_Segment segment;
    char param[0];
    _StreamHead(){}
    static bool toList(QByteArray& array, QList<cParamValue::_StreamHeadParam*>& pList){
        //_StreamHead* pStreamHead= (_StreamHead*)array.data();
        int offset= sizeof(_StreamHead);
        do{
            cParamValue::_StreamHeadParam* pStreamHeadParam= (cParamValue::_StreamHeadParam*)(array.data()+offset);
            pList.append(pStreamHeadParam);
            offset+= pStreamHeadParam->length;
        }while(offset< array.size());
        return true;
    }
};


struct _StreamBody{
    enum Type_Data:quint32{Type_Null, Type_Uint16Compress, Type_Uint16, Type_FloatCompress, Type_DoubleCompress, Type_Double};//Type_Double  must be the last
    unsigned long length = 0;
    Type_Data typeParam = Type_Null;
    //double currentTime=0;
    //double currentAcc=0;
    unsigned long dateTime = 0;
    //unsigned long dataFrame= 0;
    //double y[0];
    unsigned long lengthParam= 0;
    char param[0];
};

class Q_DECL_EXPORT sortGICAP{
public:
    sortGICAP(){}
    static void quickSort(double s[], int* pMarker, int left, int right);
    static bool isOverRange(double* cAbsc, quint64 nLength, quint64 nWidth);
    static void widthSort(double* cAbsc, int nLength, int nWidth);
    static void widthSort(double* cAbsc, int* pMarker, int nLength, int nWidth);
    static void DateSort(const std::vector<double>& pAbsc, const std::vector<double>& pOrd,
                                    const std::vector<int>& pStart, const std::vector<int>& pEnd, std::vector<double>& pAbsc1, std::vector<double>& pOrd1,
                                    std::vector<int>& pStart1, std::vector<int>& pEnd1, std::vector<int>& pMarker, uint32_t uWidth);
    static void DateSort(const std::vector<double>& pAbsc, const std::vector<double>& pOrd,const std::vector<double>& pArea,
                             const std::vector<int>& pStart, const std::vector<int>& pEnd,
                             std::vector<double>& pAbsc1, std::vector<double>& pOrd1, std::vector<double>& pArea1,
                             std::vector<int>& pStart1, std::vector<int>& pEnd1,
                             std::vector<int>& pMarker, uint32_t uWidth);
};

class vectorOperate{
public:
    template <class T>
    static bool Resize(std::vector<T>& pT, uint32_t n){
        if(n> pT.capacity()){
            pT.clear();
            pT.shrink_to_fit();
        }
        try{
            pT.resize(n);
        }catch(...){
            return false;
        }
        return true;
    }
    template <class T>
    static void Clear(std::vector<T>& pT){
        pT.clear();
        pT.shrink_to_fit();
    }
private:
    vectorOperate(){}
};
class QvectorOperate{
public:
    template <class T>
    static bool Resize(QVector<T>& pT, uint32_t n){
        if(n> pT.capacity()){
            pT.clear();
            pT.shrink_to_fit();
        }
        try{
            pT.resize(n);
        }catch(...){
            return false;
        }
        return true;
    }
    template <class T>
    static void Clear(QVector<T>& pT){
        pT.clear();
        pT.shrink_to_fit();
    }
private:
    QvectorOperate(){}
};

class Max_N_Of_Vector{
    // 排序结构和比较函数
private:
    struct sort_item {
        float value;
        int pos;
    };

    static int comp_item(const void * a, const void * b)
    {
        float v1 = ((struct sort_item *)a)->value;
        float v2 = ((struct sort_item *)b)->value;
        return (v1<v2) ? -1 : (v1>v2) ? 1 : 0;
    }
public:
    // 将存放有ary_N个元素的数组value中最大的max_N数的位置找出来，下标存在pos数组中
    static void largest_N(std::vector<double> &value, std::vector<int> &pos, int max_N);
};

#endif // CTYPECCS_H
