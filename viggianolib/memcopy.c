#include<stdio.h>
#include<stdlib.h>
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
void memcopy(void* dest,void* source,unsigned int n){
	char* d=dest,* s=source;
	if(source>=dest)
		for(int i=0;i<n;i++)
			d[i]=s[i];
	else
		for(int i=n-1;i>=0;i--)
			d[i]=s[i];
}

typedef struct {
	char a[30*sizeof(TYPE)];
}chunk;
void chkcpy(void* dest,void* source,unsigned int n){
	chunk* A=(chunk*)dest;
	chunk* B=(chunk*)source;
	*A=*B;
}

int main(){
	TYPE* a=(TYPE*) calloc(30,sizeof(TYPE));
	TYPE* b=(TYPE*) malloc(sizeof(TYPE)*30);
	TYPE cont=0;
	for(int i=0;i<30;i++,cont++)
		b[i]=cont;
		
/*	chunk* A=(chunk*)a;
	chunk* B=(chunk*)b;
	*A=*(B);*/
	//chunk<30*sizeof(TYPE)>* A=(chunk<30*sizeof(TYPE)>*)a;
	//*A=*(chunk<30*sizeof(TYPE)>*)b;
	chkcpy(a,b,30*sizeof(TYPE));
	a[0]=4343;
	for(int i=0;i<30;i++)
		printf("%d, ",a[i]);
	puts("");
	for(int i=0;i<30;i++)
		printf("%d, ",b[i]);

}