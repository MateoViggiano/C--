#define SHOWREMAININGOBJECTS
#include"smart_pointer_List_implementation.h"
using namespace std;
//using namespace vgg;
#define n 2
List<List<List<int>>> func2(){
	int counter=0;
	List<List<List<int>>> list;
	list.setSize(n);
	for range(I,n){
		list[I].setSize(n);
		for range(J,n){
			list[I][J].setSize(n);
			for range(K,n){
				list[I][J][K]=counter++;
			}
		}
	}
	return list;
}
List<List<List<List<int>>>> func(){
	int counter=0;
	List<List<List<List<int>>>> list;
	List<List<List<List<int>>>> list2;
	list.setSize(n);
	for range(I,n){
		list[I].setSize(n);
		for range(J,n){
			list[I][J].setSize(n);
			for range(K,n){
				list[I][J][K].setSize(n);
				for range(L,n){
					list[I][J][K][L]=counter++;
				}
			}
		}
	}
	list2=list;
	cout<<"[";
	for range(I,n){
		cout<<"[";
		for range(J,n){
			cout<<"[";
			for range(K,n){
				list[I][J][K].println();
			}
			cout<<"]\n";
		}
		cout<<"]\n";
	}
	cout<<"]\n";
	list=list2;
	list2=list2;

	return list2;
}
int main(){
	List<List<List<List<int>>>> list;
	list=func();
	List<List<List<int>>> sublist;
	sublist=func2();
	list.append(sublist);
	sublist=func2();
	cout<<"[";
	for range(I,n+1){
		cout<<"[";
		for range(J,n){
			cout<<"[";
			for range(K,n){
				list[I][J][K].println();
			}
			cout<<"]\n";
		}
		cout<<"]\n";
	}
	cout<<"]\n";

	list=list;
	list=list*3;
	list*=4;
	list.pop(1);
	list=list+list*4;
	
	List<sPtr<List<int>>> lista2;
	lista2=lista2;
	lista2=lista2*3;
	lista2*=4;
	lista2=lista2+lista2*4;
	List<int> lista3{54,6,25,7,2,5};
	lista3.setSize_full(5,52);
	lista3.pop();
	lista3.append(43);
	lista3.insert(324,4);
	lista3.append(-542);
	List<int> lista4=lista3.copy();
	return 0;
}