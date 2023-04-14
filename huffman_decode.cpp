#include"viggianolib/viggiano.h"
#include<windows.h>
#include<fstream>
using namespace std;
using namespace mpv;
struct Symbol{
	char symbol;
	Str<> bin;
};
istream& operator>>(istream& stream, Symbol& symb){
	Str<> input;
	stream>>input;
	if(input==""){
		symb.symbol='\0';
		return stream;
	}
	symb.symbol=input[0];
	symb.bin=input.substr(1);
	return stream;
	
}
istream& operator>>(istream& stream, List<Symbol>& lista){
	Symbol s;
	while(true){
		stream>>s;
		if(s.symbol=='\0')
			return stream;
		else{
			lista.append(s);
		}
	}
}
bool getsymbol(Symbol& symbol){
	Str<> input;
	cin>>input;
	if(input==""){
		return 1;
	}
	symbol.symbol=input[0];
	symbol.bin=input.substr(1);
	return 0;
}

void getlist(List<Symbol>& list){
	Symbol s;
	while(getsymbol(s)==0){
		list.append(s);
	}
}
int main(){
	short opcion=1;

	while(opcion!=2){
		cout<<"0 -> Ingresar datos de forma manual\n"
			<<"1 -> Leer datos de un archivo\n"
			<<"2 -> Salir\n";
		
		Str<> bin,msj;
		cin>>opcion;
		system("cls");
		fflush(stdin);
		switch(opcion){
			case 0:{
				List<Symbol> list;
				cin>>list;
				int sz=list.len();
				cout<<"Ingrese el mensaje para decodificar: ";
				cin>>bin;
				while(bin.len()>0){
					for(int i=0;i<sz;i++){
						if(bin.find(list[i].bin)==0){
							msj+=list[i].symbol;
							bin.remove(list[i].bin);
						}
					}
				}
			}break;
			case 1:{
				Str<> nombre;
				ifstream file;
				cout<<"Ingrese el nombre del archivo: ";
				cin>>nombre;
				file.open(nombre.get_text(),ios::in);
				if(file.fail()){
					cout<<"No se pudo abrir el archivo\n";
					system("pause");
					return 0;
				}
				List<Symbol> list;
				file>>list;
				int sz=list.len();
				file>>bin;
				cout<<"\nMensaje decodificado:\n";
				while(bin.len()>0){
					bool error=true;
					for(int i=0;i<sz;i++){
						if(bin.find(list[i].bin)==0){
							msj+=list[i].symbol;
							bin.remove(list[i].bin);
							error=false;
						}
					}
					if(error){
						cout<<"\nERROR\n";
						file.close();
						break;
					}
				}
				file.close();
			}break;
			case 2: 
				return 0;
				break;
			default:
				cout<<"No se ingreso una opcion valida.\n";
		}
		cout<<msj<<"\n\n";
		system("pause");
		system("cls");
	}
}