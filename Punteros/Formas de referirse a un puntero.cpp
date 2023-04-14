#include<viggiano.h>
using namespace std;
//using namespace vgg;
void imprimir(int a[],int n){
	int i;
	for(i=0;i<n;i++){
		cout<<"Direccion en la que se ubica el puntero\n";
		cout<<"&a\t>>"<<&a<<endl;
		cout<<"Direccion que contiene el puntero\n";
		cout<<"&*(a+i)\t>>"<<&*(a+i)<<endl;
		cout<<"a+i\t>>"<<a+i<<endl;
		cout<<"&a[i]\t>>"<<&a[i]<<endl;
		cout<<"Direccion a la que apunta el puntero\n";
		cout<<"a[i]\t>>"<<a[i]<<endl;
		cout<<"*(a+i)\t>>"<<*(a+i)<<endl;
		cout<<endl<<endl;
	}
}
int main(){
	int *arreglo,n=3;
	//arreglo 1
	cout<<"Ingrese numeros"<<endl;
	arreglo=new int[n];
	vgg::getar(arreglo,n);
	cout<<endl;
	imprimir(arreglo,n);
	delete[] arreglo;

	return 0;
}