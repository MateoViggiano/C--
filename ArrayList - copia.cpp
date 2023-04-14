#include<iostream>
#include"viggianolib/viggiano.h"
struct reserve{
    unsigned long long size;
	explicit reserve(long long size):size(size){}
};
template<typename T,long long min_maxSize=16>
class AList{
    private:
        T* array;
        long long maxSize;
        long long size;
    public:
    	AList():array(nullptr),maxSize(0),size(0){}
        AList(reserve reserved):array(new T[reserved.size]),maxSize(reserved.size),size(0){}
        AList(const AList& other):array(new T[other.maxSize]),maxSize(other.maxSize),size(other.size){
			mpv::memcopy(this->array,other.array,other.size);
        }
        AList(AList&& other):array(other.array),maxSize(other.maxSize),size(other.size){
        	other.size=0;
        	other.maxSize=0;
        	other.array=nullptr;
		}
		void operator=(const AList& other){
			if(this->maxSize<other.size){
				delete this->array;
				this->array=new T[other.maxSize];
				this->maxSize=other.maxSize;
			}
			this->size=other.size;
			mpv::memcopy(this->array,other.array,other.size);
		}
		void operator=(AList&& other){
			if(this==&other)
				return;
			delete[] this->array;
			this->size=other.size;
			this->maxSize=other.maxSize;
			this->array=other.array;
			other.size=0;
			other.maxSize=0;
			other.array=nullptr;
		}
		AList operator+(const AList& other)const{
			AList new_list;
			new_list.size=this->size+other.size;
			new_list.maxSize=new_list.size*2;
			new_list.array=new T[new_list.maxSize];
			mpv::memcopy(new_list.array,this->array,this->size);
			mpv::memcopy(new_list.array+this->size,other.array,other.size);
			return new_list;
		}
		// void operator+=(const AList& other){
		// std::cout<<"\n***********************************OPERADOR+= ts"<<this->size<<" tms"<<this->maxSize;
		// std::cout<<"\n***********************************OPERADOR+= os"<<other.size<<" oms"<<other.maxSize<<std::endl;
		// 	if(this->maxSize<this->size+other.size){puts("----------------------------ENTRA EN EL IF------------------------------");
		// 		T* aux=this->array;
		// 		this->maxSize=(this->size+other.size)*2;
		// 		this->array=new T[this->maxSize];
		// 		mpv::memcopy(this->array,aux,this->size); 
		// 		delete[] aux;
		// std::cout<<"\n***********************************OPERADOR+= ts"<<this->size<<" tms"<<this->maxSize;
		// std::cout<<"\n***********************************OPERADOR+= os"<<other.size<<" oms"<<other.maxSize<<std::endl;
		// 	}
		// 	mpv::memcopy(this->array+this->size,other.array,other.size);
		// 	this->size+=other.size;
		// }
		void operator+=(const AList& other){
			if(this->maxSize<this->size+other.size){
				T* aux=this->array;
				this->maxSize=(this->size+other.size)*2;
				this->array=new T[this->maxSize];
				if(aux==other.array)
					mpv::memcopy(this->array,aux,this->size);
				else
					mpv::memmove(this->array,aux,this->size);
				mpv::memcopy(this->array+this->size,other.array,other.size);
				delete[] aux;
			}
			else
				mpv::memcopy(this->array+this->size,other.array,other.size);
			this->size+=other.size;
		}
		AList operator*(unsigned int num)const{
			AList new_list;
			if(num==0)
				return new_list;
			new_list.maxSize=this->size*num*2;
			new_list.array=new T[new_list.maxSize];
			for(unsigned int i=0;i<num;i++){
				mpv::memcopy(new_list.array+new_list.size,this->array,this->size);
				new_list.size+=this->size;
			}
			return new_list;
		}
		void operator*=(const unsigned int num){
			if(num==0){
				size=0;
				maxSize=0;
				delete[] array;
				array=nullptr;
			}
			else{
				if(maxSize<size*num){
					T* aux=array;
					maxSize=size*num*2;
					array=new T[maxSize];
					mpv::memmove(array,aux,size);
					delete[] aux;
				}
				for(long long i=1,prevSize=size;i<num;i++,size+=prevSize)
					mpv::memcopy(array+size,array,prevSize);
			}
		}
		T& operator[](long long index)const{
			if(index>=0)
				return array[index];
			else
				return array[index+size];
		}
		void append(const T& data){
			if(size==maxSize){//no pongo >= porque size nunca deberia ser mayor a maxSize
				if(maxSize==0)
					maxSize=min_maxSize;
				else
					maxSize*=2;
				T* aux=array;
				array=new T[maxSize];
				mpv::memmove(array,aux,size);
				delete[] aux;
			}
			array[size++]=data;
		}
		void insert(long long index,T data){
			if(index<0)
				index+=size+1;
			if(size==maxSize){
				if(maxSize==0)
					maxSize=min_maxSize;
				else
					maxSize*=2;
				T* aux=array;
				array=new T[maxSize];
				mpv::memmove(array,aux,index);
				mpv::memmove(array+index+1,aux+index,(size++)-index);
				array[index]=data;
				delete[] aux;
			}
			else{
				mpv::memmove(array+index+1,array+index,(size++)-index);
				array[index]=data;
			}
		}
		void del(long long index=-1){
			if(index<0)
				index+=size;
			mpv::memmove(array+index,array+index+1,(--size)-index);
		}
		T pop(long long index=-1){
			if(index<0)
				index+=size;
			T aux=(T&&)(array[index]);
			mpv::memmove(array+index,array+index+1,(--size)-index);
			return aux;
		}
		AList sublist(long long start,long long end=-1)const{
			AList new_list;
			if(start<0)
				start+=size+1;
			if(end<0)
				end+=size+1;
			new_list.size=end-start;
			if(new_list.size==0){
				new_list.maxSize=0;
			}
			else{
				new_list.maxSize=new_list.size*2;
				new_list.array=new T[maxSize];
				mpv::memcopy(new_list.array,this->array+start,this->size);
			}
			return new_list;
		}
		AList cut(long long start,long long end=-1){
			AList new_list;
			if(start<0)
				start+=size+1;
			if(end<0)
				end+=size+1;
			new_list.size=end-start;
			if(new_list.size==0){
				new_list.maxSize=0;
			}
			else{
				new_list.maxSize=new_list.size*2;
				new_list.array=new T[maxSize];
				mpv::memmove(new_list.array,this->array+start,this->size);
				mpv::memmove(this->array+start,this->array+end,this->size-end);
				this->size-=new_list.size;
			}
			return new_list;
		}
		void wipe(long long start,long long end=-1){
			if(start<0)
				start+=size+1;
			if(end<0)
				end+=size+1;
			long long deletedSize=end-start;
			mpv::memmove(this->array+start,this->array+end,this->size-end);
			this->size-=deletedSize;	
		}

