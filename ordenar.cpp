#import<viggiano.h>
void ordenar(int a[],int n){
	int i,j,aux;
	for(i=0;i<n;i++){
		for(j=i,aux=a[i];j>0 and a[j-1]>aux;j--){
			a[j]=a[j-1];
		}
	a[j]=aux;
	
	}
}
int main(){
	int array[10]={5,7,4,2,-3,6,0,-8,9,13};
	ordenar(array,10);
	printar_0ai(array,'\n',10);
}