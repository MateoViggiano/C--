#include<iostream>
using namespace std;
int main(){
	int filas,columnas,i,j;
	int **matriz1,**matriz2;
	while(true){
		cout<<"\nFilas: ";cin>>filas;
		cout<<"Columnas: ";cin>>columnas;
		if(filas==0 or columnas==0)break;

		matriz1=new int*[filas];
		for(i=0;i<filas;i++){
			matriz1[i]=new int[columnas];	
		}
		matriz2=new int*[filas];
		for(i=0;i<filas;i++){
			matriz2[i]=new int[columnas];
		}	
		system("pause");
	
		for(i=0;i<filas;i++){
			delete[] matriz1[i];	
		}
		delete[] matriz1;
		
		for(i=0;i<filas;i++){
			delete[] matriz2[i];
		}
		delete[] matriz2;
	}
	
	getchar();	
	getchar();	
	getchar();
	return 0;
}