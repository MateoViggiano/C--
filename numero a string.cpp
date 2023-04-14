#include<iostream>
using namespace std;

char* int_a_string(int num){
//-----------------Calculo la cantidad de digitos, incluyendo signo '-'
	bool neg=false;
	int cont=0;
	if(num<0){	//Veo si tiene signo, de ser asi se lo saco, incremento el contador y activo el flag de signo
		num*=-1;
		neg=true;
		cont++;
	}
	int aux=num;
	do{			//Cuento la cantdad de digitos
		aux/=10;
		cont++;	
	}while(aux>0);
//--------------------------------------------
	char* str=new char[cont+1];
	aux=num;
	int n,i=0;
	if(neg==true)
		str[i]='-';
	
	i=cont-1;
	do{
		n=aux%10;
		aux/=10;
		switch(n){
			case 0:str[i]='0';break;
			case 1:str[i]='1';break;
			case 2:str[i]='2';break;
			case 3:str[i]='3';break;
			case 4:str[i]='4';break;
			case 5:str[i]='5';break;
			case 6:str[i]='6';break;
			case 7:str[i]='7';break;
			case 8:str[i]='8';break;
			case 9:str[i]='9';break;
		}
		i--;
	}while(aux>0);
	str[cont]='\0';
	return str;//devuelve un arreglo dinamico, recordar eliminarlo
}

int coma_a_int(float num,int coma){	//devuelve como entero el numero despues de la coma de un flotante
	num=num-int(num);
	int i;
	for(i=0;i<coma;i++){
		num*=10;
	}
	return int(num);
}

char* float_a_string(float num,int coma=2){	//num: numero flotante a convertir en string
	bool neg=false;							//coma: cantidad de numeros que se mostraran despues de la coma
	int cont=0;
	if(num<0){	//Veo si tiene signo, de ser asi se lo saco, incremento el contador y activo el flag de signo
		num*=-1;
		neg=true;
		cont++;
	}
	int fnum=coma_a_int(num,coma);
	int inum=int(num);//separo la parte entera	
	int aux=inum;
	do{			//Calculo cantidad de digitos de inum
		aux/=10;
		cont++;
	}while(aux>0);
	cont=cont+coma+1;	//Al contador le sumo coma(cantidad de numeros despues de las coma)+1(para el '.')
	char*str=new char[cont+1];//Reservo memoria para un string del tamaño de cont+1		(+1 para el '\0')
	if(neg==true)
		str[0]='-';
	aux=fnum;
	int n;
	int i;
	if(coma>0){
		i=cont-1;
		do{
			n=aux%10;
			aux/=10;
			switch(n){
				case 0:str[i]='0';break;
				case 1:str[i]='1';break;
				case 2:str[i]='2';break;
				case 3:str[i]='3';break;
				case 4:str[i]='4';break;
				case 5:str[i]='5';break;
				case 6:str[i]='6';break;
				case 7:str[i]='7';break;
				case 8:str[i]='8';break;
				case 9:str[i]='9';break;
			}
			i--;
		}while(aux>0);
		str[i]='.';
		str[cont]='\0';
	}
	else{
		i=cont-2;
		str[i]='\0';
	}
	i--;
	aux=inum;
	do{
		n=aux%10;
		aux/=10;
		switch(n){
			case 0:str[i]='0';break;
			case 1:str[i]='1';break;
			case 2:str[i]='2';break;
			case 3:str[i]='3';break;
			case 4:str[i]='4';break;
			case 5:str[i]='5';break;
			case 6:str[i]='6';break;
			case 7:str[i]='7';break;
			case 8:str[i]='8';break;
			case 9:str[i]='9';break;
		}
		i--;
	}while(aux>0);
	return str;
}

int main(){
	float a=-6218.574;
	char* c=float_a_string(a);//se reservo memoria para la cadena 'c'
	puts(c);
	printf("\n%s",c);
	delete[] c;
	return 0;
}