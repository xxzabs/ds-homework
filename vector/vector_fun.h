#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include"vector.h"
using namespace std;

template <typename T>
void Vector<T>::copyFrom(T const*A,Rank lo,Rank hi){

if(0<lo&&lo<=hi)_elem=new T[_capacity=2*(hi-lo)];_size=0;
while (lo<hi)
 _elem[size++]=A[lo++]; 
} 


//template<typename T> Vector<T>&Vector<T>::operator=(Vector<T>const&V){
//	if (_elem) delete []_elem;
//	copyFrom(V._elem,0,V.size());
//	return *this;
//} 

template <typename T> void Vector<T>::expand(){
	if (_size<_capacity) return;
	if (_capacity<Base_size)_capacity=Base_size;
	T*oldElem=_elem;_elem=new T[_capacity<<=1];
	for(int i=0;i<_size;i++)
	_elem[i]=oldElem[i];
	delete []oldElem; 
} 

template <typename T> void Vector<T>::shrink(){

    if (_capacity<Base_size<<1) return;
    if (_size>_capacity>>2);
    T* oldElem=_elem;_elem=new T[_capacity>>=1];
	for(int i=0;i<_size;i++) _elem[i]=oldElem[i];
	delete [] oldElem; 
}
template <typename T>T& Vector<T>::operator[](Rank r)const{
   if(0<=r&&r<_size){
   return _elem[r];
}
}
template <typename T>void permute(Vector<T>& V){
	for(int i=V.size();i>0;i--)swap(V[i-1],V[rand()%i]); 
}

template<typename T>void Vector<T>::unsort(Rank lo,Rank hi){
	if(0<lo<=hi);
	T* V=_elem+lo;
	for(Rank i=hi-lo;i>0;i--)
	swap(V[i-1],V[rand()%i]);
}
template<typename T>static bool lt (T* a,T* b){return lt(*a,*b);}
template<typename T>static bool lt (T& a,T& b){return a<b;}
template<typename T>static bool eq (T* a,T* b){return eq(*a,*b);}
template<typename T>static bool eq (T& a,T& b){return a==b;}

template<typename T>
Rank Vector<T>::find(T const& e,Rank lo,Rank hi)const{
if(0<=lo&&lo<hi&&hi<_size);
while((lo<hi--)&&(e!=_elem[hi]));
return hi;
}
template<typename T>
Rank Vector<T>::insert(Rank r,T const& e){
	if(0<=r<=_size){
	
	expand();
	for(int i=_size;i>r;i--)_elem[i]=_elem[i-1];
	_elem[r]=e;_size++;
	return r;
	}
}

		
	template<typename T> void Vector<T>::bubbleSort(Rank lo,Rank hi){
		  for(int i=lo;i<hi-1;i++)
        	for(int j=lo;j<hi-1-i;j++)
                if(_elem[j]>_elem[j+1])
				{
                T temp=_elem[j];
                _elem[j]=_elem[j+1];
                _elem[j+1]=temp;
                }
	}
 	
	template<typename T> void init_Vector(Vector<T>&v);
template <typename T> void print_Vector(const Vector<T> &v);
template <typename T> T Vector<T>::remove (Rank r){
	T e=_elem[r];
	remove(r,r+1);
	return e;
}



