#include<viggiano.h>
const int f=3,c=3;
using namespace std;

void imprimir_matriz(int m[f][c],int fil,int col){
	int i,j;
	cout<<&m;
	for(i=0;i<fil;i++){
		if(i>0)
			cout<<"\t";
		cout<<"\t"<<">>"<<m+i;
		for(j=0;j<col;j++){
			if(j>0)
				cout<<"\t\t\t";
			cout<<"\t>>"<<(*(m+i)+j)<<"\t["<<i<<"]["<<j<<"]="<<*(*(m+i)+j)<<endl;
//						<<&m[i][j]				
//						<<&(*(*(m+i)+j))
		}
	}
}
int main(){
	//cout<<"Ingrese las filas: ";cin>>f;
	//cout<<"Ingrese las columnas: ";cin>>c;
	int i,j,m[f][c]={{53,15,-6},{2,0,31},{55,2,67}};
	imprimir_matriz(m,f,c);
	while(true){
		cout<<"i=";cin>>i;
		cout<<"j=";cin>>j;
	printf("m[%d][%d]=%d\n",i,j,*(*(m+i)+j));	
	}
	
	return 0;	
	
}