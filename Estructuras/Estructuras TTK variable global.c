#include<stdio.h>
#define num 2


int i;

struct Estadisticas{
	int STK;
	float DPS,TTK,SECxS,SxSEC;
};

struct Armas{
	char nombre[15];
	int DAMAGE;
	float RPM;
	struct Estadisticas stats;
}arma[num];//arma va a ser una variable global, por lo que puedo modificarla desde cualquier funcion


void pedirDatos(){
	for(i=0;i<num;i++){
		fflush(stdin);
		printf("-----Arma %d-----",i+1);
		printf("\nIngrese el nombre del arma: ");
		fgets(arma[i].nombre,15,stdin);
		printf("Ingrese el daño: ");
		scanf("%d",&arma[i].DAMAGE);
		printf("Ingrese las balas por minuto: ");
		scanf("%f",&arma[i].RPM);
		printf("\n\n");
	}
}

void calcular(){
    for(i=0;i<num;i++){
    	arma[i].stats.SxSEC=arma[i].RPM/60;
    	arma[i].stats.SECxS=1/arma[i].stats.SxSEC;
    	arma[i].stats.STK=100/arma[i].DAMAGE;
		if(100%arma[i].DAMAGE!=0){
			arma[i].stats.STK=arma[i].stats.STK+1;
		}
		arma[i].stats.DPS = arma[i].stats.SxSEC * arma[i].DAMAGE;
		arma[i].stats.TTK = arma[i].stats.STK * arma[i].stats.SECxS - arma[i].stats.SECxS;
	}	
}

void mostrar(){
	for(i=0;i<num;i++){
    	printf("\nnombre: %s",arma[i].nombre);
    	printf("daño: %d\n",arma[i].DAMAGE);
    	printf("tiros por minuto: %f\n",arma[i].RPM);
    	printf("tiros para matar: %d\n",arma[i].stats.STK);
    	printf("tiros por segundo: %f\n",arma[i].stats.SxSEC);
    	printf("segundos por tiro: %fseg\n",arma[i].stats.SECxS);
    	printf("daño por segundo: %f\n",arma[i].stats.DPS);
    	printf("tiempo para matar: %fseg\n",arma[i].stats.TTK);
	}	
}

int main(){
	pedirDatos();
	calcular();
	mostrar();
    return 0;
}
