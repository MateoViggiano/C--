#include<stdio.h>
struct cmplx{
	float real,imaginaria;
};
struct cmplx sumacmplx(struct cmplx a,struct cmplx b){
	struct cmplx c;
	c.real=a.real+b.real;
	c.imaginaria=a.imaginaria+b.imaginaria;
	return c;
}
void scancmplx(struct cmplx *num){
	scanf("%f",&num->real);
	scanf("%f",&num->imaginaria);
}
void printcmplx(struct cmplx num){
	printf("%.2f",num.real);
	if(num.imaginaria>=0) printf("+");
	printf("%.2fi",num.imaginaria);
}
int main(){
	struct cmplx numA,numB,res;
	printf("Ingrese el primer numero: ");
	scancmplx(&numA);
	printf("Ingrese el segundo numero: ");
	scancmplx(&numB);
	res=sumacmplx(numA,numB);
	printcmplx(res);
	return 0;
}