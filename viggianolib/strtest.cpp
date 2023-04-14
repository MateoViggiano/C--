#include<stdio.h>
#include<stdlib.h>
#include"viggiano.h"
using namespace vgg;
using namespace std;
void* operator new(size_t size){
	static int count=0;
	cout<<"\nALLOCATION COUNT: "<<++count<<endl;
	return malloc(size);
}


#define N 20
#define MAIN 4
#if MAIN==0
int main(){
	Str str1="Esto es un string ";
	Str str2="Esto es otro string ";
	Str str3="Esto tambien es un string";
	str1+=str2+"(otro string)"+str3;
	str2.insert(4," de verdad que");
	str2.insert(str2.len(),", lo juro");
	str2+=" string";
	str2=str2+". Le sumo otro string";
	str2+=". Le sumo otro string";
	cout<<str2;
	Str str4="a";
	cout<<endl;
	for range(i,8){
		str4=str4+"A";
		cout<<str4<<endl;
		cout<<str4.len()<<endl;
	}
}
#elif MAIN==1
int main(){
	Str str1;
	getstr(str1);
	cout<<str1<<'\t'<<str1.len()<<endl;
	str1=str1.upper_cpy();
	cout<<str1<<'\t'<<str1.len()<<endl;
}
#elif MAIN==2
int main(){
	Str str1="0126789";
	Str str2="345";
	str1.insert(3,str2);
	cout<<str1;
}
#elif MAIN==3
int main(){
	Str str1="strnumeroing numero 3numero";
	Str str2="numero";
	cout<<(str1.count(str2,2,str1.len()-1));
	//cout<<endl<<str1.len();
}
#elif MAIN==4
int main(){
	Str str1="Hola que tal, que tal estas, tal";
	Str str2="String para intercambiar ";
	str2*=2;
	str2.upper();
	//str2.lower();
	cout<<str2;
}
#elif MAIN==5
int main(){
	Str<100> str1="string Este stringstringstring es un string con muchos espaciosstring";
//	Str<10> str1="hola";
	cout<<str1.len();
	str1.replace("string","STRING GRANDE",-1);
	cout<<str1.len()<<endl;
	//str1.rplace("","_",-1);
	cout<<"count: "<<str1.count("string")<<endl;
	
	cout<<str1<<endl;

}
#elif MAIN==6
int main(){
	Str<N> str1="Esto Estoes un string";
	Str<N> str2="Estoes";

	str1.erase(str1.rfind(str2),str1.rfind(str2)+str2.len());
	str1.erase(str1.rfind("st"),str1.rfind("st")+2);
	//str1.erase(5,5+str2.len());
	//if(str1.find(str2)!=-1)
		//str1.erase(str1.rfind("st"),str1.rfind("st")+strsize("st"));
	str1+='.';
	cout<<endl<<str1;
}
#elif MAIN==7
int main(){
	Str<N> str1="Esto Estoes un string";
	Str<N> str2="Estoes ";
	str1.erase(str1.find(str2),str1.find(str2)+str2.len());
	if(str1.find("st")!=-1)
		str1.erase(str1.rfind("st"),str1.rfind("st")+strsize("st"));
	str1+='.';
	str1.insert(5,"es ");
	cout<<endl<<str1;
}
#elif MAIN==8
int main(){
	Str<N> str1="Esto Estoes un string";
	str1.replace("Estoes","de verdad que es");
	str1+=", en serio";
	cout<<endl<<str1;
}
#elif MAIN==9
#define n 6
int main(){
	//Str<n> str1="Esto       es      un               string  con muchos    espacios";
	Str<n> str1="    hola    ";
	cout<<str1.len()<<endl;
	//str1=str1.strip_cpy();
	str1.strip();
	Str<n> str2="Hola";
	cout<<(str1==str2.lower_cpy());
}
#endif