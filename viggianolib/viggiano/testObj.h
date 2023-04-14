#pragma once
#include<iostream>
#ifdef SHOWCOUNT
struct testObj{
    inline static long long objCount=0;
	int a;
	int* array;
	testObj(){
		array=new int[10];
		objCount++;
        puts("\ndefault constructor");
	}
	testObj(int a):a(a),array(new int[10]){
		for(int i=0;i<10;i++)
			array[i]=a;
		objCount++;
		puts("\nassignment constructor");
	}
	testObj(const testObj& other):a(other.a),array(new int[10]){
		for(int i=0;i<10;i++)
			array[i]=a;
		objCount++;
		puts("\ncopy constructor");
	}
	testObj(testObj&& other):a(other.a){
		this->array=other.array;
		other.array=nullptr;
		objCount++;
		puts("\nmovement constructor");
	}
	void operator=(const testObj& other){
		delete[] this->array;
		this->array=new int[10];
		for(int i=0;i<10;i++)
			this->array[i]=other.array[i];
		this->a=other.a;
		puts("\ncopy operator");
	}
	void operator=(testObj&& other){
		delete[] this->array;
		this->array=other.array;
		other.array=nullptr;
		this->a=other.a;
		puts("\nmovement operator");
	}
	~testObj(){\
		delete[] this->array;
		//if(--objCount==0)
			std::cout<<"\nOBJECT COUNTER="<<--objCount<<std::endl;
	}
	bool operator==(const testObj& other){
		return this->a==other.a;
	}
	bool operator!=(const testObj& other){
		return this->a!=other.a;
	}
	bool operator<=(const testObj& other){
		return this->a<=other.a;
	}
	bool operator>=(const testObj& other){
		return this->a>=other.a;
	}
	bool operator<(const testObj& other){
		return this->a<other.a;
	}
	bool operator>(const testObj& other){
		return this->a>other.a;
	}
};
#else
struct testObj{
    inline static long long objCount=0;
	int a;
	int* array;
	testObj(){
		array=new int[10];
	}
	testObj(int a):a(a),array(new int[10]){
		for(int i=0;i<10;i++)
			array[i]=a;
	}
	testObj(const testObj& other):a(other.a),array(new int[10]){
		for(int i=0;i<10;i++)
			array[i]=a;
		objCount++;
	}
	testObj(testObj&& other):a(other.a){
		this->array=other.array;
		other.array=nullptr;
		objCount++;
	}
	void operator=(const testObj& other){
		delete[] this->array;
		this->array=new int[10];
		for(int i=0;i<10;i++)
			this->array[i]=other.array[i];
		this->a=other.a;
	}
	void operator=(testObj&& other){
		delete[] this->array;
		this->array=other.array;
		other.array=nullptr;
		this->a=other.a;
	}
	~testObj(){\
		delete[] this->array;
	}
	bool operator==(const testObj& other){
		return this->a==other.a;
	}
	bool operator!=(const testObj& other){
		return this->a!=other.a;
	}
	bool operator<=(const testObj& other){
		return this->a<=other.a;
	}
	bool operator>=(const testObj& other){
		return this->a>=other.a;
	}
	bool operator<(const testObj& other){
		return this->a<other.a;
	}
	bool operator>(const testObj& other){
		return this->a>other.a;
	}
};
#endif
std::ostream& operator<<(std::ostream& stream,const testObj& obj){
	stream<<obj.a;
	return stream;
}