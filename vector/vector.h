#include<iostream>
#include<cstdlib>
using namespace std;
typedef int Rank;
#define Base_size 10
#define DEFAULT_CAPACITY 10
template <typename T>
class Vector{
protected:
  Rank _size;int _capacity;T* _elem;
  void copyFrom (T const* A,Rank lo, Rank hi);
  void expand();
  void shrink();
  bool bubble(Rank lo,Rank hi);
  void bubbleSort(Rank lo,Rank hi);
  Rank max(Rank lo,Rank hi);
  void selectionSort(Rank lo,Rank hi) ;
  	void merge(Rank lo,Rank hi);
	void mergeSort(Rank lo,Rank hi);
	//Rank partition (Rank lo,Rank hi);
	void quickSort(Rank lo,Rank hi);
	void heapSort(Rank lo,Rank hi);

public:
	Vector(int c=Base_size,int s=0,T y=0)
		{_elem = new T[_capacity = c];for(_size=0;_size<s;_elem[size++]=y);}	
	Vector (T const* A,Rank n){ copyFrom(A,0,n); }
	Vector (T const* A,Rank lo,Rank hi){ copyFrom(A,lo,hi);}
	Vector (Vector<T> const& V){copyFrom(V._elem,0,V._size);}
	Vector (Vector<T> const& V,Rank lo,Rank hi){copyFrom( V._elem,lo,hi); }
   // bool bubble(Rank lo,Rank hi);
   // void bubbleSort(Rank lo,Rank hi);
	~Vector() { delete [] _elem;}
	
	Rank size() const {return _size;}
	bool empty() const {return !_size;}
	int disorted() const;
	Rank find ( T const& e)const{return find(e,0,_size);}
	Rank find (T const& e,Rank lo,Rank hi)const;
	Rank search(T const& e)const{
		return(_size<=0)?-1:search(e,0,_size);
	}
	Rank search(T const& e,Rank lo,Rank hi)const;
	
//	T& operator[] (Rank r) const;
//	Vector<T> &operator= ( Vector<T> const& );
	T remove( Rank r );
	int remove(Rank lo,Rank hi);
	Rank insert(Rank r,T const& e);
	Rank insert(T const& e){ 
		return insert(_size,e); }
	void sort(Rank lo, Rank hi);
	void sort() {sort(0,_size);}
	int deduplicate();
	void unsort(Rank lo,Rank hi);
	void unsort(){unsort(0,_size);}
	int uniquify();
	void traverse(void(*)(T&));
	template<typename VST>void traverse(VST&);
}; 
//——————————————————————————————————————————————————————// 
//copyfrom
template <typename T>
void Vector<T>::copyFrom(T const*A, Rank lo, Rank hi){
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo<hi)
		_elem[_size++] = A[lo++];
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem) delete []_elem;
	copyFrom (V._elem,0,V._size());
	return *this;
}//=号重载,满足向量要求 

template <typename T>
T& Vector<T>::operator [] ( Rank  r) const {  //重载下标操作符
    return _elem[r];   //assert: 0 <= r < _size
}

