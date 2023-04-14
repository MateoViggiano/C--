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
};

void pedirDatos(Armas Arma[]){
	for(int i=0;i<3;i++){
		fflush(stdin);
		printf("-----Arma %d-----",i+1);
		printf("\nIngrese el nombre del arma: ");
		fgets((Arma+i)->nombre,15,stdin);
		printf("Ingrese el daño: ");
		scanf("%d",&(Arma+i)->DAMAGE);
		printf("Ingrese las balas por minuto: ");
		scanf("%f",&(Arma+i)->RPM);
		printf("\n\n");
	}
}

void calcularEstadisticas(Armas Arma[]){
	for(int i=0;i<3;i++){
    	Arma[i].stats.SxSEC=Arma[i].RPM/60;
    	Arma[i].stats.SECxS=1/Arma[i].stats.SxSEC;
    	Arma[i].stats.STK=100/Arma[i].DAMAGE;
		if(100%Arma[i].DAMAGE!=0){
			Arma[i].stats.STK=Arma[i].stats.STK+1;
		}
		Arma[i].stats.TTK = Arma[i].stats.STK * Arma[i].stats.SECxS - Arma[i].stats.SECxS;
	}
}

void mostrarEstadisticas(Armas Arma[]){
	for(int i=0;i<3;i++){
    	printf("\nnombre: %s\n",Arma[i].nombre);
    	printf("daño: %d\n",Arma[i].DAMAGE);
    	printf("tiros por minuto: %f\n",Arma[i].RPM);
    	printf("tiros para matar: %d\n",Arma[i].stats.STK);
    	printf("tiros por segundo: %f\n",Arma[i].stats.SxSEC);
    	printf("segundos por tiro: %fseg\n",Arma[i].stats.SECxS);
    	printf("tiempo para matar: %fseg\n",Arma[i].stats.TTK);
	}
}

int main(){
	int i;
	struct Armas arma[3];
	pedirDatos(arma);
	calcularEstadisticas(arma);
	mostrarEstadisticas(arma);
    /*for(i=0;i<3;i++){
    	arma[i].stats.SxSEC=arma[i].RPM/60;
    	arma[i].stats.SECxS=1/arma[i].stats.SxSEC;
    	arma[i].stats.STK=100/arma[i].DAMAGE;
		if(100%arma[i].DAMAGE!=0){
			arma[i].stats.STK=arma[i].stats.STK+1;
		}
		arma[i].stats.TTK = arma[i].stats.STK * arma[i].stats.SECxS - arma[i].stats.SECxS;
	}*/
    
    /*for(i=0;i<3;i++){
    	printf("\nnombre: %s\n",arma[i].nombre);
    	printf("daño: %d\n",arma[i].DAMAGE);
    	printf("tiros por minuto: %f\n",arma[i].RPM);
    	printf("tiros para matar: %d\n",arma[i].stats.STK);
    	printf("tiros por segundo: %f\n",arma[i].stats.SxSEC);
    	printf("segundos por tiro: %fseg\n",arma[i].stats.SECxS);
    	printf("tiempo para matar: %fseg\n",arma[i].stats.TTK);
	}*/
    
    
    return 0;

}
