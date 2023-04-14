#include<iostream>
using namespace std;

template<typename type>
type** new_matrix(type**m,int fil, int col){
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
	int filas=10000,columnas=10000;
	int **matriz1,**matriz2;
	while(true){
		/*cout<<"\nFilas: ";cin>>filas;
		cout<<"Columnas: ";cin>>columnas;
		if(filas==0 or columnas==0)break;*/
		matriz1=new_matrix(matriz1,filas,columnas);
		matriz2=new_matrix(matriz2,filas,columnas);
	
		//system("pause");
	
		//delete_matrix(matriz1,filas);
		//delete_matrix(matriz2,filas);

	}
	
	getchar();	
	getchar();	
	getchar();
	return 0;
}
