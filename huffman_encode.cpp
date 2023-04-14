#include"viggianolib/viggiano.h"
#include<windows.h>
#include<fstream>
using namespace std;
using namespace mpv;
struct Simbolo{
	char simbolo;
	float probabilidad;
	Str<100> binario;
	int apariciones;
	Simbolo(char simbolo):simbolo(simbolo),apariciones(1){}
	void calcular_prababilidad(int cantidad_simbolos){
		this->probabilidad=(float)(this->apariciones*100)/(float)cantidad_simbolos;
	}
	bool operator==(char simbol){
		if(this->simbolo==simbol)
			return 1;
		else 
			return 0;	
	}
};
std::ostream& operator<<(std::ostream& stream,const Simbolo simb){
	stream<<simb.simbolo<<'<'<<simb.apariciones<<'>'<<simb.probabilidad<<'%'<<'='<<simb.binario;
	return stream;
}
struct Nodo{
	List<char> simbolos;
	int apariciones=1;
	sPtr<Nodo> izquierda;
	sPtr<Nodo> derecha;
	Nodo():izquierda(nullptr),derecha(nullptr){}
	Nodo(Simbolo other):apariciones(other.apariciones),izquierda(nullptr),derecha(nullptr){
		this->simbolos.append(other.simbolo);
	}
};
std::ostream& operator<<(std::ostream& stream,const Nodo simb){
	for(int i=0;i<simb.simbolos.len();i++){
		stream<<simb.simbolos[i]<<' ';
	}
	stream<<'<'<<simb.apariciones<<">\n";
	return stream;
}
List<Simbolo> contar_simbolos(Str<100> mensaje){
	List<Simbolo> lista;
	int msg_sz=mensaje.len();
	for(int i=0,posicion;i<msg_sz;i++){
		posicion=lista.index(mensaje[i]);	//busco el indice del simbolo actual en la lista, si no esta devuelve un -1
		if(posicion==-1)
			lista.append(mensaje[i]);
		else
			lista[posicion].apariciones++;
	}
	return lista;
}
Pair<int,int> menores_posiciones(List<sPtr<Nodo>> lista){
	Pair<int,int> posiciones(0,0);
	int sz=lista.len(),i;
	for(i=0;i<sz;i++){
		if(lista[i]->apariciones<lista[posiciones.d1]->apariciones)
			posiciones.d1=i;
	}
	if(posiciones.d1==0)
		posiciones.d2=1;
	for(i=0;i<sz;i++){
		if(i!=posiciones.d1 and lista[i]->apariciones<lista[posiciones.d2]->apariciones)
			posiciones.d2=i;
	}
	return posiciones;
}
sPtr<Nodo> crear_arbol(List<sPtr<Nodo>> lista){
	while(lista.len()>1){
		for(int i=0;i<lista.len();i++)
			cout<<*(lista[i]);
		Pair<int,int> menores=menores_posiciones(lista);
		cout<<endl<<menores.d1<<"  "<<menores.d2<<"\n\n";
		sPtr<Nodo> nuevo(new Nodo);
		nuevo->apariciones=lista[menores.d1]->apariciones+lista[menores.d2]->apariciones;
		nuevo->simbolos=lista[menores.d1]->simbolos+lista[menores.d2]->simbolos;
		nuevo->derecha=lista[menores.d1];
		nuevo->izquierda=lista[menores.d2];
		if(menores.d1<menores.d2){
			lista.del(menores.d2);
			lista.del(menores.d1);
		}
		else{
			lista.del(menores.d1);
			lista.del(menores.d2);			
		}

		lista.insert(0,nuevo);
	}
	return lista[0];
}
void asignar_valores_binarios(sPtr<Nodo> raiz,List<Simbolo>& caracteres){
	int sz=caracteres.len();
	for(int i=0;i<sz;i++){
		sPtr<Nodo> puntero(raiz);
		while(puntero->simbolos.len()>1){
			if(puntero->izquierda->simbolos.has(caracteres[i].simbolo)){
				if(puntero->izquierda->apariciones>=puntero->derecha->apariciones)
					caracteres[i].binario+="0";
				else
					caracteres[i].binario+="1";
				puntero=puntero->izquierda;
			}
			else{
				if(puntero->derecha->apariciones>puntero->izquierda->apariciones)
					caracteres[i].binario+="0";
				else
					caracteres[i].binario+="1";
				puntero=puntero->derecha;
			}
		}
	}
}
Str<100> codificar(Str<100> mensaje,List<Simbolo> simbolos){
	Str<100> mensaje_codificado;
	for(int i=0;i<mensaje.len();i++){
		mensaje_codificado+=((simbolos[simbolos.index(mensaje[i])]).binario);
	}
	return mensaje_codificado;
}
int main(){
	while(true){
		system("cls");
		Str<100> mensaje;
		cin>>mensaje;
		if(mensaje==""){
			cout<<"No se ingreso un mensaje"<<endl;
			return 0;
		}
		
		List<Simbolo> simbolos=contar_simbolos(mensaje);
		List<sPtr<Nodo>> nodos_por_enlazar;
		int sz=simbolos.len();
		for(int i=0;i<sz;i++){
			nodos_por_enlazar.append(new Nodo(simbolos[i]));
			simbolos[i].calcular_prababilidad(mensaje.len());
		}
		sPtr<Nodo> raiz=crear_arbol(nodos_por_enlazar);
		asignar_valores_binarios(raiz,simbolos);
		for(int i=0;i<sz;i++){
			cout<<simbolos[i]<<endl;
		}
		Str<100> mensaje_codificado=codificar(mensaje,simbolos);
		cout<<"Longitud del mensaje: "<<mensaje.len()<<endl
			<<"Cantidad de sombolos: "<<sz<<endl
			<<"Mensaje codificado:\n"<<mensaje_codificado<<"\n\n\n";
		ofstream file;
		file.open("encode.txt",ios::out);
		for(int i=0;i<sz;i++)
			file<<simbolos[i].simbolo<<simbolos[i].binario<<endl;
		file<<endl<<mensaje_codificado;
		file.close();
		system("pause");
	}	
}