#include<iostream>
#include<stdlib.h>
using namespace std;
int menor(int* punt_arreglo,int n){
	int i,men;
	for(i=1,men=punt_arreglo[0];i<n;i++){
		if(punt_arreglo[i]<men){
			men=*(punt_arreglo+i);
		}
	}
	return men;
}

int main(){
	int i,*arreglo,res;
	arreglo=new int[10];
	for(i=0;i<10;i++){
		cout<<"Num "<<i+1<<": ";
		cin>>arreglo[i];
	}
	res=menor(arreglo,10);
	cout<<res<<endl;
	delete[] arreglo;
	return 0;	
}
