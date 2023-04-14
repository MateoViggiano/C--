#include"viggiano.h"
using namespace vgg;
using namespace std;
int main(){
	List<Str<>> lista2;
	lista2.append("hola");
	lista2.append("que tal");
	lista2.insert(-2,"__");
	lista2[0]="HOLA";
	for(int i=0;i<lista2.len();i++){
		cout<<(lista2[i])<<endl;
	}

	
}