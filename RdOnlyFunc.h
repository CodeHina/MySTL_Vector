#ifndef RDONLYFUNC_H_INCLUDED
#define RDONLYFUNC_H_INCLUDED


//是否有序判断 - 0即有序
template<typename T>
int Vector<T>::disordered() const
{
    int i = 0;
    int n = 0;
    while(++i < _size)
    {
        if(_elem[i - 1] > _elem[i])
            n++;
    }
    return n;
}



//无序向量的查找
template<typename T>
Rank Vector<T>::Find(const T& e,Rank lo,Rank hi) const
{
    while(lo < hi-- && (e != _elem[hi]));   //前为真执行后 - 成功返回最后一个e的位置/失败返回lo-1位置
    return hi;
}
template<typename T>        //全区间查找
Rank Vector<T>::Find(const T& e) const {return Find(e,0,_size);}






//有序向量的二分查找 - 满足语义 - 返回不大于e的那个位置 - 极小时返回lo-1/极大返回hi-1
template<typename T>
Rank Vector<T>::bin_search(const T& e,Rank lo,Rank hi) const
{
    while (lo < hi)               //不变性[0,lo)均不大于e,[hi,n)均大于e - 复杂度为O(log2^n)
    {
        Rank mi = (lo + hi) >> 1; //取区间中点 - *******************************************************这里尤其要注意 - 由于lo\hi在不断变化,所以采用(lo + hi)/2取中点
        if (e < _elem[mi])
            hi = mi;
        else
            lo = mi + 1;
    }
    return --lo;
}
template<typename T>
Rank Vector<T>::bin_search(const T& e) const {return bin_search(e,0,_size);}





#endif // RDONLYFUNC_H_INCLUDED
