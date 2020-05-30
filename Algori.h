#ifndef ALGORI_H_INCLUDED
#define ALGORI_H_INCLUDED

#include <cmath> //for log() - log(4) / log(2) - ��2Ϊ��4�Ķ���
#include "D:\C++\MyProject\PQ_CompHeap\PQ_CompHeap.h" //�������������㷨

//�����㷨-----------------------------------------------------------------------------------------------


//ð������ - ��Ѱ����Ե�λ�ò�ɨ�轻�� - ��������ȻΪO(n^2)
template<typename T>    //������������в���
Rank Vector<T>::bubble(Rank lo,Rank hi)
{
    Rank last  = lo;        //��ʼ�����һ�������λ��Ϊlo - ����������Ϊ[lo-1,lo]

    while (++lo < hi)       //�����������ɨ��
    {
        if (_elem[lo-1] > _elem[lo])
        {
            last = lo;      //���������,�����last,��������Խ��д���
            std::swap(_elem[lo-1],_elem[lo]);
        }
    }
    return last;
}
template<typename T>
void Vector<T>::bubble_sort(Rank lo,Rank hi)
{
    while (lo < hi)
    {
        hi = bubble(lo,hi); //ֱ�Ӹ��µ�ǰ���� -- ��������
    }
    return;
}


//ѡ������ - �ҳ�����±������� - O(n^2) - ����������������˽����Ĵ���
template<typename T>
Rank Vector<T>::select_max(Rank lo,Rank hi)
{
    Rank max_index = lo;
    for (int i = lo + 1; i < hi; ++i)
    {
        if(_elem[i] > _elem[max_index])
            max_index = i;
    }
    return max_index;
}
template<typename T>
void Vector<T>::selection_sort(Rank lo,Rank hi)
{
    while (lo < hi)
    {
        Rank max_index = select_max(lo,hi);
        std::swap(_elem[max_index],_elem[--hi]);
    }

}


//������
template<typename T>
void Vector<T>::heap_sort( Rank lo, Rank hi )
{
    //��������������֯Ϊ��
    PQ_CompHeap<T> heap(_elem,lo,hi);//��������������֯��һ���� - flyod�㷨O(n)

    while( !heap.IsEmpty() )
    {
        _elem[--hi] = heap.Del_max();   //ȡ��H�е����Ԫ��������Ȼ�����S��,�����������Ե�
                                        //ʵ��˼·�ǽ��Ѷ������Ԫ��ѵ�ĩԪ�ػ���,���S��������H������
                                        //ֻ�漰�����ĸ����ռ� - �Ǿ͵��㷨
    }
}



//��������
template<typename T>
void Vector<T>::insert_sort(Rank lo,Rank hi)
{
    int s_size = lo + 1;     //�Ѿ������Ԫ�صĸ��� - ��ʼ��������Ϊ[lo,s_size)
    while(s_size < _size)
    {
        T val = _elem[s_size];
        Insert(val,bin_search(val,lo,s_size)+1);
        Remove(++s_size);   //��������Ҫ�Բ��������Ԫ�ؽ��д���
    }
    return;
}

//�鲢����
template<typename T>
void Vector<T>::Merge(Rank lo,Rank mi,Rank hi)  //[lo,mi) / [mi,hi)
{
    //B \ C ����ϲ���A������ - ��B[lo,mi) - C[mi,hi)  - A
    //A
    T* A = _elem + lo;
    //B
    int size_b = mi - lo;
    T* B = new T[size_b];
    for (int i = 0; i < size_b; ++i)
        B[i] = A[i];
    //C
    int size_c = hi - mi;
    T* C = _elem + mi;

    //�鲢 i j k
    for (int i = 0,j = 0,k = 0; (j < size_b) || (k < size_c);)
    {
        //��B��Ԫ�ط���A��
        if ((j < size_b) && ((k >= size_c) || (B[j] <= C[k])))
            A[i++] = B[j++];
        //C -> A
        if ((k < size_c) && ((j >= size_b) || (B[j] > C[k])))
            A[i++] = C[k++];
    }

    delete [] B;                    //�ͷſռ䲻����
    return;
}
template<typename T>
void Vector<T>::Merge_sort(Rank lo,Rank hi)
{
    //�ݹ�һ��Ҫ���˳��ݹ������
    if (hi - lo < 2)                           //�ݹ����Ϊ��λ����
        return;
    Rank mi  = (lo + hi) / 2;                  //�ֶ���֮ - �ֳ�����С����
    //������С������й鲢����
    Merge_sort(lo,mi);
    Merge_sort(mi,hi);
    //����������������й鲢
    Merge(lo,mi,hi);
    return;
}


