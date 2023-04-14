#include<iostream>
#include<string.h>
using namespace std;
int vocales(char*,int*,int*,int*,int*,int*);
int main(){
	char* cadena;
	int cantidad=0,a=0,e=0,i=0,o=0,u=0;
	cadena=new char[50];
	cout<<"Ingrese la cadena: ";
	fgets(cadena,50,stdin);
	cantidad=vocales(cadena,&a,&e,&i,&o,&u);
	cout<<"Cantidad de:"<<"\na:"<<a<<"\ne:"<<e<<"\ni:"<<i<<"\no:"<<o<<"\nu:"<<u<<"\nCantidad de vocales:"<<cantidad;
	delete[] cadena;
	return 0;
}

int vocales(char cadena[],int* a,int* e,int* i,int* o,int* u){
	int j;
	for(j=0;cadena[j]!='\0';j++){
		switch(cadena[j]){
			case 'a':(*a)++;break;
			case 'e':(*e)++;break;
			case 'i':(*i)++;break;
			case 'o':(*o)++;break;
			case 'u':(*u)++;break;
			default:break;
		}
	}
	return *a+*e+*i+*o+*u;
}