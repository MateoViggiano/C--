#define SHOWREMAININGOBJECTS
#include"viggiano.h"
using namespace vgg;
using namespace std;
struct retCycle{
	wPtr<retCycle> next;
};
int main(){
	List<int> lista;
	lista.append_none();
	cout<<lista.len()<<endl;
	cout<<lista[-1]<<endl;
	lista[-1]=32;
	cout<<lista[0]<<endl;
	lista.print();
}