//��������
template<typename T>
Rank Vector<T>::partition(Rank lo,Rank hi,int a)
{
    //�˱��� - �����������з�Ϊ������ lo(���) L(������) R(������) U(δ��������) �Ĳ��� L < lo <= R
    //lo (lo,mi] (mi,k) [k,hi)
    T pivot = _elem[lo]; int mi = lo;
    for ( int k = lo + 1; k <= hi; k++ )
    {
        if(_elem[k] < pivot) //��ǰԪ��С�����
        {
            std::swap(_elem[++mi],_elem[k]); //(k++)������һԪ�� - ֻ�轫R���е���Ԫ���뵱ǰԪ�ؽ��н��� - ��������е�����,R���еĿ�����󻬶�
        }
        //else k++  - R�����������
        //��ֻ��д��forѭ����
    }
    //ѭ������lo L(lo,mi] R(mi,hi) - ֻ�轫miλ��Ԫ����loλ��Ԫ�ػ���������ɻ���
    std::swap(_elem[lo],_elem[mi]);

    return mi;//�������
}

template<typename T>
Rank Vector<T>::partition(Rank lo,Rank hi) //[lo,hi]�ָ�����,�ҳ����
{

    T pivot = _elem[lo];


    while( lo != hi )
    {
        while( lo < hi && pivot <= _elem[hi] )  //��������ݲ����������ʱ
            --hi;    //���Ͻ�R���е���
        _elem[lo] = _elem[hi];  //�������ǰ��

        while( lo < hi && _elem[lo] <= pivot )  //��������ݲ�С��ǰ��ʱ
            ++lo;    //���Ͻ�L���е���
        _elem[hi] = _elem[lo];  //����������
    }

    _elem[lo] = pivot;  //����������

    return lo;//�������λ�� - ������еĿ��ٻ���
}

template<typename T>
void Vector<T>::QuickSort(Rank lo,Rank hi)  //[lo,hi)
{
    if( hi - lo < 2 ) return;   //��Ȼ����

    //Rank mi = partition(lo,hi-1);       //[lo,hi-1]����Ѱ����� - �汾A
    Rank mi = partition(lo,hi-1,1);


    /*

        ���ŵ�˼�룺

            ���β���

                ���ǰ��Ԫ�ض����������ĺ��Ԫ�أ������Ԫ�ض���С�����ǰ��Ԫ��

                �ؼ������ҵ����

            ���з�Ϊ������

                L < mi <= R
        //��������Ϊȫ���������,��ÿ�ζ��ᵼ�����еĻ��ּ����䲻����
        //���¸��ӶȴﵽO(n^2)
    */


    QuickSort(lo,mi);//[lo,mi) ����
    QuickSort(mi+1,hi);//[mi+1,hi)
}






//����ѡȡ�㷨-------------------------------------------------------------------------------------
template<typename T>
bool majority(Vector<T> arr,T& maj)
{
    maj = majCandidate(arr); //ѡȡһ�����ܵ����� - O(n)
    return majCheck( arr,maj );//�ж��Ƿ�Ϊ���� - O(n)
}//O(n)

template<typename T>
bool majCheck(Vector<T> arr, T& maj)
{
    int count = 0;//��ѡȡ��maj���ֵĴ���
    for( int i = 0; i < arr.get_size(); ++i )
        if( arr[i] == maj ) count++;

    return count*2 > arr.get_size();    //���ݴ����ж��Ƿ�Ϊ�������������� * 2 �ش��� ���������
}

template<typename T>
T majCandidate(Vector<T> arr)
{
    /*
        ������֮��
            ���arr��������,ֻ�����ѡȡx
            ��x������,��ô��ȥһ������һ��ǰ׺ - x�ĸ�����ͬ������������Ԫ��,��ô��׺�����������Ǹ�x
            ��x��������,��ôͬ����ȥ����һ��ǰ׺,�������ٵĸ���Ҳ����ط������ļ��ٸ�����,�ʺ�׺����Ȼ��������
    */
    T maj; //������һ����ѡ��
    for(int c = 0, i = 0; i < arr.get_size(); ++i)
    {
        if( c == 0 ) //ǰ׺��x�ĸ���Ϊ0
        {
            maj = arr[i];//maj(������ѡ�߾�Ϊ��ǰ���еĵ�һ��Ԫ��)
            c = 1;//�������Ȼ����Ϊ1
        }
        else
            maj == arr[i] ? ++c : --c;//��Ӧ�����Ӵ˼��������� ���� ����������������֮����,�����ټ���������
    }//O(n)

    return maj;//���ظ�������ѡ��
}

//�������е�RankΪk��Ԫ��ѡȡ�㷨

/*
���� - �����н���ȫ����,��ѡȡ��A[k] - O(nlogn) - ������
*/

