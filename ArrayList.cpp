#include"viggianolib/viggiano.h"
using namespace mpv;
using namespace std;
/*int main(){
    AList<testObj> lista;    
	lista.append(54);cout<<lista<<endl;
    lista.append(43);cout<<lista<<endl;
    lista.append(11);cout<<lista<<endl;
    lista.append(31);cout<<lista<<endl;
    lista.append(43);cout<<lista<<endl;
    lista.append(-5);cout<<lista<<endl;
    lista.append(75);cout<<lista<<endl;
    lista.append(54);cout<<lista<<endl;
    lista.insert(0,432);cout<<lista<<lista.len()<<endl;
    lista.insert(5,976);cout<<lista<<endl;
    lista.insert(-6,652);cout<<lista<<endl;
    lista.insert(5,433);cout<<lista<<endl;
    lista.insert(-1,111);cout<<lista<<endl;
    lista.insert(-9,900);cout<<lista<<endl;
    lista.insert(-1,900);cout<<lista<<lista.len()<<endl;
//	lista.del((lista.len()-1));
//    lista.del(-8);
    AList<testObj> lista2=lista;
    lista2+=lista;
    lista+=lista+lista2;
    lista.wipe(4,4);
    cout<<lista<<endl<<lista2<<"\n\n\n";
	
   	while(lista.len()){
    	lista.del(-1);
    	cout<<lista<<endl;
	}
	lista.insert(0,342);
	
	cout<<lista.len();
    return 0;
}*/
int main(){
    AList<sPtr<int>> lista;    
	lista.append(new int(34));
    lista.append(new int(43));
    lista.append(new int(11));
    lista.append(new int(31));
    lista.append(new int(43));
    lista.append(new int(-5));
    lista.append(new int(75));
    lista.append(new int(54));
    lista.insert(0,new int(432));
    lista.insert(5,new int(976));
    lista.insert(-6,new int(652));
    lista.insert(5,new int(433));
    lista.insert(-1,new int(111));
    lista.insert(-9,new int(900));
    lista.insert(-1,new int(900));
//	lista.del((lista.len()-1));
    //lista.del(-8);
    AList<sPtr<int>> lista2=lista;
    lista2+=lista;
    lista+=lista+lista2;
    lista.wipe(4,4);
    //cout<<lista<<endl<<lista2<<"\n\n\n";
	
   	while(lista.len()){
    	lista.del(-1);
    	//cout<<lista<<endl;
	}
	lista.insert(0,new int(342));
	sPtr<int> p=lista[0];
	cout<<lista.len();

    return 0;
}