#include"viggiano.h"
using namespace vgg;
using namespace std;
int main(){
	//List<sPtr<int>> lista1={new int(4),new int(67),new int(1),new int(-8),new int(13)};
	//lista1[lista1.index(13,0,lista1.len()-1)]=62;
	//lista1.setSize_full(100,new int(32));
	//lista1.clear();
	List<sPtr<int>> lista1;
	lista1.setSize(100);
	lista1[-1]=new int(-999);
	cout<<*lista1[-1];
	lista1[4]=new int;
	
}