/*
����1 - ��
        1.����Floyd�㷨����һ��С���� - O(n)
        2.����k��DelMax() - O(k*logn)
        3.�Ѷ�����RankΪk��Ԫ��
k����ʱ��O(nlogn)
*/
template<typename T> //�������ڶ��Ǵ󶥶ѽ��� - ������Ϊk - ������Ϊn-1-k
T Vector<T>::select_k_ver1(Rank k,Rank lo, Rank hi)
{
    PQ_CompHeap<T> H(_elem, lo, hi); //��֯Ϊ�󶥶�

    int i = hi - lo - 1 - k;
    while(i--)
    {
        H.Del_max();
    }
    return H.get_max();
}
/*
����2 - ��
        1.����Floyd�㷨������k��Ԫ����֯Ϊһ���󶥶� - O(k)
        2.����ʣ���n-k��Ԫ�� - ������һ��insert()-Del_max() - O(2 * (n-k)*logk)

                �ѵĹ�ģ��k���k+1ʱ,�Ѷ�Ԫ�ؼ�Ϊ��ǰ������Ϊk��Ԫ��,��ʣ�µ�����Ԫ�ض����β�����,�����������Ѷ���Ϊ����

        3.�Ѷ�����RankΪk��Ԫ��
k����ʱ���߹�Сʱ - �临�Ӷ�ΪO(n)
����kȡ��ʱ - �ᵽ��O(nlogn)
*/
template<typename T>
T Vector<T>::select_k_ver2(Rank k,Rank lo, Rank hi)
{
    PQ_CompHeap<T> H(_elem, lo, lo+k); //��֯Ϊ�󶥶�

    for(int i = lo + k; i < hi-1; ++i)
    {
        H.insert(_elem[i]);
        std::cout << H.Del_max() << std::endl;
    }
    H.insert(_elem[hi-1]);

    return H.get_max();
}//�˺����Ǵ����-----------------------------�ȴ�����


/*
    ����3 - ��
        1.��ȡk��Ԫ����֯Ϊ�󶥶�H-O(k)
        2.ȡʣ���n-k��Ԫ����֯ΪС����O(n-k)
        3.�Ƚ�H��G�ĶѶ� - ֻҪH_max > G_min - �ͽ����߽��� - �ٽ���һ�����˲��� - O(2 * (logk + log(n-k)))
        4.ֱ��H_max <= G_min,��ôG�ĶѶ���Ϊ��Ϊk��Ԫ��

--------------------------------------------------------------------------------

    ���ϼ��ֶѵķ����������öѵĶ�����,����ƫ���Ի�ʹ�ü���һЩԪ�رȽ� - ��������k��ѡȡ����ᵼ����Щ�������Ӷȹ���


*/


//����ѡȡ�㷨
template<typename T>
T Vector<T>::QuickSelect(Rank k,Rank lo, Rank hi)
{
    /*
        ���û�������partition�㷨 - ���ظ�������i A[i] = x
        ��k == i ����������
        ��k < i  �����������������֮������[lo,i)
        ���� i <= k �����������������֮������[i+1,hi)
    */
/*
    //�ݹ�ʵ��
    Rank i = partition(lo,hi);//[lo,hi)������Ԫ����Ϊ���ʱ���� - O(n)
    if(i == k) return _elem[i];
    else if(k < i) return QuickSelect(k,lo,i);
    else return QuickSelect(k,i+1,hi);

�ݹ�������������Ϊ���Դ� - ����ΪO(n) - ����O(n^2)
*/

    //����ʵ��
    while(lo < hi)
    {
        Rank i = lo; Rank j = hi - 1;
        T pivot = _elem[i];
        //--------------------------------��ѭ��
        while(i < j) //[i,j]�����һ��partition�ָ�
        {
            while( (i < j) && (pivot <= _elem[j]) ) j--; //�Ҳ��������
                _elem[i] = _elem[j];
            while( (i < j) && (_elem[i] < pivot) )  i++; //����������
                _elem[j] = _elem[i];
        }//assert i == j
        _elem[i] = pivot;
        //--------------------------------O(hi - 1 + lo) == O(n)
        if(k == i) return _elem[i];
        else if(k < i) hi = i; //[lo,i)
        else lo = i + 1;
    }//assert _elem[i] ��Ϊ����

//��ѭ���������� - �����ʱ��ΪO(n^2)

}

