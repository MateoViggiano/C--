#include<iostream>
int main(){
	
	int sz=50;
	int array[sz]={0};
	int base=10,n=462402348;
	for(int i=0;n!=0 and i<sz;i++){
		array[i]=n%base;
		n/=base;
	}
	bool print=false;
	for(int i=sz-1;i>=0;i--){
		if(not print)
			print=array[i];
		if(print){
			std::cout<<array[i];
		}
	}
}