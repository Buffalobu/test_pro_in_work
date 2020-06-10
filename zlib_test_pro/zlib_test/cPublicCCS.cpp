#include "cPublicCCS.h"

void sortGICAP::quickSort(double s[], int* pMarker, int left,//数组下标
                 int right)//数组下标，为长度-1

{
    if (left < right){
        int low = left, high = right;
        double key = s[left];
        int keyMarker=pMarker[left];
        while (low < high){
            while(low < high && s[high] - key >= 0.0000001) // 从右向左找第一个小于key的数
                high--;
            if(low < high){
                pMarker[low] = pMarker[high];
                s[low++] = s[high];
            }
            while(low < high && s[low] < key) // 从左向右找第一个大于等于key的数
                low++;
            if(low < high){
                pMarker[high] = pMarker[low];
                s[high--] = s[low];
            }
        }
        s[low] = key;
        pMarker[low]=keyMarker;
        sortGICAP::quickSort(s, pMarker,left, low - 1); // 递归调用
        sortGICAP::quickSort(s, pMarker,low + 1, right);
    }
}
void sortGICAP::widthSort(double* cAbsc,/*y值数组*/
                              int* pMarker,/**/
                              int nLength,
                              int nWidth)//只排序前nWidth个最大值
{
    if(nLength==nWidth)
        return;
    int countAbsc=0;
    double temp1=0;
    int left1=0,right1=nLength-1,left2=nLength-1;
    while(left1<nWidth){
        for(int i=left1;i<nLength;i++){
            if(cAbsc[left1]<cAbsc[i]){
                countAbsc++;
                if(countAbsc>=nWidth-left1){
                    temp1=cAbsc[right1];
                    cAbsc[right1]=cAbsc[left1];
                    cAbsc[left1]=temp1;
                    temp1=pMarker[right1];
                    pMarker[right1]=pMarker[left1];
                    pMarker[left1]=temp1;
                    right1--;
                    break;
                }
            }
        }
        countAbsc=0;
        if(left2!=right1)
            left2=right1;
        else left1++;
    }
}
void sortGICAP::widthSort(double* cAbsc,/*y值数组*/
                              int nLength,
                              int nWidth)//只排序前nWidth个最大值
{
    if(nLength==nWidth)
        return;
    int countAbsc=0;
    double temp1=0;
    int left1=0,right1=nLength-1,left2=nLength-1;
    while(left1<nWidth){
        for(int i=left1;i<nLength;i++){
            if(cAbsc[left1]<cAbsc[i]){
                countAbsc++;
                if(countAbsc>=nWidth-left1){
                    temp1=cAbsc[right1];
                    cAbsc[right1]=cAbsc[left1];
                    cAbsc[left1]=temp1;
                    right1--;
                    break;
                }
            }
        }
        countAbsc=0;
        if(left2!=right1)
            left2=right1;
        else left1++;
    }
}

bool sortGICAP::isOverRange(double* cAbsc,/*y值数组*/
                              quint64 nLength,
                              quint64 nWidth)//只排序前nWidth个最大值
{
    if(nLength==nWidth)
        return false;
    quint64 indexMax=0;
    std::list<int> tempList;
    for(quint64 i=1; i< nLength; ){
        if(cAbsc[i]-cAbsc[i-1]> 1e-8)
            indexMax=i;
    }
    for(quint64 i=0; i< nLength; ++i){
        if(cAbsc[indexMax]-cAbsc[i]< 1e-8){
            tempList.push_back(i);
            if(tempList.size()>=nWidth){
                return true;
            }
        }
    }
    return false;
}

