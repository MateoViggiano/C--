#include<iostream>
#include<math.h>
#define POT(BASE,EXP,RES)	RES=1;\
							for(int i=1;i<=EXP;i++){\
								RES*=BASE;\
							}
using namespace std;

long double pot(long double base,float exp){
	if(exp<0){
		exp*=-1;
		base=1/base;
	}
	int exp_int=exp;
	if(exp_int==exp){
	
		long double res=1;
		POT(base,exp,res);
		return res;
	}
	else{
		cout<<"Exponente fraccionario"<<endl;
		long long indice=1;
		for(;indice<10000 and exp-exp_int!=0;indice*=10){
			exp*=10;
			exp_int=exp;
		}
		cout<<"exp="<<exp<<endl
			<<"exp_int="<<exp_int<<endl
			<<"indice="<<indice<<endl;
		long double radicando=1;
		POT(base,exp_int,radicando);
		cout<<"radicando="<<radicando<<endl;
		long double raiz=radicando/2,aux;
		for(int i=2;i<1000000;i++){
			POT(raiz,indice,aux);
			//cout<<raiz<<"-->"<<aux<<endl;
			if(aux>radicando)
				while(aux>radicando){	
					POT(raiz,indice,aux);
					raiz-=raiz/i;
				}
			else if(aux<radicando)
				while(aux<radicando){
					POT(raiz,indice,aux);
					raiz+=raiz/i;
				}
			else
				return raiz;
		}
		return raiz;
	}
}

int main(){
	long double A,B;
	cin>>A;
	cin>>B;
	cout<<pot(A,B)<<endl;		// 15.58845727
	cout<<"\n\n\n"<<pow(A,B);
	return 0;
}