#include<iostream>
using namespace std;
int main(){
	int i,arreglo[10],*punt_arreglo,men;
	for(i=0;i<10;i++){
		cout<<"Num "<<i+1<<": ";
		cin>>arreglo[i];
	}

	punt_arreglo = arreglo;
	
	for(i=1,men=*punt_arreglo;i<10;i++){
		if(*(punt_arreglo+i)<men){
			men=*(punt_arreglo+i);
		}	
	}
	cout<<men;
	return 0;
}