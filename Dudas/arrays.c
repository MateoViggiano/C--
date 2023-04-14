#include<stdio.h>
int main(){
	int array[5]={54,8,-23,8,-54};
	printf("Array:\n");
	printf("%d\n",array[0]);
	printf("%d\n",array);
	printf("%d\n",&(array[0]));
	printf("%d\n",&array);
	printf("\n\n");

/*	array=array+1;
	printf("%d\n",array);
	printf("%d\n",&array[0]);
	printf("%d\n",&array);*/
/*	int* arrayDin=new int[5];
	for(int i=0;i<5;i++)
		arrayDin[i]=array[i];
	printf("Array dinamico:\n");
	printf("%d\n",arrayDin[0]);
	printf("%d\n",arrayDin);
	printf("%d\n",&arrayDin[0]);
	printf("%d\n",&arrayDin);
	printf("\n\n");
	
	arrayDin++;
	printf("Array dinamico++:\n");
	printf("%d\n",arrayDin[0]);
	printf("%d\n",arrayDin);
	printf("%d\n",&arrayDin[0]);
	printf("%d\n",&arrayDin);
	printf("\n\n");
	
	int* arrayPunt=array;
	printf("Puntero a array:\n");
	printf("%d\n",arrayPunt[0]);
	printf("%d\n",arrayPunt);
	printf("%d\n",&arrayPunt[0]);
	printf("%d\n",&arrayPunt);
	printf("\n\n");
	
	arrayPunt++;
	printf("Puntero a array++:\n");
	printf("%d\n",arrayPunt[0]);
	printf("%d\n",arrayPunt);
	printf("%d\n",&arrayPunt[0]);
	printf("%d\n",&arrayPunt);
	printf("\n\n");*/
	return 0;
}