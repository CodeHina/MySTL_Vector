#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#define DEFAULT_CAPACITY 10
#include <ctime>
#include <cstdlib>

typedef int Rank;

//#include "D:\c++_project\PQ_CompHeap\PQ_CompHeap.h" //引入完全二叉堆 - 进行堆排序

template<typename T>
class Vector
{
//private:
protected:  //子类可访问
    int _size;
    int _capacity;
    T * _elem;
protected:
//拷贝函数
    void copy_from(const T* A,Rank lo,Rank hi);
//扩容与缩容
    void expand();
    void shrink();

//排序算法
    Rank bubble(Rank lo,Rank hi);       //扫描交换 - 返回最后一组逆序对的位置
    void bubble_sort(Rank lo,Rank hi);  //冒泡排序


    void selection_sort(Rank lo,Rank hi);
    Rank select_max(Rank lo,Rank hi);   //无序区间寻找最大值下标

    void insert_sort(Rank lo,Rank hi);

    void Merge(Rank lo,Rank mi,Rank hi);//两个有序区间进行合并
    void Merge_sort(Rank lo,Rank hi);   //归并排序




public:
    //快排
    void QuickSort(Rank lo,Rank hi);
    Rank partition(Rank lo,Rank hi);    //分割A
    Rank partition(Rank,Rank,int);//分割B

    //堆排序
    void heap_sort( Rank lo, Rank hi );

    //选取秩为k的元素
    T select_k_ver1(Rank k, Rank lo, Rank hi);
    T select_k_ver2(Rank k, Rank lo, Rank hi);
    //快速选取
    T QuickSelect(Rank k, Rank lo, Rank hi);

    //希尔排序
    void ShellSort(Rank lo, Rank hi);


public:
//构造与析构函数

    Vector(int s = 0,int c = DEFAULT_CAPACITY,T v = 0) : _size(s),_capacity(c) //初始规模为0,容量为c,所有元素初始化为0
    {
        _elem = new T[_capacity];
        for (int i = 0; i < _size; ++i)
            _elem[i] = v;
    }
    //拷贝构造函数
    Vector(const Vector<T>& that) { copy_from(that._elem,0,that._size); }
    //拷贝数组进行构造
    Vector(const T* A,Rank lo,Rank hi) { copy_from(A,lo,hi); }
    Vector(const T* A,int a_size) { copy_from(A,0,a_size); }

    //析构函数
    virtual ~Vector() { delete [] _elem; }




//只读访问接口

    int get_size() const {return _size;}
    bool IsEmpty() const {return !_size;}   //精妙的判空

    int disordered() const;                 //逆序对个数

    Rank Find(const T& e) const;            //无序向量的查找
    Rank Find(const T& e,Rank lo,Rank hi) const;

    Rank bin_search(const T& e) const;      //有序向量的二分查找
    Rank bin_search(const T& e,Rank lo,Rank hi) const;

//可写访问接口

    //运算符的重载
    T& operator[](Rank index) const { return _elem[index]; }    //返回的值可以做左值
    Vector<T>& operator=(const Vector<T>& that);                //赋值运算符的重载

    //插入操作
    int put_back(const T& e) { return Insert(e); }
    int Insert(const T& e) { return Insert(e,_size); }    //默认尾部插入
    int Insert(const T& e,Rank index);

    //删除元素
    T Remove(Rank index);
    int Remove(Rank lo,Rank hi);        //区间删除[lo,hi)  - 删除hi - lo个元素

    //排序接口
    void Sort() { Sort(0,_size); }      //整体排序
    void Sort(Rank lo,Rank hi);         //区间排序

    //唯一化
    int deduplicate();  //无序去重
    int uniquify();     //有序去重



//遍历接口 - 只读
    void traverse() const
    {
        for (int i = 0; i < _size;++i)
            std::cout << _elem[i] << " ";
        std::cout << std::endl;
    }




};  //Vector

//---------------------------------------------------------------protected---------------------------------------------------------------

//copy_from(只作用于构造函数) - 拷贝一个数组
template<typename T>
void Vector<T>::copy_from(const T* A,Rank lo,Rank hi)
{
    //分配空间,规模清零
    _elem = new T[_capacity = (hi - lo) * 2];
    _size = 0;

    while(lo < hi)
    {
        _elem[_size++] = A[lo++];
    }
    return;
}

//expand() - shrink()//缩容不再实现
template<typename T>
void Vector<T>::expand()
{
    if(_size < _capacity) {return;}
    if(_capacity < DEFAULT_CAPACITY) {_capacity = DEFAULT_CAPACITY;}

    T * old_elem = _elem;
    _elem = new T[_capacity <<= 1]; //加倍式扩容 - 其分摊的复杂度为O(1)
    for (int i = 0; i < _size; ++i) _elem[i] = old_elem[i];

    delete [] old_elem;         //释放旧数组 - new/delete不能忘
    return;
}


#include "Algori.h"





//---------------------------------------------------------------public---------------------------------------------------------------
//构造与析构均已经实现


//只读访问接口
#include "RdonlyFunc.h" //配置此文件的绝对路径


//运算符重载
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& that)       //可以实现链式赋值
{
    if (this == &that)  //不进行此判断 - 两者为同一对象时会释放that
        return *this;

    delete [] _elem;//释放当前的内存
    copy_from(that._elem,0,that._size);
    return *this;
}


//可写访问接口
#include "RdWrFunc.h"





#endif // VECTOR_H_INCLUDED
