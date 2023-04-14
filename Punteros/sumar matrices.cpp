#include<iostream>
using namespace std;

template<typename type>
type** new_matrix(type** m,int fil, int col){
	int i;
	m=new type*[fil];
	for(i=0;i<fil;i++){
		m[i]=new type[col];
	}
	return m;
}
template<typename type>
void delete_matrix(type** m,int fil){
	int i;
	for(i=0;i<fil;i++){
		delete[] m[i];
	}
	delete[] m;
}
template<typename type>
void rellenar_matriz(type** m,int fil, int col){
	int i,j;
	for(i=0;i<fil;i++){
		for(j=0;j<col;j++){
			cout<<"["<<i<<"]["<<j<<"]";
			cin>>*(*(m+i)+j);
		}
	}
}
template<typename type>
void imprimir_matriz(type** m,int fil,int col){
	int i,j;
	for(i=0;i<fil;i++){
		for(j=0;j<col;j++){
			cout<<"["<<i<<"]["<<j<<"]="<<m[i][j]<<"\t>>"<<&m[i][j]<<endl;
		}
	}
}
template<typename type>
type** sumar_matrices(type**m1,type**m2,int fil,int col){
	int i,j;
	type**m3;
	m3=new_matrix(m3,fil,col);
	for(i=0;i<fil;i++){
		for(j=0;j<col;j++){
			m3[i][j]=m1[i][j]+m2[i][j];
		}
	}
	return m3;
}

int main(){
	int filas,columnas;
	float **matriz1,**matriz2,**matriz3;
	while(true){
		cout<<"Filas: ";cin>>filas;
		cout<<"Columnas: ";cin>>columnas;
		if(filas==0 or columnas==0)break;
		matriz1=new_matrix(matriz1,filas,columnas);
		matriz2=new_matrix(matriz2,filas,columnas);
		cout<<"Ingrese la matriz 1:"<<endl;
		rellenar_matriz(matriz1,filas,columnas);
		cout<<endl<<"Ingrese la matriz 2:"<<endl;
		rellenar_matriz(matriz2,filas,columnas);
		matriz3=sumar_matrices(matriz1,matriz2,filas,columnas);
		cout<<"\nMatriz1\n";
		imprimir_matriz(matriz1,filas,columnas);
		cout<<"Matriz2\n";
		imprimir_matriz(matriz2,filas,columnas);
		cout<<"Resultado\n";
		imprimir_matriz(matriz3,filas,columnas);
		delete_matrix(matriz1,filas);
		delete_matrix(matriz2,filas);
		delete_matrix(matriz3,filas);
		cout<<endl<<endl;
	}
	
	getchar();	
	getchar();	
	getchar();
	return 0;
}