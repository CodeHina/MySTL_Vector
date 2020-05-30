#ifndef RDWRFUNC_H_INCLUDED
#define RDWRFUNC_H_INCLUDED



//�������
template<typename T>
int Vector<T>::Insert(const T& e,Rank index)
{
    expand();
    //�����
    for (int i = _size; i > index; --i)
    {
        _elem[i] = _elem[i-1];
    }
    _elem[index] = e;
    _size++;
    return index;       //���ز���λ�ý����ϲ������
}

//ɾ������Ԫ��
template<typename T>
T Vector<T>::Remove(Rank index)
{
    T v = _elem[index];     //����ɾ������

    Remove(index,index+1);  //[index,index+1)����
    return v;               //���ܷ��ر��ر��������û���ָ��
}
template<typename T>
int Vector<T>::Remove(Rank lo,Rank hi)  //[hi,_size)����Ԫ��ǰ��
{
    if (lo == hi) return 0;             //����Ч�ʿ���,���������˻�������
    while (hi < _size)
    {
        _elem[lo++] = _elem[hi++];      //[hi,_size)����ǰ��
    }
    _size = lo;
    return hi - lo;
}


//����ӿ�
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

//����������Ψһ��
template<typename T>
int Vector<T>::deduplicate()
{
    int old_size = _size;
    int i = 0;           //�Ѿ����ظ�Ԫ�������Ԫ�ظ��� - ��ʼ��Ϊ0
    while (i < _size)
    {
        (Find (_elem[i],0,i) > 0) ? Remove(i) : i++;    //[0,i) - �������� - ��������
    }
    return old_size - _size;
}
//����������Ψһ��
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
