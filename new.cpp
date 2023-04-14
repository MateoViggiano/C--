#include"viggianolib/viggiano.h"
using namespace std;
using namespace mpv;
int main(){
	int* p=new int(32);
	Str<>* p2=(Str<>*)::operator new(sizeof(Str<>));
	new(p2) Str<>("String");
	delete p;
	//delete p2;
	cout<<*p2;
	p2->~Str<>();
	
	::operator delete(p2,sizeof(Str<>));
}