#pragma once
#include"arrays.h"
//circuitos logicos
namespace mpv{
	void NOT(bool s[], bool x[], int n){
		int i;
		for(i=0; i<n; i++) {
			s[i]=not x[i];
		}
	}
	void OR(bool s[], bool x[], bool y[], int n){
		int i;
		for(i=0; i<n; i++) {
			s[i]=x[i] or y[i];
		}
	}
	
	void AND(bool s[], bool x[], bool y[], int n){
		int i;
		for(i=0; i<n; i++) {
			s[i]=x[i] and y[i];
		}
	}
	
	void XOR(bool s[], bool x[], bool y[], int n){
		int i;
		for(i=0; i<n; i++) {
			s[i]=x[i] xor y[i];
		}
	}
	
	void NOR(bool s[], bool x[], bool y[], int n){
		int i;
		for(i=0; i<n; i++) {
			s[i]= not(x[i] or y[i]);
		}
	}
	
	void NAND(bool s[], bool x[], bool y[], int n){
		int i;
		for(i=0; i<n; i++) {
			s[i]=not(x[i] and y[i]);
		}
	}
	
	void XNOR(bool s[], bool x[], bool y[], int n){
		int i;
		for(i=0; i<n; i++) {
			s[i]= not (x[i] xor y[i]);
		}
	}
	
	
	//circuitos aritmeticos
	void SUM(bool *C, bool *V,bool *N,bool *Z, bool s[], bool x[], bool y[],int n){   // suma desde 0 hasta i (sumara los numeros en un arreglo de izquierda a derecha)
		int i;
		bool S,X=x[n-1],Y=y[n-1];
		*C=0;
		for(i=0; i<n; i++) {
			S= x[i] xor y[i] xor *C;
			*C= y[i] and *C or x[i] and *C or x[i] and y[i];
			s[i]=S;
		}
		*V= not X and not Y and s[n-1] or X and Y and not s[n-1];
		for(*Z=s[0],i=1; i<n; i++) {
			*Z = *Z or s[i];
		}
		*Z = not *Z;
		*N=s[n-1];
	}
	
	void INC( bool *C, bool s[],bool x[], int n){
		int i;
		bool S;
		*C=1;
		arcpy(s,x,n);
		for(i=0; i<n; i++) {
	
			S= s[i] xor *C;
			*C=s[i] and *C;
			s[i]=S;
		}
	}
	
	//pasar de arreglo binario a entero decimal
	int bin_dec_SS(bool C,bool s[],int bits){
		int i,num=C*pot(2,bits);
		for(i=0; i<bits; i++) {
			num=num+s[i]*pot(2,i);
		}
		return num;
	}
	
	int bin_dec_CS(bool V,bool s[],int bits){
		int i,num=0;
		if(V==0) {
			if(s[bits-1]==1) {
				bool vacio,sneg[bits];
				NOT(sneg,s,bits);
				INC(&vacio,sneg,sneg,bits);
				for(i=0; i<bits; i++) {
					num=num+sneg[i]*pot(2,i);
				}
				return num*-1;
			}
			else {
				for(i=0; i<bits; i++) {
					num=num+s[i]*pot(2,i);
				}
				return num;
			}
		}
		else {
			if(s[bits-1]==0) {
				bool vacio,sneg[bits];
				NOT(sneg,s,bits);
				INC(&vacio,sneg,sneg,bits);
				for(i=0; i<bits; i++) {
					num=num+sneg[i]*pot(2,i);
				}
				return num*-1;
			}
			else {
				for(i=0; i<bits; i++) {
					num=num+s[i]*pot(2,i);
				}
				return num;
			}
		}
	}
}
