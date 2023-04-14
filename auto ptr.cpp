#include"viggianolib2/viggianolib/viggiano.h"

using namespace vgg;
using namespace std;
#define n 3
/*
template<typename T>
class Ptr{
	private:
		int* refCount;
	public:
		T* data;
	Ptr():refCount(new int),data(new T){
		*this->refCount=1;
		INCPOINTERS
	}
	explicit Ptr(T dat):refCount(new int),data(new T){
		*this->refCount=1;
		*this->data=dat;
		INCPOINTERS
	}
	Ptr(Ptr& other):refCount(other.refCount),data(other.data){
		(*this->refCount)++;
		INCPOINTERS
	}
	void operator=(const Ptr& other){
		(*this->refCount)--;
		if(*this->refCount==0){
			delete refCount;
			delete data;
		}
		this->refCount=other.refCount;
		this->data=other.data;
		(*this->refCount)++;
	}
	T& operator*(){
		return *data;
	}
	T* operator->(){
		return data;
	}
	~Ptr(){
		(*this->refCount)--;
		if((*this->refCount)==0){
			delete this->data;
			delete this->refCount;
		}
		DECPOINTERS
		REMAININGPOINTERS
	}
};*/

/*Ptr<List<int>> func(){
	Ptr<List<int>> p(List<int>(8,6,27,2,45));
	return p;
}
int main(){
	Ptr<List<int>> p;
	p=func();
	(*p).append(43);
	(*p).println();
	p->println();
	p.data->println();
}*/
template<typename T>
Ptr<Ptr<T>*> func(int fil,int col){
	int i,j;
	Ptr<T> array[10];
	Ptr<Ptr<T>> p(array);
	return array;
}
int main(){
	//Ptr<Ptr<int>> p=func<int>(10,10);
	Ptr<Ptr<int>*> array();
	Ptr<int> sub[10];
	*array=sub;
	cout<<array[4];
}
