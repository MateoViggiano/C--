#include<iostream>
using namespace std;
int** new_matrix(int fil, int col){
	int i,**m;
	m=new int*[fil];
	for(i=0;i<fil;i++){
		m[i]=new int[col];
	}
	return m;
}
void delete_matrix(int** m,int filas){
	int i;
	for(i=0;i<filas;i++){
		delete[] m[i];
	}
	delete[] m;
}
void rellenar_matriz(int** m,int fil, int col){
	int i,j;
	for(i=0;i<fil;i++){
		for(j=0;j<col;j++){
			printf("[%d][%d]",i,j);
			//cin>>m[i][j];
			cin>>*(*(m+i)+j);
		}
	}
}
void imprimir_matriz(int** m,int fil,int col){
	int i,j;
	for(i=0;i<fil;i++){
		for(j=0;j<col;j++){
			printf("[%d][%d]=%d\t>>%d\n",i,j,m[i][j],&m[i][j]);
		}
	}
}
int main(){
	int**matriz,filas,columnas,i;
	//creando matriz 1
	cout<<"Matriz1:\nFilas: ";cin>>filas;
	cout<<"Columnas: ";cin>>columnas;
	matriz=new_matrix(filas,columnas);
	rellenar_matriz(matriz,filas,columnas);
	cout<<endl<<endl;
	imprimir_matriz(matriz,filas,columnas);
	delete_matrix(matriz,filas);
	//memoria limpia
	//creando matriz 2
	cout<<endl<<endl<<"Matriz2:\nFilas: ";cin>>filas;
	cout<<"Columnas: ";cin>>columnas;
	matriz=new_matrix(filas,columnas);
	rellenar_matriz(matriz,filas,columnas);
	cout<<endl<<endl;
	imprimir_matriz(matriz,filas,columnas);
	delete_matrix(matriz,filas);
	//memoria limpia
	getchar();
	getchar();
	return 0;
}