#include"viggianolib/viggiano.h"
using namespace std;
using namespace mpv;
template<typename T>
void sz(const List<T>& lista){
	cout<<"\nsize: "<<lista.size()<<endl;
	cout<<"len: "<<lista.len()<<endl;
}
int main(){
	List<int> lista(625,-3,7,2,56,5427,-452,5,2,54,62,9);
	List<int> lista2=lista.sublist(0,-1);
	List<int> lista3=lista2.sublist(0,-1);
	for(int i=-13;i<=12;i++){
		for(int j=-13;j<=12;j++){
			if(i<0 and j>=0 and i+13>j or i<0 and j<0 and i+13>j+13 or j>=0 and j>=0 and i>j or i>=0 and j<0 and i>j+13)
				continue;
			cout<<i<<' '<<j<<endl;
			lista2=lista;
			lista3=lista2.cut(i,j);
			cout<<lista2<<lista3<<endl;
			sz(lista2);sz(lista3);
		}
	}
	//sz(lista2);
	//cout<<lista.cut(-13, -12)<<endl;
	lista.wipe(3,-6);
	lista.println();
	while(lista.size()>=1){
		lista.wipe(0,1);
		lista.println();
		sz(lista);
	}
	return 0;
}
