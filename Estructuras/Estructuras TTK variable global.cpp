#include<stdio.h>

struct Estadisticas{
	int STK;
	float TTK,SECxS,SxSEC;
};

struct Armas{
	char nombre[15];
	int DAMAGE;
	float RPM;
	struct Estadisticas stats;
}arma[3];

void pedirDatos(){
	int i;
	for(i=0;i<3;i++){
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

int main(){
	int i;
	
	pedirDatos();

    for(i=0;i<3;i++){
    	arma[i].stats.SxSEC=arma[i].RPM/60;
    	arma[i].stats.SECxS=1/arma[i].stats.SxSEC;
    	arma[i].stats.STK=100/arma[i].DAMAGE;
		if(100%arma[i].DAMAGE!=0){
			arma[i].stats.STK=arma[i].stats.STK+1;
		}
		arma[i].stats.TTK = arma[i].stats.STK * arma[i].stats.SECxS - arma[i].stats.SECxS;
	}
    
    for(i=0;i<3;i++){
    	printf("\nnombre: %s\n",arma[i].nombre);
    	printf("daño: %d\n",arma[i].DAMAGE);
    	printf("tiros por minuto: %f\n",arma[i].RPM);
    	printf("tiros para matar: %d\n",arma[i].stats.STK);
    	printf("tiros por segundo: %f\n",arma[i].stats.SxSEC);
    	printf("segundos por tiro: %fseg\n",arma[i].stats.SECxS);
    	printf("tiempo para matar: %fseg\n",arma[i].stats.TTK);
	}
    
    
    return 0;

}
