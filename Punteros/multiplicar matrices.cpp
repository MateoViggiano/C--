#include<viggiano.h>
template<typename type>
type** multiplicar_matrices(type** m1,type** m2,int fil,int col){
	int i,j;
	type**m3=new_matrix(m3,fil,col);
	for(i=0;i<fil;i++){
		for(j=0;j<col;j++){
			m3[i][j]=m1[i][j]*m2[i][j];
		}
	}
	return m3;
}
using namespace std;
int main(){
	while(true){
	int f,c,**mat1,**mat2,**mat3;
	cout<<"Ingrese las filas: ";cin>>f;
	cout<<"Ingrese las columnas: ";cin>>c;
	if(f==0 or c==0)
		return 0;
	mat1=new_matrix(mat1,f,c);
	mat2=new_matrix(mat2,f,c);
	cout<<"Ingrese la matriz 1\n";
	getmtrx(mat1,f,c);
	cout<<"Ingrese la matriz 2\n";
	getmtrx(mat2,f,c);
	mat3=multiplicar_matrices(mat1,mat2,f,c);
	cout<<endl;
	cout<<"Matriz1\n";
	printmtrx(mat1,f,c,true);
	cout<<"Matriz2\n";
	printmtrx(mat2,f,c,true);
	cout<<"Matriz3\n";
	printmtrx(mat3,f,c,true);
	delete_matrix(mat1,f);
	delete_matrix(mat2,f);
	delete_matrix(mat3,f);
	}
}	