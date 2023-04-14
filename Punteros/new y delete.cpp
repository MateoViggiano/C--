#include<viggiano.h>
using namespace std;
void imprimir(int a[],int n){
	int i;
	for(i=0;i<n;i++){
		cout<<a+i<<">>"<<a[i]<<endl;
	}
}
int main(){
	int *arreglo,n=10;
	//arreglo 1
	cout<<"Arreglo 1"<<endl;
	arreglo=new int[n];
	getar_0ai(arreglo,"Pos ",": ",n);
	cout<<endl;
	printar(arreglo,n,"{d}>>{a}");
	//imprimir(arreglo,n);
	delete[] arreglo;

	cout<<endl<<endl;
	//arreglo 2
	cout<<"Arreglo 2"<<endl;
	arreglo=new int[n];
	getar_0ai(arreglo,"Pos ",": ",n);
	cout<<endl;
	//printar(arreglo,n,"{d}>>{a}");
	imprimir(arreglo,n);
	delete[] arreglo;
	return 0;
}