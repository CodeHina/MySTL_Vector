#ifndef ALGORI_H_INCLUDED
#define ALGORI_H_INCLUDED

#include <cmath> //for log() - log(4) / log(2) - 以2为底4的对数
#include "D:\C++\MyProject\PQ_CompHeap\PQ_CompHeap.h" //引入堆排序相关算法

//排序算法-----------------------------------------------------------------------------------------------


//冒泡排序 - 找寻逆序对的位置并扫描交换 - 最坏情况下仍然为O(n^2)
template<typename T>    //对无序区间进行操作
Rank Vector<T>::bubble(Rank lo,Rank hi)
{
    Rank last  = lo;        //初始化最后一个逆序对位置为lo - 考察的逆序对为[lo-1,lo]

    while (++lo < hi)       //区间从左向右扫描
    {
        if (_elem[lo-1] > _elem[lo])
        {
            last = lo;      //存在逆序对,则更新last,并对逆序对进行处理
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
        hi = bubble(lo,hi); //直接更新当前区间 -- 快速缩减
    }
    return;
}


//选择排序 - 找出最大下标再排序 - O(n^2) - 但是这种情况减少了交换的次数
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


//堆排序
template<typename T>
void Vector<T>::heap_sort( Rank lo, Rank hi )
{
    //将待排序区间组织为堆
    PQ_CompHeap<T> heap(_elem,lo,hi);//将待排序区间组织成一个堆 - flyod算法O(n)

    while( !heap.IsEmpty() )
    {
        _elem[--hi] = heap.Del_max();   //取出H中的最大元更新至已然排序的S中,是满足有序性的
                                        //实际思路是将堆顶的最大元与堆底末元素互换,完成S的生长和H的缩减
                                        //只涉及常数的辅助空间 - 是就地算法
    }
}



//插入排序
template<typename T>
void Vector<T>::insert_sort(Rank lo,Rank hi)
{
    int s_size = lo + 1;     //已经排序的元素的个数 - 初始就序区间为[lo,s_size)
    while(s_size < _size)
    {
        T val = _elem[s_size];
        Insert(val,bin_search(val,lo,s_size)+1);
        Remove(++s_size);   //插入排序要对插入后多余的元素进行处理
    }
    return;
}

//归并排序
template<typename T>
void Vector<T>::Merge(Rank lo,Rank mi,Rank hi)  //[lo,mi) / [mi,hi)
{
    //B \ C 数组合并到A数组中 - 且B[lo,mi) - C[mi,hi)  - A
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

    //归并 i j k
    for (int i = 0,j = 0,k = 0; (j < size_b) || (k < size_c);)
    {
        //把B的元素放入A中
        if ((j < size_b) && ((k >= size_c) || (B[j] <= C[k])))
            A[i++] = B[j++];
        //C -> A
        if ((k < size_c) && ((j >= size_b) || (B[j] > C[k])))
            A[i++] = C[k++];
    }

    delete [] B;                    //释放空间不能忘
    return;
}
template<typename T>
void Vector<T>::Merge_sort(Rank lo,Rank hi)
{
    //递归一定要有退出递归的条件
    if (hi - lo < 2)                           //递归基即为单位区间
        return;
    Rank mi  = (lo + hi) / 2;                  //分而治之 - 分成两个小区间
    //对两个小区间进行归并排序
    Merge_sort(lo,mi);
    Merge_sort(mi,hi);
    //对两个有序区间进行归并
    Merge(lo,mi,hi);
    return;
}


//快速排序
template<typename T>
Rank Vector<T>::partition(Rank lo,Rank hi,int a)
{
    //此变种 - 将待划分序列分为三部分 lo(轴点) L(左序列) R(右序列) U(未划分序列) 四部分 L < lo <= R
    //lo (lo,mi] (mi,k) [k,hi)
    T pivot = _elem[lo]; int mi = lo;
    for ( int k = lo + 1; k <= hi; k++ )
    {
        if(_elem[k] < pivot) //当前元素小于轴点
        {
            std::swap(_elem[++mi],_elem[k]); //(k++)考察下一元素 - 只需将R序列的首元素与当前元素进行交换 - 完成左序列的增长,R序列的快速向后滑动
        }
        //else k++  - R序列完成扩充
        //故只需写入for循环中
    }
    //循环结束lo L(lo,mi] R(mi,hi) - 只需将mi位置元素与lo位置元素互换即可完成划分
    std::swap(_elem[lo],_elem[mi]);

    return mi;//返回轴点
}

template<typename T>
Rank Vector<T>::partition(Rank lo,Rank hi) //[lo,hi]分割区间,找出轴点
{

    T pivot = _elem[lo];


    while( lo != hi )
    {
        while( lo < hi && pivot <= _elem[hi] )  //当轴点数据不大于其后序时
            --hi;    //不断将R序列递增
        _elem[lo] = _elem[hi];  //否则归入前序

        while( lo < hi && _elem[lo] <= pivot )  //当轴点数据不小于前序时
            ++lo;    //不断将L序列递增
        _elem[hi] = _elem[lo];  //否则归入后序
    }

    _elem[lo] = pivot;  //更新轴点的秩

    return lo;//返回轴点位置 - 完成序列的快速划分
}

template<typename T>
void Vector<T>::QuickSort(Rank lo,Rank hi)  //[lo,hi)
{
    if( hi - lo < 2 ) return;   //自然有序

    //Rank mi = partition(lo,hi-1);       //[lo,hi-1]区间寻找轴点 - 版本A
    Rank mi = partition(lo,hi-1,1);


    /*

        快排的思想：

            分治策略

                轴点前的元素都不大于轴点的后的元素，轴点后的元素都不小于轴点前的元素

                关键在于找到轴点

            序列分为三部分

                L < mi <= R
        //若此序列为全部相等序列,则每次都会导致序列的划分及极其不均衡
        //导致复杂度达到O(n^2)
    */


    QuickSort(lo,mi);//[lo,mi) 快排
    QuickSort(mi+1,hi);//[mi+1,hi)
}






//众数选取算法-------------------------------------------------------------------------------------
template<typename T>
bool majority(Vector<T> arr,T& maj)
{
    maj = majCandidate(arr); //选取一个可能的众数 - O(n)
    return majCheck( arr,maj );//判断是否为众数 - O(n)
}//O(n)

template<typename T>
bool majCheck(Vector<T> arr, T& maj)
{
    int count = 0;//此选取的maj出现的次数
    for( int i = 0; i < arr.get_size(); ++i )
        if( arr[i] == maj ) count++;

    return count*2 > arr.get_size();    //根据次数判断是否为众数（众数次数 * 2 必大于 总体个数）
}

template<typename T>
T majCandidate(Vector<T> arr)
{
    /*
        减而治之：
            如果arr存在众数,只需从中选取x
            若x是众数,那么减去一个这样一个前缀 - x的个数加同样个数的其他元素,那么后缀中众数还是那个x
            若x不是众数,那么同样减去这样一个前缀,众数减少的个数也不会必非众数的减少个数多,故后缀中仍然存在众数
    */
    T maj; //众数的一个候选者
    for(int c = 0, i = 0; i < arr.get_size(); ++i)
    {
        if( c == 0 ) //前缀中x的个数为0
        {
            maj = arr[i];//maj(众数候选者就为当前队列的第一个元素)
            c = 1;//其个数自然更新为1
        }
        else
            maj == arr[i] ? ++c : --c;//相应的增加此计数器个数 或者 非众数个数增加与之抵消,即减少计数器个数
    }//O(n)

    return maj;//返回该众数候选者
}

//无序序列的Rank为k的元素选取算法

/*
尝试 - 对序列进行全排序,在选取其A[k] - O(nlogn) - 最好情况
*/

/*
尝试1 - 堆
        1.利用Floyd算法建立一个小顶堆 - O(n)
        2.采用k次DelMax() - O(k*logn)
        3.堆顶即是Rank为k的元素
k过大时即O(nlogn)
*/
template<typename T> //这里由于堆是大顶堆建法 - 整数秩为k - 倒数秩为n-1-k
T Vector<T>::select_k_ver1(Rank k,Rank lo, Rank hi)
{
    PQ_CompHeap<T> H(_elem, lo, hi); //组织为大顶堆

    int i = hi - lo - 1 - k;
    while(i--)
    {
        H.Del_max();
    }
    return H.get_max();
}
/*
尝试2 - 堆
        1.利用Floyd算法将任意k个元素组织为一个大顶堆 - O(k)
        2.对于剩余的n-k个元素 - 各调用一次insert()-Del_max() - O(2 * (n-k)*logk)

                堆的规模从k变成k+1时,堆顶元素即为当前堆中秩为k的元素,将剩下的所有元素都做次操作后,最后插入操作后堆顶即为所求

        3.堆顶即是Rank为k的元素
k过大时或者过小时 - 其复杂度为O(n)
但是k取中时 - 会到达O(nlogn)
*/
template<typename T>
T Vector<T>::select_k_ver2(Rank k,Rank lo, Rank hi)
{
    PQ_CompHeap<T> H(_elem, lo, lo+k); //组织为大顶堆

    for(int i = lo + k; i < hi-1; ++i)
    {
        H.insert(_elem[i]);
        std::cout << H.Del_max() << std::endl;
    }
    H.insert(_elem[hi-1]);

    return H.get_max();
}//此函数是错误的-----------------------------等待调整


/*
    尝试3 - 堆
        1.任取k个元素组织为大顶堆H-O(k)
        2.取剩余的n-k个元素组织为小顶堆O(n-k)
        3.比较H和G的堆顶 - 只要H_max > G_min - 就将两者交换 - 再进行一次下滤操作 - O(2 * (logk + log(n-k)))
        4.直到H_max <= G_min,那么G的堆顶即为秩为k的元素

--------------------------------------------------------------------------------

    以上几种堆的方法都是利用堆的堆序性,这种偏序性会使得减少一些元素比较 - 但是由于k的选取问题会导致有些方法复杂度过高


*/


//快速选取算法
template<typename T>
T Vector<T>::QuickSelect(Rank k,Rank lo, Rank hi)
{
    /*
        采用划分轴点的partition算法 - 返回该轴点的秩i A[i] = x
        若k == i 即返回所求
        若k < i  即将所求区间减而治之到区间[lo,i)
        否则 i <= k 即将所求区间减而治之到区间[i+1,hi)
    */
/*
    //递归实现
    Rank i = partition(lo,hi);//[lo,hi)区间首元素作为轴点时的秩 - O(n)
    if(i == k) return _elem[i];
    else if(k < i) return QuickSelect(k,lo,i);
    else return QuickSelect(k,i+1,hi);

递归深度随机意义下为线性次 - 最坏情况为O(n) - 总体O(n^2)
*/

    //迭代实现
    while(lo < hi)
    {
        Rank i = lo; Rank j = hi - 1;
        T pivot = _elem[i];
        //--------------------------------内循环
        while(i < j) //[i,j]区间的一次partition分割
        {
            while( (i < j) && (pivot <= _elem[j]) ) j--; //右侧区间递增
                _elem[i] = _elem[j];
            while( (i < j) && (_elem[i] < pivot) )  i++; //左侧区间递增
                _elem[j] = _elem[i];
        }//assert i == j
        _elem[i] = pivot;
        //--------------------------------O(hi - 1 + lo) == O(n)
        if(k == i) return _elem[i];
        else if(k < i) hi = i; //[lo,i)
        else lo = i + 1;
    }//assert _elem[i] 即为所求

//外循环次数不定 - 故其最坏时间为O(n^2)

}

template<typename T>
T LinearSelect(Vector<T>& arr, Rank k)
{
    /*
        1.确定一个小常数Q,如果序列的规模小于Q - 采用任意一种选取算法即可 - 递归基 - O(QlogQ) - Q是常数 - 故O(1)
        2.将A均匀的分成n/Q个子序列,每个子序列进行排序 - 任意排序算法
        3.计算各序列的中位数,并将其组织成一个新的序列    - 以上两步找到中位数的操作只需 - (n/Q)*O(1)
        4.再计算中位数的中位数 - 递归调用linearSelect([(hi - lo) / 2],lo,hi) - M - T(n / Q)
        5.再根据M将序列元素分成三个部分,L(l < M) E(e == M) G(M < g) - 一次遍历 - O(n)
        6.if(L.size() >= k) return LinearSelect(L,k)
          else if( L.size() + E.size() >= k ) return M;
          else return LinearSelect(G,k - L.size() - E.size()) - 这里注意更新k的后序序列的新秩 - 这里递归最多不过T(3n/4)

        总体复杂度 T(n) = O(n) + T(n/Q) + T(3n/4) = O(20c*n) - O(n)
        其常系数过大
    */

    int Q = 3;
    if( arr.get_size() <= Q ) return arr.QuickSelect(k, 0, arr.get_size());
    //排序
    int j = 0;
    for(int i = 0; i < (arr.get_size() / Q); ++i,j += Q)
        arr.QuickSort(j,j+Q);
    if(j + Q > arr.get_size())
        arr.QuickSort(j, arr.get_size());

    //std::cout << "arr" << std::endl;
    //arr.traverse();

    //取中位数组成新序列
    Vector<T> mids;
    int m = 0, n = 0;
    for(; n < (arr.get_size() / Q); ++n,m += Q)
    {
       //std::cout << "中位数：" <<  arr[(m + m + Q - 1) / 2] << std::endl;
        mids.put_back(arr[(m + m + Q - 1) / 2]);//取每个小序列的中位数
    }
    if(m + Q > arr.get_size())
       mids.put_back(arr[(m + arr.get_size() - 1) / 2]);

    //std::cout << "mids" << std::endl;
    //mids.traverse();

    T M = LinearSelect(mids,(mids,mids.get_size() / 2)); //选取此序列的中位数

    //再根据M将序列分成三个部分
    Vector<T> L; Vector<T> E; Vector<T> G;

    for(int m = 0; m < arr.get_size(); ++m)
    {
        if(arr[m] < M) L.put_back(arr[m]);
        else if(arr[m] == M) E.put_back(M);
        else G.put_back(arr[m]);
    }
    //再根据三部分分别递归
    if(L.get_size() >= k) return LinearSelect(L,k);
    else if(L.get_size() + E.get_size() >= k) return M;
    else return LinearSelect(G,k - L.get_size() - E.get_size());
}

template<typename T>
void Vector<T>::ShellSort(Rank lo, Rank hi)
{
    int n = hi - lo;
    if(n < 5) return QuickSort(lo,hi);
    int k = int(log(n+1) / log(2));      //采用的希尔序列 - { 1, 3, 5, ……, 2^k-1 }

    while( true )
    {
        int w = int(pow(2,k) - 1);
        //std::cout << "k = " << k
                  //<< "w = " << w << std::endl;

        //由此根据以上将一维向量逻辑上看成宽度(列)为w的二维向量
        //并对0 <= i < w-1列进行排序 - 采用输入敏感性算法(逆序对位置) - 插入/冒泡
        /*
            0   1   2   3   ……  w-1
            w   ……              2w-1
            *
            *
            n-w ……      n-1

        A(m*n) - m(n / w或者n / w + 1行) n(w列)
        第i列第k个元素秩为A[i + kw] 0 <= k < n/w
        */

        for(int i = 0; i < w; ++i) //对每列进行排序
        {
            for(int r = i + w; r < n; r += w ) //对第i列进行插入排序
            {
                //初始1个元素自然有序 - 从第该列第2个元素开始 - 将序列分为S/U
                //在S中插入元素
                int t = _elem[r]; //待插入元素
                int j = r - w;    //S的右边界
                while( j >= 0 && _elem[j] > t ) //当j未越出左边界并且当前元素与待插入元素构成逆序对时
                {
                    _elem[j+w] = _elem[j]; //大元素后移
                    j -= w;                //判断下一个元素与待插入元素的逆序关系
                }//assert - j = i - w(待插入元素为最小元素,插入位置j+w) / j(当前元素不大于待插入元素 - 故插入元素位置为j+w)
                _elem[j+w] = t; //在插入位置插入当前元素
            }
        }


        if(k == 1) break;

        k -= 1; //减小宽度
    }
}




#endif // ALGORI_H_INCLUDED
