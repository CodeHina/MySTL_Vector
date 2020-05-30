#ifndef RDONLYFUNC_H_INCLUDED
#define RDONLYFUNC_H_INCLUDED


//�Ƿ������ж� - 0������
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



//���������Ĳ���
template<typename T>
Rank Vector<T>::Find(const T& e,Rank lo,Rank hi) const
{
    while(lo < hi-- && (e != _elem[hi]));   //ǰΪ��ִ�к� - �ɹ��������һ��e��λ��/ʧ�ܷ���lo-1λ��
    return hi;
}
template<typename T>        //ȫ�������
Rank Vector<T>::Find(const T& e) const {return Find(e,0,_size);}






//���������Ķ��ֲ��� - �������� - ���ز�����e���Ǹ�λ�� - ��Сʱ����lo-1/���󷵻�hi-1
template<typename T>
Rank Vector<T>::bin_search(const T& e,Rank lo,Rank hi) const
{
    while (lo < hi)               //������[0,lo)��������e,[hi,n)������e - ���Ӷ�ΪO(log2^n)
    {
        Rank mi = (lo + hi) >> 1; //ȡ�����е� - *******************************************************��������Ҫע�� - ����lo\hi�ڲ��ϱ仯,���Բ���(lo + hi)/2ȡ�е�
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
