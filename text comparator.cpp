#include"viggianolib/viggiano.h"
#include<iomanip>
#include<windows.h>
using namespace mpv;
using namespace std;
struct Simbolo{
	char simbolo;
	float probabilidad;
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
	stream<<simb.simbolo<<'<'<<simb.apariciones<<'>'<<simb.probabilidad<<'%';
	return stream;
}
List<Simbolo> contar_simbolos(Str<500> mensaje){
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
int main(){
    while(true){
    	system("cls");
        short opcion;
        cout<<"1-->Analizar un texto\n"
            <<"2-->Comparar dos textos\n";
        cin>>opcion;
        cin.get();
        if(opcion==1){
            Str<500> texto;
            cout<<"Ingrese el texto:\n";
            cin>>texto;
            List<Simbolo> simbolos=contar_simbolos(texto);
            cout<<"Cantidad de caracteres: "<<texto.len()<<endl;
            for(auto i:simbolos){
                i.calcular_prababilidad(texto.len());
                cout<<setprecision(3)<<i<<endl;
            }
        }
        else{
        	Str<500> texto1,texto2;
        	cout<<"Ingrese el primer texto:\n";
        	cin>>texto1;
        	cout<<"Ingrese el segundo texto:\n";
        	cin>>texto2;
            List<Simbolo> simbolos1=contar_simbolos(texto1), simbolos2=contar_simbolos(texto2);
        	cout<<"\n************Texto 1*****************************:\n";
        	cout<<"Cantidad de caracteres: "<<texto1.len()<<endl;
            for(auto i:simbolos1){
                i.calcular_prababilidad(texto1.len());
                cout<<setprecision(3)<<i<<endl;
            }
            cout<<"\nTexto 2:\n";
        	cout<<"\n************Texto 2*****************************:\n";
            cout<<"Cantidad de caracteres: "<<texto2.len()<<endl;
            for(auto i:simbolos2){
                i.calcular_prababilidad(texto2.len());
                cout<<setprecision(3)<<i<<endl;
            }
            if(texto1==texto2)
                cout<<"\n\nLos dos textos son iguales\n";
            else
                cout<<"\n\nLos textos son distintos\n";
		}
        cout<<endl;
        system("pause");
    }
}