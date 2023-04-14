#include"viggiano.h"

using namespace std;


bool showRemainingObjects=true;
int remainingObjects=0;
template<typename T>
struct Object{
	template<typename D>
	struct Node{
		D data;
	};
	Node<T>* inside;
	int* refCount;
	void operator=(Object& other){
		delete this->inside;
		this->inside=other.inside;
		this->refCount=other.refCount;
		(*this->refCount)++;
	}
	Object(const Object& other){
		this->inside=other.inside;
		this->refCount=other.refCount;
		(*this->refCount)++;
		remainingObjects++;
		puts("\nobjeto creado");
	}
	Object(){
		this->inside=new Node<T>;
		this->refCount=new int;
		*this->refCount=1;
		remainingObjects++;
		puts("\nobjeto creado");
	}
	~Object(){
		remainingObjects--;		
		if(showRemainingObjects)
			printf("\nOBJET DESTRUIDO. QUEDAN %d\n",remainingObjects);
		(*this->refCount)--;
		if(*this->refCount==0){
			delete this->inside;
			delete this->refCount;
		}
		

	}
};
int main(){
/*	Object<int> obj;
	Object<int> obj2=obj;
	Object<int> obj3;*/
	Object<Object<int>> OBJ1;
	Object<Object<int>> OBJ2;
	OBJ2=OBJ1;
	OBJ1.inside->data.inside->data=1234;
	OBJ2.inside->data.inside->data=14534;
/*	obj.inside->data=234;
	cout<<obj.inside->data<<endl;*/
	
}