template<typename T>
T LinearSelect(Vector<T>& arr, Rank k)
{
    /*
        1.ȷ��һ��С����Q,������еĹ�ģС��Q - ��������һ��ѡȡ�㷨���� - �ݹ�� - O(QlogQ) - Q�ǳ��� - ��O(1)
        2.��A���ȵķֳ�n/Q��������,ÿ�������н������� - ���������㷨
        3.��������е���λ��,��������֯��һ���µ�����    - ���������ҵ���λ���Ĳ���ֻ�� - (n/Q)*O(1)
        4.�ټ�����λ������λ�� - �ݹ����linearSelect([(hi - lo) / 2],lo,hi) - M - T(n / Q)
        5.�ٸ���M������Ԫ�طֳ���������,L(l < M) E(e == M) G(M < g) - һ�α��� - O(n)
        6.if(L.size() >= k) return LinearSelect(L,k)
          else if( L.size() + E.size() >= k ) return M;
          else return LinearSelect(G,k - L.size() - E.size()) - ����ע�����k�ĺ������е����� - ����ݹ���಻��T(3n/4)

        ���帴�Ӷ� T(n) = O(n) + T(n/Q) + T(3n/4) = O(20c*n) - O(n)
        �䳣ϵ������
    */

    int Q = 3;
    if( arr.get_size() <= Q ) return arr.QuickSelect(k, 0, arr.get_size());
    //����
    int j = 0;
    for(int i = 0; i < (arr.get_size() / Q); ++i,j += Q)
        arr.QuickSort(j,j+Q);
    if(j + Q > arr.get_size())
        arr.QuickSort(j, arr.get_size());

    //std::cout << "arr" << std::endl;
    //arr.traverse();

    //ȡ��λ�����������
    Vector<T> mids;
    int m = 0, n = 0;
    for(; n < (arr.get_size() / Q); ++n,m += Q)
    {
       //std::cout << "��λ����" <<  arr[(m + m + Q - 1) / 2] << std::endl;
        mids.put_back(arr[(m + m + Q - 1) / 2]);//ȡÿ��С���е���λ��
    }
    if(m + Q > arr.get_size())
       mids.put_back(arr[(m + arr.get_size() - 1) / 2]);

    //std::cout << "mids" << std::endl;
    //mids.traverse();

    T M = LinearSelect(mids,(mids,mids.get_size() / 2)); //ѡȡ�����е���λ��

    //�ٸ���M�����зֳ���������
    Vector<T> L; Vector<T> E; Vector<T> G;

    for(int m = 0; m < arr.get_size(); ++m)
    {
        if(arr[m] < M) L.put_back(arr[m]);
        else if(arr[m] == M) E.put_back(M);
        else G.put_back(arr[m]);
    }
    //�ٸ��������ֱַ�ݹ�
    if(L.get_size() >= k) return LinearSelect(L,k);
    else if(L.get_size() + E.get_size() >= k) return M;
    else return LinearSelect(G,k - L.get_size() - E.get_size());
}

template<typename T>
void Vector<T>::ShellSort(Rank lo, Rank hi)
{
    int n = hi - lo;
    if(n < 5) return QuickSort(lo,hi);
    int k = int(log(n+1) / log(2));      //���õ�ϣ������ - { 1, 3, 5, ����, 2^k-1 }

    while( true )
    {
        int w = int(pow(2,k) - 1);
        //std::cout << "k = " << k
                  //<< "w = " << w << std::endl;

        //�ɴ˸������Ͻ�һά�����߼��Ͽ��ɿ��(��)Ϊw�Ķ�ά����
        //����0 <= i < w-1�н������� - ���������������㷨(�����λ��) - ����/ð��
        /*
            0   1   2   3   ����  w-1
            w   ����              2w-1
            *
            *
            n-w ����      n-1

        A(m*n) - m(n / w����n / w + 1��) n(w��)
        ��i�е�k��Ԫ����ΪA[i + kw] 0 <= k < n/w
        */

        for(int i = 0; i < w; ++i) //��ÿ�н�������
        {
            for(int r = i + w; r < n; r += w ) //�Ե�i�н��в�������
            {
                //��ʼ1��Ԫ����Ȼ���� - �ӵڸ��е�2��Ԫ�ؿ�ʼ - �����з�ΪS/U
                //��S�в���Ԫ��
                int t = _elem[r]; //������Ԫ��
                int j = r - w;    //S���ұ߽�
                while( j >= 0 && _elem[j] > t ) //��jδԽ����߽粢�ҵ�ǰԪ���������Ԫ�ع��������ʱ
                {
                    _elem[j+w] = _elem[j]; //��Ԫ�غ���
                    j -= w;                //�ж���һ��Ԫ���������Ԫ�ص������ϵ
                }//assert - j = i - w(������Ԫ��Ϊ��СԪ��,����λ��j+w) / j(��ǰԪ�ز����ڴ�����Ԫ�� - �ʲ���Ԫ��λ��Ϊj+w)
                _elem[j+w] = t; //�ڲ���λ�ò��뵱ǰԪ��
            }
        }


        if(k == 1) break;

        k -= 1; //��С���
    }
}




#endif // ALGORI_H_INCLUDED
