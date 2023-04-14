#include"viggiano.h"
using namespace std;
using namespace vgg;
template<typename T>
void func(Queue<T>& cola){
	while(cola.empty()==false){
		cout<<cola.pop()<<endl;
	}
}
int main(){
	Queue<int> cola1;
	cola1.push(5);
	cola1.push(15);
	cola1.push(62);	
	cola1.push(-42);
	while(cola1.empty()==false){
		cout<<cola1.pop()<<endl;
	}
	func(cola1);
	cout<<endl<<"FIN DEL PROGRAMA";
	return 0;
}
