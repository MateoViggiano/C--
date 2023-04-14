#include<iostream>
struct cmplx{
	float real,imaginaria;
};
cmplx sumacmplx(cmplx a, cmplx b){
	cmplx c;
	c.real=a.real+b.real;
	c.imaginaria=a.imaginaria+b.imaginaria;
	return c;
}
void scancmplx(cmplx *num){
	scanf("%f",&num->real);
	scanf("%f",&num->imaginaria);
}
void printcmplx(cmplx num){
	printf("%.2f",num.real);
	if(num.imaginaria>=0) printf("+");
	printf("%.2fi",num.imaginaria);
}
int main(){
	cmplx numA,numB,res;
	printf("Ingrese el primer numero: ");
	scancmplx(&numA);
	printf("Ingrese el segundo numero: ");
	scancmplx(&numB);
	res=sumacmplx(numA,numB);
	printcmplx(res);
	return 0;
}