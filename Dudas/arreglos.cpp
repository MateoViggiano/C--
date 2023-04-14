#include<stdio.h>
int main(){
	
	int array[5]={54,8,-23,8,-54};
	printf("Array:\n");
	printf("%d\n",array[0]);
	printf("%d\n",array);
	printf("%d\n",&(array[0]));
	printf("%d\n",&array);
	printf("%d\n\n",sizeof(array));
	
	
	/*array=array+1;
	printf("Array:\n");
	printf("%d\n",array[0]);
	printf("%d\n",array);
	printf("%d\n",&(array[0]));
	printf("%d\n",&array);
	printf("\n\n");*/
	
	int* arrayDin=new int[5];
	for(int i=0;i<5;i++)
		arrayDin[i]=array[i];
	printf("Array dinamico:\n");
	printf("%d\n",arrayDin[0]);
	printf("%d\n",arrayDin);
	printf("%d\n",&arrayDin[0]);
	printf("%d\n",&arrayDin);
	printf("%d\n\n",sizeof(arrayDin));


	arrayDin++;
	printf("Array dinamico++:\n");
	printf("%d\n",arrayDin[0]);
	printf("%d\n",arrayDin);
	printf("%d\n",&arrayDin[0]);
	printf("%d\n",&arrayDin);
	printf("%d\n\n",sizeof(arrayDin));

	
	int* arrayPunt=array;
	printf("Puntero a array:\n");
	printf("%d\n",arrayPunt[0]);
	printf("%d\n",arrayPunt);
	printf("%d\n",&arrayPunt[0]);
	printf("%d\n",&arrayPunt);
	printf("%d\n\n",sizeof(arrayPunt));


	arrayPunt++;
	printf("Puntero a array++:\n");
	printf("%d\n",arrayPunt[0]);
	printf("%d\n",arrayPunt);
	printf("%d\n",&arrayPunt[0]);
	printf("%d\n",&arrayPunt);
	printf("%d\n\n",sizeof(arrayPunt));


	printf("\n\n\n\n%f",43);
	return 0;
}