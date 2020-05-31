#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#define DEFAULT_CAPACITY 10
#include <ctime>
#include <cstdlib>

typedef int Rank;

//#include "D:\c++_project\PQ_CompHeap\PQ_CompHeap.h" //������ȫ����� - ���ж�����

template<typename T>
class Vector
{
//private:
protected:  //����ɷ���
    int _size;
    int _capacity;
    T * _elem;
protected:
//��������
    void copy_from(const T* A,Rank lo,Rank hi);
//����������
    void expand();
    void shrink();

//�����㷨
    Rank bubble(Rank lo,Rank hi);       //ɨ�轻�� - �������һ������Ե�λ��
    void bubble_sort(Rank lo,Rank hi);  //ð������


    void selection_sort(Rank lo,Rank hi);
    Rank select_max(Rank lo,Rank hi);   //��������Ѱ�����ֵ�±�

    void insert_sort(Rank lo,Rank hi);

    void Merge(Rank lo,Rank mi,Rank hi);//��������������кϲ�
    void Merge_sort(Rank lo,Rank hi);   //�鲢����




public:
    //����
    void QuickSort(Rank lo,Rank hi);
    Rank partition(Rank lo,Rank hi);    //�ָ�A
    Rank partition(Rank,Rank,int);//�ָ�B

    //������
    void heap_sort( Rank lo, Rank hi );

    //ѡȡ��Ϊk��Ԫ��
    T select_k_ver1(Rank k, Rank lo, Rank hi);
    T select_k_ver2(Rank k, Rank lo, Rank hi);
    //����ѡȡ
    T QuickSelect(Rank k, Rank lo, Rank hi);

    //ϣ������
    void ShellSort(Rank lo, Rank hi);


public:
//��������������

    Vector(int s = 0,int c = DEFAULT_CAPACITY,T v = 0) : _size(s),_capacity(c) //��ʼ��ģΪ0,����Ϊc,����Ԫ�س�ʼ��Ϊ0
    {
        _elem = new T[_capacity];
        for (int i = 0; i < _size; ++i)
            _elem[i] = v;
    }
    //�������캯��
    Vector(const Vector<T>& that) { copy_from(that._elem,0,that._size); }
    //����������й���
    Vector(const T* A,Rank lo,Rank hi) { copy_from(A,lo,hi); }
    Vector(const T* A,int a_size) { copy_from(A,0,a_size); }

    //��������
    virtual ~Vector() { delete [] _elem; }




//ֻ�����ʽӿ�

    int get_size() const {return _size;}
    bool IsEmpty() const {return !_size;}   //������п�

    int disordered() const;                 //����Ը���

    Rank Find(const T& e) const;            //���������Ĳ���
    Rank Find(const T& e,Rank lo,Rank hi) const;

    Rank bin_search(const T& e) const;      //���������Ķ��ֲ���
    Rank bin_search(const T& e,Rank lo,Rank hi) const;

//��д���ʽӿ�

    //�����������
    T& operator[](Rank index) const { return _elem[index]; }    //���ص�ֵ��������ֵ
    Vector<T>& operator=(const Vector<T>& that);                //��ֵ�����������

    //�������
    int put_back(const T& e) { return Insert(e); }
    int Insert(const T& e) { return Insert(e,_size); }    //Ĭ��β������
    int Insert(const T& e,Rank index);

    //ɾ��Ԫ��
    T Remove(Rank index);
    int Remove(Rank lo,Rank hi);        //����ɾ��[lo,hi)  - ɾ��hi - lo��Ԫ��

    //����ӿ�
    void Sort() { Sort(0,_size); }      //��������
    void Sort(Rank lo,Rank hi);         //��������

    //Ψһ��
    int deduplicate();  //����ȥ��
    int uniquify();     //����ȥ��



//�����ӿ� - ֻ��
    void traverse() const
    {
        for (int i = 0; i < _size;++i)
            std::cout << _elem[i] << " ";
        std::cout << std::endl;
    }




};  //Vector

//---------------------------------------------------------------protected---------------------------------------------------------------

//copy_from(ֻ�����ڹ��캯��) - ����һ������
template<typename T>
void Vector<T>::copy_from(const T* A,Rank lo,Rank hi)
{
    //����ռ�,��ģ����
    _elem = new T[_capacity = (hi - lo) * 2];
    _size = 0;

    while(lo < hi)
    {
        _elem[_size++] = A[lo++];
    }
    return;
}

//expand() - shrink()//���ݲ���ʵ��
template<typename T>
void Vector<T>::expand()
{
    if(_size < _capacity) {return;}
    if(_capacity < DEFAULT_CAPACITY) {_capacity = DEFAULT_CAPACITY;}

    T * old_elem = _elem;
    _elem = new T[_capacity <<= 1]; //�ӱ�ʽ���� - ���̯�ĸ��Ӷ�ΪO(1)
    for (int i = 0; i < _size; ++i) _elem[i] = old_elem[i];

    delete [] old_elem;         //�ͷž����� - new/delete������
    return;
}


#include "Algori.h"





//---------------------------------------------------------------public---------------------------------------------------------------
//�������������Ѿ�ʵ��


//ֻ�����ʽӿ�
#include "RdonlyFunc.h" //���ô��ļ��ľ���·��


//���������
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& that)       //����ʵ����ʽ��ֵ
{
    if (this == &that)  //�����д��ж� - ����Ϊͬһ����ʱ���ͷ�that
        return *this;

    delete [] _elem;//�ͷŵ�ǰ���ڴ�
    copy_from(that._elem,0,that._size);
    return *this;
}


//��д���ʽӿ�
#include "RdWrFunc.h"





#endif // VECTOR_H_INCLUDED
