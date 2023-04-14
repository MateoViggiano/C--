#include"viggianolib/viggiano.h"
long long objCount=0;
struct testObj{
	int a;
	testObj(){
		objCount++;
	}
	testObj(int a):a(a){
		objCount++;
	}
	testObj(const testObj& other):a(other.a){
		objCount++;
	}
	testObj(testObj&& other):a(other.a){
		objCount++;
	}
	void operator=(const testObj& other){
		this->a=other.a;
	}
	~testObj(){
		std::cout<<"\nOBJECT COUNTER="<<--objCount<<std::endl;
	}
};
std::ostream& operator<<(std::ostream& stream,testObj obj){
	stream<<obj.a;
	return stream;
}
using namespace std;
using namespace mpv;
int main(){
    List<testObj> lista;    
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
	//lista.del(lista.len());
	//lista.del((lista.len()-1));
    //lista.del(-8);
    List<testObj> lista2;
    lista+=lista;
    cout<<"\nEMPIEZA A BORRAR\n";
	cout<<lista<<endl;
   	while(lista.len()){
    	lista.del(-1);
    	cout<<lista<<endl;
	}
	//cout<<lista;
    return 0;
}