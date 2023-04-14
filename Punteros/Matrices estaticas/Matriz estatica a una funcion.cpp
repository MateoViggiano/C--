#include<iostream>
using namespace std;
void imprimir_matriz(int* m,int fil,int col){
	int k,i,j,fc=fil*col;
	cout<<&m;
	for(i=0,j=0,k=0;k<fc;k++,j++){
		if(j==col){
			j=0;
			i++;
		}
		if(k!=0)
			cout<<'\t';
		cout<<"\t>>"<<m+k<<"\t["<<i<<"]["<<j<<"]="<<m[k]<<endl;
	}
}


void rellenar_matriz(int*m,int fil,int col){
	int k,i,j,fc=fil*col;
	for(k=0,j=0,i=0;k<fc;k++,j++){
		if(j==col){
			j=0;
			i++;
		}
		cout<<"["<<i<<"]["<<j<<"]=";cin>>m[k];
	}
}

int main(){
	int f,c;
	cout<<"Ingrese las filas: ";cin>>f;
	cout<<"Ingrese las columnas: ";cin>>c;
	int i,j,m[f][c];
	int* p;
	p=&m[0][0];
	rellenar_matriz(p,f,c);
	imprimir_matriz(p,f,c);
	cout<<endl;
	while(true){
		cout<<"i=";cin>>i;
		cout<<"j=";cin>>j;
	printf("m[%d][%d]=%d\n",i,j,*(*(m+i)+j));	
	}
	
	return 0;	
	
}