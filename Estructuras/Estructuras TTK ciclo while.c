#include<stdio.h>
#include<string.h>
struct Estadisticas{
	int STK;
	float DPS,TTK,SECxS,SxSEC;
};

struct Armas{
	char nombre[15];
	int DAMAGE;
	float RPM;
	struct Estadisticas stats;
}/*aca se pueden declarar variables globales de tipo estructura*/;

int main(){
	int continuar=1;
	while(continuar==1){
		struct Armas arma;//declaro una variable local de tipo estructura
		fflush(stdin);
		printf("Ingrese el nombre del arma: ");
		fgets(arma.nombre,15,stdin);
		if(strcmp(arma.nombre,"end\n")==0){
			continuar=0;
		}
		else{
			printf("Ingrese el daño: ");
			scanf("%d",&arma.DAMAGE);
			printf("Ingrese las balas por minuto: ");
			scanf("%f",&arma.RPM);
			printf("\n");
	
	    	arma.stats.SxSEC=arma.RPM/60;
	    	arma.stats.SECxS=1/arma.stats.SxSEC;
	    	arma.stats.STK=100/arma.DAMAGE;
			if(100%arma.DAMAGE!=0){
				arma.stats.STK=arma.stats.STK+1;
			}
			arma.stats.DPS = arma.stats.SxSEC * arma.DAMAGE;
			arma.stats.TTK = arma.stats.STK * arma.stats.SECxS - arma.stats.SECxS;
	
	    	printf("\nnombre: %s",arma.nombre);
	    	printf("daño: %d\n",arma.DAMAGE);
	    	printf("tiros por minuto: %f\n",arma.RPM);
	    	printf("tiros para matar: %d\n",arma.stats.STK);
	    	printf("tiros por segundo: %f\n",arma.stats.SxSEC);
	    	printf("segundos por tiro: %fseg\n",arma.stats.SECxS);
	    	printf("daño por segundo: %f\n",arma.stats.DPS);
	    	printf("tiempo para matar: %fseg\n\n",arma.stats.TTK);
		}
	}

     return 0;

}