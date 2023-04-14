#include"viggianolib/viggiano.h"
#include"windows.h"
#include<fstream>
#include<iomanip>
using namespace std;
using namespace mpv;
struct Simbolo{
	char simbolo;
	float probabilidad;
	Str<> binario;
	int apariciones;
	Simbolo(char simbolo,int apariciones):simbolo(simbolo),apariciones(apariciones){}
	Simbolo(char simbolo,Str<> bin):simbolo(simbolo),binario(bin){}
	void calcular_prababilidad(int cantidad_simbolos){
		this->probabilidad=(float)(this->apariciones*100)/(float)cantidad_simbolos;
	}
	bool operator==(const Simbolo& other){
		if(this->simbolo==other.simbolo)
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

std::istream& operator>>(std::istream& stream,List<Simbolo>& list){
	char c=0;
	int n;
	do{
		stream.get(c);
		if(c!='\n'){
			stream>>n;stream.get();
			list.append(Simbolo(c,n));
		}
		else break;
	}while(c!='\n');
	return stream;
}
Pair<int,int> menores_posiciones(List<sPtr<Nodo>> lista){
	int sz=lista.len(),i;
	Pair<int,int> posiciones(sz-1,sz-1);
	for(i=sz-1;i>=0;i--){
		if(lista[i]->apariciones<lista[posiciones.d1]->apariciones)
			posiciones.d1=i;
	}
	if(posiciones.d1==sz-1)
		posiciones.d2=sz-2;
	for(i=sz-1;i>=0;i--){
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

int main(){
	List<Simbolo> simbolos;
	Str<> mensaje_codificado;
	int leer_archivo;
	
	cout<<"0 -> Ingresar datos de forma manual\n"
		<<"1 -> Leer datos de \"ocurrencias.txt\"\n";
	cin>>leer_archivo;fflush(stdin);
	if(leer_archivo==0){
		cout<<"Ingrese los simbolos y sus ocurrencias:\n";
		cin>>simbolos;
		cout<<"Ingrese el mensaje codificado:\n";
		cin>>mensaje_codificado;			
	}
	else{
		ifstream archivo;
		archivo.open("ocurrencias.txt",ios::in);
		if(archivo.fail()){
			cout<<"No se pudo abrir el archivo\n";
			system("pause");
			return 0;
		}
		archivo>>simbolos;
		archivo>>mensaje_codificado;
		archivo.close();
	}
	cout<<endl<<simbolos<<endl;
	List<sPtr<Nodo>> nodos_por_enlazar;
	int sz=simbolos.len();
	int longitud=0;float total=0;
	for(int i=0;i<sz;i++){
		longitud+=simbolos[i].apariciones;
	}
	for(int i=0;i<sz;i++){
		nodos_por_enlazar.append(new Nodo(simbolos[i]));
		simbolos[i].calcular_prababilidad(longitud);total+=simbolos[i].probabilidad;
	}
	sPtr<Nodo> raiz=crear_arbol(nodos_por_enlazar);
	asignar_valores_binarios(raiz,simbolos);
	ofstream file2;
	file2.open("valores.txt",ios::out);
	ofstream file;
	file.open("output.txt",ios::out);
	for(int i=0;i<sz;i++){
		file<<simbolos[i].simbolo<<simbolos[i].binario<<endl;
		cout<<simbolos[i]<<endl;
		file2<<setprecision(3)<<simbolos[i].simbolo<<'='<<simbolos[i].probabilidad<<'%'<<endl;
	}
	file<<endl<<mensaje_codificado<<endl;
	file.close();
	file2.close();
	cout<<total<<endl;
	system("pause");	
}
