#include<iostream>
#include"../vector/vector1.h"
#include<stdlib.h>
using namespace std;
int main(){
	int a[10]={0};
	Vector<int> v(a,10); 
	for (int i = 0; i<10 ; i++){
		a[i] = rand()%100;
		v[i] = a[i];
		cout <<v[i] <<endl;
}
    for(int i=0;i<10;i++){
   	v.unsort(1,10);
	cout<<v[i]<<endl;
	 
}
    //for(int i=0;i<10;i++){
    	
	//}



















































}

