//#include<viggiano.h>
//using namespace std;
#include<stdio.h>
typedef struct Numeros{
	int num1;
	int num2;
	int num3;
}numeros;
int main(){
	numeros c;
	numeros*p=&c;
	printf("%d\n",&numeros);
	printf("size c=\t%d\n",sizeof(c));
	printf("&c=\t%d\n",&c);
	printf("c=\t%d\n",c);
	printf("&c.num1=%d\n",&c.num1);
	printf("&c.num2=%d\n",&c.num2);
	printf("&c.num3=%d\n",&c.num3);	

	return 0;

}
