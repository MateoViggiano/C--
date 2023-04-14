#include<stdio.h>
#include"viggianolib/viggiano.h"
void analizarString(const char* string,char* min,char* max){
	int i;
	
	for(i=0,*min=*string,*max=*string;string[i]!='\0';i++){
		if(string[i]>*max){
			*max=string[i];
		}	
		if(string[i]<*min)
			*min=string[i];
	}
}

int main(){
	
	char palabraUno[20] = "hola";
	//char palabraDos[20] = "xyz";
	char palabraDos[20] = {'x','y','\0','z','a','d'};
	
	char min;
	char max;
	analizarString(palabraUno,&min,&max); //Usando palabra Uno
	printf("%s : min=%c max=%c\n\n", palabraUno, min, max);
	analizarString(palabraDos,&min,&max); //Usando palabra Dos
	printf("%s : min=%c max=%c", palabraDos, min, max);
	printf("\n%f",'@');
}