#include<iostream>
#include"viggianolib/viggiano.h"
using namespace vgg;
using namespace std;
long long fact(long long n){
	int a=1;
	for(int i=1;i<=n;i++){
		a*=i;
	}
	return a;
}

double expo1(double n,int p=13){
	double a;
	for(int i=0;i<=13;i++){
		a+=(pot(n,i)/fact(i));
	}
	return a;
}
double expo2(double n,long double p=18000){
	return pot(1+(n/p),p);
}
double expo3(double n,long double p=100000000){
	double a=1+n;
	for(int i=2;i<=p;i++){
		a+=pot(n,i)/fact(i);
	}
	return a;
}
double expo4(double n,long double p=10000000){		//La mas exacta
	double sumatoria=1,productoria=1;
	for(int i=1;i<=p;i++){
		productoria*=n/i;
		sumatoria+=productoria;
	}
	return sumatoria;
}
#define N 78
int main(){
	cout<<expo1(N)<<endl;
	cout<<expo2(N)<<endl;
	cout<<expo2(N)<<endl;
	cout<<expo4(N)<<endl;
}