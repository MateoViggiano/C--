#include<iostream>
#include<stdlib.h>
#include<cstring>
#define TYPE int
/*template<unsigned int size>
struct chunk{
	char a[size];
};

template <unsigned int size,typename T>
void cpy(T* a, T* b){
 	chunk<size*sizeof(T)>* A=(chunk<size*sizeof(T)>*)a;
	*A=*(chunk<size*sizeof(T)>*)b;
}*/
void cpy(void* dest,void* source,unsigned int n){
	char* d=(char*)dest,* s=(char*)source;
	for(int i=0;i<n;i++)
		d[i]=s[i];
}
void mcpy(void* dest,void* source,unsigned int n){
	char* d=(char*)dest,* s=(char*)source;		
	if(source>=dest)				
		for(int i=0;i<n;i++)
			d[i]=s[i];
	else
		for(int i=n-1;i>=0;i--)
			d[i]=s[i];
}
template<typename T>
void temp_mcpy(T* dest,T* source,unsigned int n){
	if(source>=dest)
		for(int i=0;i<n;i++)
			dest[i]=source[i];
	else
		for(int i=n-1;i>=0;i--)
			dest[i]=source[i];
}

template<unsigned int n>
struct chunk{
	char a[n];
};
template<unsigned int n>
void chkcpy(void* dest,void* source){
	chunk<n>* A=(chunk<n>*)dest;
	chunk<n> aux=*(chunk<n>*)source;				//se necesita un auxiliar por si la memoria esta superpuesta.
	*A=aux;
}
template<unsigned int n,typename T>
struct chnk{
	T a[n];
};
template<unsigned int n,typename T>
void chcpy(void* dest,void* source){
	chnk<n,T>* A=(chnk<n,T>*)dest;
	chnk<n,T> aux=*(chnk<n,T>*)source;				//se necesita un auxiliar por si la memoria esta superpuesta.
	*A=aux;
}

int main(){

	TYPE* a=(TYPE*) calloc(30,sizeof(TYPE));
	TYPE* b=(TYPE*) malloc(sizeof(TYPE)*30);
	int cont=0;
	for(int i=0;i<30;i++,cont++)
		b[i]=cont;
	mcpy(a,b,30*sizeof(TYPE));
	int M;scanf("%d",&M);
	//chcpy<(30-M),int>(a+M,a);
	//mcpy(a+M,a,(30-M)*sizeof(int));
	temp_mcpy(a+M,a,30-M);
	memmove(b+M,b,(30-M)*sizeof(TYPE));

	//a[0]=4343;
	for(int i=0;i<30;i++)
		std::cout<<a[i]<<", ";
	puts("");
	for(int i=0;i<30;i++)
		std::cout<<b[i]<<", ";

}