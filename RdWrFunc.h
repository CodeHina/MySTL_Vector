#ifndef RDWRFUNC_H_INCLUDED
#define RDWRFUNC_H_INCLUDED



//插入操作
template<typename T>
int Vector<T>::Insert(const T& e,Rank index)
{
    expand();
    //后项拷贝
    for (int i = _size; i > index; --i)
    {
        _elem[i] = _elem[i-1];
    }
    _elem[index] = e;
    _size++;
    return index;       //返回插入位置交给上层调用者
}

//删除单个元素
template<typename T>
T Vector<T>::Remove(Rank index)
{
    T v = _elem[index];     //保存删除数据

    Remove(index,index+1);  //[index,index+1)区间
    return v;               //不能返回本地变量的引用或者指针
}
template<typename T>
int Vector<T>::Remove(Rank lo,Rank hi)  //[hi,_size)区间元素前移
{
    if (lo == hi) return 0;             //出于效率考虑,单独处理退化的问题
    while (hi < _size)
    {
        _elem[lo++] = _elem[hi++];      //[hi,_size)区间前移
    }
    _size = lo;
    return hi - lo;
}


//排序接口
template<typename T>
void Vector<T>::Sort(Rank lo,Rank hi)
{
    if (hi - lo < 2)
        return;
    srand(time(0));
    switch(rand() % 4)
    {
        case 1:
            bubble_sort(lo,hi);
        case 2:
            selection_sort(lo,hi);
        case 3:
            insert_sort(lo,hi);
        case 4:
            Merge_sort(lo,hi);

    }

    return;
}

//无序向量的唯一化
template<typename T>
int Vector<T>::deduplicate()
{
    int old_size = _size;
    int i = 0;           //已经无重复元素区间的元素个数 - 初始化为0
    while (i < _size)
    {
        (Find (_elem[i],0,i) > 0) ? Remove(i) : i++;    //[0,i) - 无重区间 - 不断生长
    }
    return old_size - _size;
}
//有序向量的唯一化
template<typename T>
int Vector<T>::uniquify()
{
    int old_size = _size;
    int i = 0,j = 1;
    while (j < _size)
    {
        if(_elem[i] != _elem[j])
        {
            _elem[++i] = _elem[j];
        }
        j++;
    }
    _size = ++i;
    return old_size - _size;
}




#endif // RDWRFUNC_H_INCLUDED
