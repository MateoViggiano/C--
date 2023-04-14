#pragma once
#include<iostream>
//ordenamiento
namespace mpv{
	template <typename T>
	void insertion(T a[],int n,bool reverse=false){
		int i,j;
		T aux;
		if(reverse==false){
			for(i=0; i<n; i++) {
				for(j=i,aux=a[i]; aux<a[j-1] && j>0; j--) {
					a[j]=a[j-1];
				}
				a[j]=aux;
			}
		}
		else{
			for(i=0; i<n; i++) {
				for(j=i,aux=a[i]; aux>a[j-1] && j>0; j--) {
					a[j]=a[j-1];
				}
				a[j]=aux;
			}
		}	
	}
	template<typename T>
	void selection(T a[],int n,bool reverse=false){
		int i,j,selec;
		T aux;
		if(reverse==false) {
			for(i=0; i<n; i++) {
				for(selec=i,j=i; j<n; j++) {
					if(a[j]<a[selec]) {
						selec=j;
					}
				}
				aux=a[i];
				a[i]=a[selec];
				a[selec]=aux;
			}
		}
		else {
			for(i=0; i<n; i++) {
				for(selec=i,j=i; j<n; j++) {
					if(a[j]>a[selec]) {
						selec=j;
					}
				}
				aux=a[i];
				a[i]=a[selec];
				a[selec]=aux;
			}
		}
	}
	template<typename T>
	void reverse(T a[],int n){
		int i,j;
		T aux;
		for(i=0,j=n-1;i!=n/2;i++,j--){
			aux=a[i];
			a[i]=a[j];
			a[j]=aux;
		}
	}
	// Input/Output de arrays
	template<typename T>
	void str__Print(T a,int b,T* dir,const char *str){
		int sz=0,i,j;
		while(str[sz]){
			++sz;
		}
		++sz;
		char c[sz]= {0};
		for(i=0,j=0; i<sz; i++,j++) {
			c[j]=str[i];
			if(str[i]=='{') {
				c[j]='\0';
				printf("%s",c);
				if(str[i+1]=='a') {
					std::cout<<a;
				}
				else if(str[i+1]=='i') {
					printf("%d",b);
				}
				else if(str[i+1]=='d') {
					printf("0x%x",dir);
				}
				i+=2;
				j=-1;
			}
		}
		printf("%s",c);
	}
	//Array Input
	template<typename T>
	void getar(T a[],int n,const char str[]="[{i}]=",bool reverse=false){
		int i;
		if(reverse==false) {
			for(i=0; i<n; i++) {
				str__Print(a[i],i,a+i,str);
				std::cin>>a[i];
			}
		}
		else {
			for(i=n-1; i>=0; i--) {
				str__Print(a[i],i,a+i,str);
				std::cin>>a[i];
			}
		}
	}
	//Array Output
	template<typename T>
	void printar(T a[],int n, const char *str="{a}",const char* end=", ",const char* first="[",const char *last="]\n",bool reverse=false){
		int i;
		std::cout<<first;
		if(reverse==false) {
			for(i=0; i<n; i++) {
				str__Print(a[i],i,a+i,str);
				if(i!=n-1)
					std::cout<<end;
			}
		}
		else {
			for(i=n-1; i>=0; i--) {
				str__Print(a[i],i,a+i,str);
				if(i!=0)
					std::cout<<end;
			}
		}
		std::cout<<last;
	}
	//Rellenar arreglos
	template <typename T>
	void memfill(T a[], T x, int n){
		for(int i=0; i<n; i++) {
			a[i]=x;
		}
	}
	template<typename T>
	void memcopy(T* dest,T* source,unsigned int n){
		if(source>=dest)
			for(int i=0;i<n;i++)
				dest[i]=source[i];
		else
			for(int i=n-1;i>=0;i--)
				dest[i]=source[i];
	}
	template<typename T>
	void memmove(T* dest,T* source,unsigned int n){
		if(source>=dest)
			for(int i=0;i<n;i++)
				dest[i]=(T&&)source[i];
		else
			for(int i=n-1;i>=0;i--)
				dest[i]=(T&&)source[i];
	}
	template<typename T>
	bool memcomp(T a[], T b[],int n){// Retorna 0 si son iguales.
		for(int i=0;i<n;i++){
			if(a[i]!=b[i])
				return 1;
		}
		return 0;
	}
    template<typename T>
    void memdestructor(T* mem,long long n){
        for(long long i=0;i<n;i++)
            mem[i].~T();
    }
	//matrices
	template<typename T>
	void new_matrix(T**& m,int fil, int col){
		m=new T*[fil];
		for(int i=0; i<fil; i++) {
			m[i]=new T[col];
		}
	}
	template<typename T>
	void delete_matrix(T** m,int fil){
		for(int i=0; i<fil; i++) {
			delete[] m[i];
		}
		delete[] m;
	}
	template<typename T>
	void getmtrx(T** m,int fil, int col){
		int i,j;
		for(i=0; i<fil; i++) {
			for(j=0; j<col; j++) {
				std::cout<<"["<<i<<"]["<<j<<"]";
				std::cin>>*(*(m+i)+j);
			}
		}
	}
	template<typename T>
	void printmtrx(T** m,int fil,int col,bool printDir=false){
		int i,j;
		for(i=0; i<fil; i++) {
			for(j=0; j<col; j++) {
				std::cout<<"["<<i<<"]["<<j<<"]="<<m[i][j];
				if(printDir)
					std::cout<<"\t>>"<<&m[i][j];
				std::cout<<std::endl;
	
			}
		}
	}
}