void sortGICAP::DateSort(const std::vector<double>& pAbsc, const std::vector<double>& pOrd,
                         const std::vector<int>& pStart, const std::vector<int>& pEnd, std::vector<double>& pAbsc1, std::vector<double>& pOrd1,
                         std::vector<int>& pStart1, std::vector<int>& pEnd1, std::vector<int>& pMarker, uint32_t uWidth)
{
    uint32_t nLength=pOrd.size();
    vectorOperate::Resize(pOrd1, nLength);//pOrd1.resize(nLength);
    std::copy(pOrd.begin(),pOrd.end(),pOrd1.begin());
    if(nLength<uWidth)
        uWidth=nLength;
    sortGICAP::widthSort(&(pOrd1[0]),&(pMarker[0]),nLength,uWidth);
    sortGICAP::quickSort(&(pOrd1[0]),&(pMarker[0]),0,uWidth-1);
    vectorOperate::Resize(pAbsc1, uWidth);//pAbsc1.resize(uWidth);
    vectorOperate::Resize(pOrd1, uWidth);//pOrd1.resize(uWidth);
    vectorOperate::Resize(pStart1, uWidth);//pStart1.resize(uWidth);
    vectorOperate::Resize(pEnd1, uWidth);//pEnd1.resize(uWidth);
    for(uint32_t j=0;j<uWidth;j++){
        pAbsc1[j]=pAbsc[pMarker[j]];
        pOrd1[j]=pOrd[pMarker[j]];
        pStart1[j]=pStart[pMarker[j]];
        pEnd1[j]=pEnd[pMarker[j]];
    }
}

void sortGICAP::DateSort(const std::vector<double>& pAbsc, const std::vector<double>& pOrd,const std::vector<double>& pArea,
                         const std::vector<int>& pStart, const std::vector<int>& pEnd,
                         std::vector<double>& pAbsc1, std::vector<double>& pOrd1, std::vector<double>& pArea1,
                         std::vector<int>& pStart1, std::vector<int>& pEnd1,
                         std::vector<int>& pMarker, uint32_t uWidth)
{
    uint32_t nLength=pOrd.size();
    vectorOperate::Resize(pOrd1, nLength);//pOrd1.resize(nLength);
    std::copy(pOrd.begin(),pOrd.end(),pOrd1.begin());
    if(nLength<uWidth)
        uWidth=nLength;
    sortGICAP::widthSort(&(pOrd1[0]),&(pMarker[0]),nLength,uWidth);
    sortGICAP::quickSort(&(pOrd1[0]),&(pMarker[0]),0,uWidth-1);
    vectorOperate::Resize(pAbsc1, uWidth);//pAbsc1.resize(uWidth);
    vectorOperate::Resize(pOrd1, uWidth);//pOrd1.resize(uWidth);
    vectorOperate::Resize(pArea1, uWidth);
    vectorOperate::Resize(pStart1, uWidth);//pStart1.resize(uWidth);
    vectorOperate::Resize(pEnd1, uWidth);//pEnd1.resize(uWidth);
    for(uint32_t j= 0; j< uWidth; j++){
        pAbsc1[j]= pAbsc[pMarker[j]];
        pOrd1[j]= pOrd[pMarker[j]];
        pArea1[j]= pArea[pMarker[j]];
        pStart1[j]= pStart[pMarker[j]];
        pEnd1[j]= pEnd[pMarker[j]];
    }
}

void Max_N_Of_Vector::largest_N(std::vector<double>& value, std::vector<int>& pos, int max_N)
{
    int ary_N = value.size();
    pos.resize(max_N);
    // 对数组前max_N个元素排序
    struct sort_item sort_items[max_N];
    for (int i = 0; i < max_N; i++)
    {
        sort_items[i].value = value[i];
        sort_items[i].pos = i;
    }
    qsort(sort_items, max_N, sizeof(struct sort_item), comp_item);
    for (int i = 0; i < max_N; i++)
    {
        pos[i] = sort_items[i].pos;//max_N - 1 - sort_items[i].pos;
    }

    // 线性扫描数组剩余元素
    for (int i = max_N; i < ary_N; i++)
    {
        int j = 0;
        for (j = 0; j < max_N; j++)
            if (value[i] > value[pos[j]])
                break;
        if (j < max_N)
        {
            for (int k = max_N - 1; k > j; k--)
            {
                pos[k] = pos[k-1];
            }
            pos[j] = i;
        }
    }
    std::sort(pos.begin(), pos.end());
}
