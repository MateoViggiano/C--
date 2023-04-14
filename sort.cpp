#include<iostream>
using namespace std;
template<typename T>
void insertion(T* a,int n){
	for(int i=0,j,aux;i<n;i++){
		for(j=i,aux=a[i];a[j-1]>aux and j>0;j--){
			a[j]=a[j-1];
		}
		a[j]=aux;
	}
}
int main(){
	int array[6]{4,7,52,7,-43,75};
	insertion(array,6);
	for(auto i:array){
		std::cout<<i<<", ";
	}
}