		void setSize_full(long long size,const T& data){
			this->size=size;
			if(maxSize<size){
				maxSize=size*2;
				delete[] array;
				array=new T[maxSize];
			}
			for(long long i=0;i<size;i++)
				array[i]=data;
		}
		void setSize(long long size){
			this->size=size;
			if(maxSize<size){
				maxSize=size*2;
				delete[] array;
				array=new T[maxSize];
			}
		}
		int index(T data,int start=0,int end=-1)const{	//retorna -1 si no se encontro el elemento
			if(start<0)
				start+=this->sz+1;
			if(end<0)
				end+=this->sz+1;
			for(int i=start;i<end;i++){
				if(array[i]==data)
					return i;
			}
			return -1;
		}
		long long len()const{
			return size;
		}
		int count(T data)const{
			int counter=0;
			for(int i=0;i<size;i++)
				if(array[i]==data)
					counter++;
			return counter;
		}
		~AList(){
			delete[] this->array;
		}

};
template<typename T, long long mms>
std::ostream& operator<<(std::ostream& stream,const AList<T,mms>& list){
	stream<<'[';
	for(int i=0,size=list.len();i<size;i++){
		stream<<list[i];
		if(i<size-1)
			std::cout<<", ";		
	}
	stream<<']';
	return stream;
}

using namespace std;
int main(){
    AList<testObj> lista;    
	lista.append(54);cout<<lista<<endl;
    lista.append(43);cout<<lista<<endl;
    lista.append(11);cout<<lista<<endl;
    lista.append(31);cout<<lista<<endl;
    lista.append(43);cout<<lista<<endl;
    lista.append(-5);cout<<lista<<endl;
    lista.append(75);cout<<lista<<endl;
    lista.append(54);cout<<lista<<endl;
    lista.insert(0,432);cout<<lista<<lista.len()<<endl;
    lista.insert(5,976);cout<<lista<<endl;
    lista.insert(-6,652);cout<<lista<<endl;
    lista.insert(5,433);cout<<lista<<endl;
    lista.insert(-1,111);cout<<lista<<endl;
    lista.insert(-9,900);cout<<lista<<endl;
    lista.insert(-1,900);cout<<lista<<lista.len()<<endl;
//	lista.del((lista.len()-1));
//    lista.del(-8);
    AList<testObj> lista2;
    lista.wipe(4,4);
    cout<<lista<<endl<<lista2<<"\n\n\n";

   	while(lista.len()){
    	lista.del(-1);
    	cout<<lista<<endl;
	}
	//cout<<lista;
    return 0;
}
