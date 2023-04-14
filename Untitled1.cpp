#include<iostream>
#include"viggianolib/viggiano.h"
using namespace mpv;
using namespace std;
int main(){
	AList<testObj> list1;
	list1.append(67);
	list1.append(65);
	list1.append(2);
	list1.append(85);
	list1.append(70);
	list1.append(67);
	list1.append(234);
	list1.append(4);
	list1.append(67);
	list1.append(9);
	list1.append(67);
	cout<<list1<<endl;
	cout<<list1.remove(67,true)<<endl;
	cout<<list1<<endl;
}