template <typename T>
int Vector<T>::check(Rank lo, Rank hi, double m1, double m2)
{
	int count = 0;
	for(int i=lo;i<hi;i++)
	{
		if(_elem[i]>=m1&&_elem[i]<m2)
		{
			_elem[count]=_elem[i];
			count++;
		}
	}
	return count;
}
//扩容expand
template <typename T>
void Vector<T>::expand()
{
	if(_size < _capacity) return;//未满 不扩容 
	if(_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY; //保证不低于原来的容量 
	T *oldElem = _elem; _elem = new T[_capacity <<= 1];
	for(int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete []oldElem;//释放原空间 
}

//缩容shrink
template <typename T>
void Vector<T>::shrink()
{
	if(_capacity < DEFAULT_CAPACITY << 1)return;
	if(_size << 2 > _capacity)return;
	T* oldElem = _elem; _elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)_elem[i] = oldElem[i];
	delete []oldElem;
}
//插入 
template <typename T>
Rank Vector<T>::insert ( Rank r, T const& e )
{
	expand();//有需要就先扩容 
	for(int i=_size; i>r; i--)
		_elem[i] = _elem[i-1];
	_elem[r] = e;
	_size++;
	return r;
}
//查找
template <typename T> 
Rank Vector<T>::find ( T const& e, Rank lo, Rank hi ) const
{
	while ((lo < hi--)&&(e != _elem[hi] ) );
	return hi;
}
template <typename T>
static Rank binSearch(T* A, T const& e, Rank lo,Rank hi)//二分查找 
{
	while(1<hi - lo)
	{
		Rank mi = (lo < hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi;
	}
	return (e == A[lo]) ? lo : -1;
}

//置乱 
template <typename T>
void Vector<T>::unsort ( Rank lo, Rank hi )
{
	T* V = _elem + lo;
	for(Rank i = hi - lo;i > 0; i--)
		swap(V[i-1],V[rand() % i]);
} //对[lo, hi)置乱

//区间删除
template <typename T>
int Vector<T>::remove ( Rank lo, Rank hi )
{
	if( lo == hi)return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();//如需要 缩容 
	return hi - lo; 
 } 
 //单元素删除
template <typename T>
T Vector<T>::remove ( Rank r )
{
	T e = _elem[r];//备份被删除的元素 
	remove(r, r+1);
	return e;
}
//唯一化
template <typename T>
int Vector<T>::deduplicate() //无序去重
{
	int oldSize = _size;
	Rank i = 1;
	while(i < _size)
		(find(_elem[i], 0, i) < 0)?i++:remove( i );
	return oldSize - _size; 
}
template <typename T>
int Vector<T>::uniquify()
{
	Rank i = 0,j = 0;
	while ( ++j < _size)
		if( _elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = ++i; shrink();
	return j - i;
}
//有序性甄别
template <typename T>
int Vector<T>::disordered() const
{
	int n = 0;
	for(int i = 1;i < _size; i++)
		if( _elem[i-1] > _elem[i] ) n++;
	return n;//当且仅当n=0时向量有序 
}
//排序


template <typename T> 
bool Vector<T>::bubble(Rank lo, Rank hi) { //一趟扫描交换
   bool sorted = true; 
   while (++lo < hi) 
      if (_elem[lo - 1] > _elem[lo]) 
	  {
         sorted = false; 
         swap(_elem[lo - 1], _elem[lo]); 
      }
   return sorted; //返回有序标志
}
template<typename T>
bool Vector<T>::bubble(Rank n, Rank lo, Rank hi)
{
	bool sorted = true;
	while (++lo < hi)
	{
		if (_elem[lo - 1]<_elem[lo])
		{
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);	//交换两个值
		}
	}	
	return sorted;
}
template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)	//冒泡排序
{
	while (!bubble(lo, hi--));
}
template<typename T>
void Vector<T>::bubbleSort(Rank n, Rank lo, Rank hi)	//冒泡排序
{
	while (!bubble(n, lo, hi--));
}


template <typename T> //有序向量的归并
void Vector<T>::merge(Rank lo ,Rank mi, Rank hi){
    //以mi 为界，各自有序的子向量[lo,mi) [mi, hi)
    T*  A = _elem + lo; //合并后的向量A[0,hi-lo) = _elem[lo,hi)
    int lb = mi - lo ; T* B = new T[lb] ;//前子向量B[0,lb) = _elem[lo,mi)
    for(Rank i = 0 ; i < lb ;B[i] = A[i++]);//复制前子向量,只有前面的有必要复制，有被覆盖的风险
    int lc = hi-mi ; T* C = _elem + mi;//前子向量C[0,lc) = _elem[mi,hi)
    for(Rank i = 0 , j = 0,k = 0 ; (j < lb)||(k < lc);){
        // 将B[j]和C[k]中的小者续至A的末尾
        if((j < lb) && (!(k < lc) || B[j] <= C[k])) A[i++] = B[j++];
        if((k < lc) && (!(j < lb) || C[k] <= B[j])) A[i++] = C[k++];
    }
    delete []B; //释放临时空间B
} // 归并后得到完整的有序向量 lo,hi



//分治策略
template <typename T> //有序向量的归并排序
void Vector<T>::mergeSort(Rank lo , Rank hi){
    if (hi - lo < 2) return; //一直分治到单元素区间，此时自然顺序
    int mi = (lo + hi) >>1; // 找到中轴点
    mergeSort(lo,mi); mergeSort(mi,hi); merge(lo,mi,hi); //分治，然后归并
}

#endif




