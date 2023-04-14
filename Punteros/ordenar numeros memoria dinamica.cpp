#include<viggiano.h>
using namespace std;
void ordenar(int a[],int n){
	int i,j,aux;
	for(i=0;i<n;i++){
		for(j=i,aux=a[i];aux<a[j-1] and j>0;j--){
			a[j]=a[j-1];
		}
		a[j]=aux;
	}
}
int main(){
	int *array;
	array=new int[10];
	getar_0ai(array,10);
	ordenar(array,10);
	cout<<endl;
	printar_0ai(array,'\n',10);
	delete[] array;
	return 0;
}