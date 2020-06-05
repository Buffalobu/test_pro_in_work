#ifndef UNION_FIND_H
#define UNION_FIND_H
#include "assert.h"

class union_find
{
public:
    union_find(int n)
    {
        assert(n>0);
        count = n;
        index = new int[n];
        roote = new int[0];
        for(int i = 0;i < n; i++)
        {
            index[i] = i;
            roote[i] = 0;
        }
    }

    ~union_find()
    {
        if(index != nullptr)
        {
            delete[] index;
            index = nullptr;
        }
        if(roote != nullptr)
        {
            delete[] roote;
            roote = nullptr;
        }
    }
    int number()
    {
        return count;
    }
    /**
     * @projectName translate_test
     * @brief       查找根节点
     * @param       p
     * @author      LuoYong
     * @date        2019-11-13
     */
    int find(int p)
    {
        while(p != index[p])
        {
            index[p] = index[index[p]];//将父节点指向爷爷节点，路径压缩
            p = index[p];
        }
        return p;
    }
    /**
     * @projectName translate_test
     * @brief       判断是否连通
     * @param       p,q
     * @author      LuoYong
     * @date        2019-11-13
     */
    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }
    /**
     * @projectName translate_test
     * @brief       连通操作
     * @param       参数1,参数2...
     * @author      LuoYong
     * @date        2019-11-13
     */
    void union_opreation(int p, int q)
    {
        int x = find(p);
        int y = find(q);
        if(x == y) //已经连通直接返回
            return;
        if(roote[x] < roote[y])//将小树作为大树的子树
        {
            index[x] = y;
            roote[y]++; //大树的大小加1
        }
        else
        {
            index[y] = x;
            roote[x]++;
        }
        count--;
    }

private:
    int count;
    int* index;//数组下标表示值，数组里面装的是其父节点
    int* roote;//记录树的大小（分支数）
};


#endif // UNION_FIND_H
