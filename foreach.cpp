#include"viggianolib/viggiano.h"
//using namespace mpv;
using namespace std;
int main(){
	mpv::AList<int> list;
	for(int i=0;i<15;i++)
		list.append(i);
/*	for(auto i:list)
		cout<<i<<", ";*/
	for(mpv::AList<int>::iterator i=list.rbegin();i!=list.rend();i--)
		cout<<*i<<", ";
}