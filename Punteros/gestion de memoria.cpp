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
			for(j=0;j<columnas;j++){
				cout<<&matriz1[i][j]<<"\tRESERVED\n";	
			}
			
		}
		matriz2=new int*[filas];
		for(i=0;i<filas;i++){
			matriz2[i]=new int[columnas];
			for(j=0;j<columnas;j++){
				cout<<&matriz2[i][j]<<"\tRESERVED\n";	
			}
		}
		cout<<endl;
		for(i=0;i<filas;i++){
			for(j=0;j<columnas;j++){
				cout<<"["<<i<<"]["<<j<<"]>>"<<&matriz1[i][j]<<endl;
			}
		}
		for(i=0;i<filas;i++){
			for(j=0;j<columnas;j++){
				cout<<"["<<i<<"]["<<j<<"]>>"<<&matriz2[i][j]<<endl;
			}
		}		
		system("pause");
	
		for(i=0;i<filas;i++){
			delete[] matriz1[i];
			for(j=0;j<columnas;j++){
				cout<<&matriz1[i][j]<<"\tDELETED\n";
			}
			
		}
		delete[] matriz1;
		
		for(i=0;i<filas;i++){
			delete[] matriz2[i];
			for(j=0;j<columnas;j++){
				cout<<&matriz2[i][j]<<"\tDELETED\n";
			}
		}
		delete[] matriz2;
	}
	
	getchar();	
	getchar();	
	getchar();
	return 0;
}