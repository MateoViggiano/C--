#include<iostream>
#include"viggianolib/viggiano.h"
using namespace mpv;
using namespace std;
int sz=15;
int main(){
	
	

	testObj* ptr=(testObj*)::operator new(sz*sizeof(testObj));
	new(ptr) testObj[5];
		new(ptr+1) testObj[0];
	new(ptr+2) testObj[0];
	new(ptr+2) testObj[0];
	new(ptr+2) testObj[0];
	new(ptr+2) testObj[0];
	new(ptr+7) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+11) testObj[0];
	new(ptr+11) testObj[0];
	new(ptr+11) testObj[0];
	new(ptr+11) testObj[0];
	new(ptr+11) testObj[0];
	new(ptr+13) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+5) testObj[sz-5];
	new(ptr+1) testObj[0];
	new(ptr+2) testObj[0];
	new(ptr+2) testObj[0];
	new(ptr+2) testObj[0];
	new(ptr+2) testObj[0];
	new(ptr+7) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+5) testObj[0];
	new(ptr+11) testObj[0];
	new(ptr+11) testObj[0];
	new(ptr+11) testObj[0];
	new(ptr+11) testObj[0];
	new(ptr+11) testObj[0];
	new(ptr+13) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	new(ptr+15) testObj[0];
	memdestructor(ptr,sz);
	::operator delete(ptr,sz*sizeof(testObj));
	//::operator delete(ptr,sz*sizeof(testObj));
}

/*int main(){
	Str<43>* ptr=(Str<43>*)::operator new(sz*sizeof(Str<43>));
	Str<43> str="a";
	for(int i=0;i<sz;i++,str+='a'){
		new(ptr+i) Str<43>(str);
	}
	//new(ptr) Str<43>[sz];
	Str<>* ptr2=new Str<>[30];
	delete[] ptr2;
	cout<<endl<<ptr[0]<<endl<<ptr[sz-1]<<endl;
	memdestructor(ptr,sz);
	::operator delete(ptr,sz*sizeof(Str<43>));
	int* intptr=(int*)::operator new(sz*sizeof(int));
	new(intptr) int[sz];
	memdestructor(intptr,sz);
}*/