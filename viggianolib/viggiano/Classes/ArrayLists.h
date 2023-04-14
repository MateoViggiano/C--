#pragma once
#include<iostream>
#include"../arrays.h"
namespace mpv{
    struct reserve{
        unsigned long long size;
        explicit reserve(long long size):size(size){}
    };
    template<typename T>
    void memrealloc(T*& mem,long long new_size,long long prev_size){
        T* aux=mem;
        mem=(T*)::operator new(new_size*sizeof(T));
        
    }
    template<typename T,long long min_maxSize=64>
    class AList{
        private:
            T* array;
            long long maxSize;
            long long size;
            void realloc(long long new_size){
                if(new_size>maxSize){
                    T* aux=this->array;
                    array=(T*)::operator new(new_size*sizeof(T));
                    new(array) T[new_size];
                    memmove(array,aux,size);
                    memdestructor(aux,size);
                    ::operator delete(aux,maxSize*sizeof(T));
                    maxSize=new_size*2;
                }
                else{
                    new(array+size) T[new_size-size];
                }
            }
        public:
            AList():array(nullptr),maxSize(0),size(0){}
            AList(reserve reserved):array((T*)::operator new(reserved.size*sizeof(T))),maxSize(reserved.size),size(0){}
            AList(const AList& other):array((T*)::operator new(other.maxSize*sizeof(T))),maxSize(other.maxSize),size(other.size){
                new(this->array) T[other.size];
                mpv::memcopy(this->array,other.array,other.size);
            }
            AList(AList&& other):array(other.array),maxSize(other.maxSize),size(other.size){
                other.size=0;
                other.maxSize=0;
                other.array=nullptr;
            }
            void operator=(const AList& other){
                if(this->maxSize<other.size){
                    memdestructor(this->array,this->size);
                    ::operator delete(this->array,this->maxSize*sizeof(T));
                    this->array=(T*)::operator new(other.maxSize*sizeof(T));
                    new(this->array) T[other.size];
                    this->maxSize=other.maxSize;
                    this->size=other.size;
                }
                else
                    if(this->size>other.size)
                        memdestructor(this->array+other.size,this->size-other.size);
                mpv::memcopy(this->array,other.array,other.size);
            }
            void operator=(AList&& other){
                if(this==&other)
                    return;
                memdestructor(this->array,size);
                ::operator delete(this->array,this->maxSize*sizeof(T));
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
                new_list.array=(T*)::operator new(new_list.maxSize*sizeof(T));
                new(new_list.array) T[new_list.size];
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
                    this->array=(T*)::operator new((this->size+other.size)*2*sizeof(T));
                    new(this->array) T[this->size+other.size];
                    if(aux==other.array)
                        mpv::memcopy(this->array,aux,this->size);
                    else
                        mpv::memmove(this->array,aux,this->size);
                    mpv::memcopy(this->array+this->size,other.array,other.size);
                    memdestructor(aux,this->size);
                    ::operator delete(aux,this->maxSize*sizeof(T));
                    this->maxSize=(this->size+other.size)*2;
                }
                else{
                    new(this->array+this->size) T[other.size];
                    mpv::memcopy(this->array+this->size,other.array,other.size);
                }
                this->size+=other.size;
            }
            AList operator*(unsigned int num)const{
                AList new_list;
                if(num==0)
                    return new_list;
                new_list.maxSize=this->size*num*2;
                new_list.array=(T*)::operator new(new_list.maxSize*sizeof(T));
                new(new_list.array) T[this->size*num];
                for(unsigned int i=0;i<num;i++){
                    mpv::memcopy(new_list.array+new_list.size,this->array,this->size);
                    new_list.size+=this->size;
                }
                return new_list;
            }
            void operator*=(const unsigned int num){
                if(num==0){
                    memdestructor(array,size);
                    size=0;
                }
                else{
                    realloc(size*num);
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
                    long long prev_maxSize=maxSize;
                    if(maxSize==0)
                        maxSize=min_maxSize;
                    else
                        maxSize*=2;
                    T* aux=array;
                    array=(T*)::operator new(maxSize*sizeof(T));
                    new(array) T[size];
                    mpv::memmove(array,aux,size);
                    memdestructor(aux,size);
                    ::operator delete(aux,prev_maxSize*sizeof(T));
                }
                new(array+size++) T(data);
            }
            void insert(long long index,T data){
                if(index<0)
                    index+=size+1;
                if(size==maxSize){
                    long long prev_maxSize=maxSize;
                    if(maxSize==0)
                        maxSize=min_maxSize;
                    else
                        maxSize*=2;
                    T* aux=array;
                    array=(T*)::operator new(maxSize*sizeof(T));
                    new(array) T[size+1];
                    mpv::memmove(array,aux,index);
                    mpv::memmove(array+index+1,aux+index,size-index);
                    array[index]=data;
                    memdestructor(aux,size++);
                    ::operator delete(aux,prev_maxSize*sizeof(T));
                }
                else{
                    new(array+size) T();
                    mpv::memmove(array+index+1,array+index,(size++)-index);
                    array[index]=data;
                }
            }
            void del(long long index=-1){
                if(index<0)
                    index+=size;
                mpv::memmove(array+index,array+index+1,(--size)-index);
                array[size].~T();
            }
            T pop(long long index=-1){
                if(index<0)
                    index+=size;
                T aux=(T&&)(array[index]);
                mpv::memmove(array+index,array+index+1,(--size)-index);
                array[size].~T();
                return aux;
            }
            AList sublist(long long start,long long end=-1)const{
                AList new_list;
                if(start<0)
                    start+=size+1;
                if(end<0)
                    end+=size+1;
                new_list.size=end-start;
                if(new_list.size!=0){
                    new_list.maxSize=new_list.size*2;
                    new_list.array=(T*)::operator new(new_list.maxSize*sizeof(T));
                    new(new_list.array) T[new_list.size];
                    mpv::memcopy(new_list.array,this->array+start,new_list.size);
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
                if(new_list.size!=0){
                    new_list.maxSize=new_list.size*2;
                    new_list.array=(T*)::operator new(new_list.maxSize*sizeof(T));
                    new(new_list.array) T[new_list.size];
                    mpv::memmove(new_list.array,this->array+start,new_list.size);
                    mpv::memmove(this->array+start,this->array+end,this->size-end);
                    this->size-=new_list.size;
                    memdestructor(this->array+this->size,new_list.size);
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
                memdestructor(this->array+this->size,deletedSize);
            }
            void setSize_full(long long new_size,const T& data){
                if(maxSize<new_size){
                    memdestructor(array,size);
                    ::operator delete(array,maxSize*sizeof(T));
                    maxSize=new_size*2;
                    array=(T*)::operator new(maxSize);
                    new(array) T[new_size];
                }
                else{
                    if(size>new_size)
                        memdestructor(array+new_size,size-new_size);
                    else if(size<new_size)
                        new(array+size) T[new_size-size];
                }
                size=new_size;
                for(long long i=0;i<size;i++)
                    array[i]=data;
            }
            void setSize(long long new_size){
                if(maxSize<new_size){
                    memdestructor(array,size);
                    ::operator delete(array,maxSize*sizeof(T));
                    maxSize=new_size*2;
                    array=(T*)::operator new(maxSize);
                    new(array) T[new_size];
                }
                else{
                    if(size>new_size)
                        memdestructor(array+new_size,size-new_size);
                    else if(size<new_size)
                        new(array+size) T[new_size-size];
                }
                size=new_size;
            }
            int index(const T& data,int start=0,int end=-1)const{	//retorna -1 si no se encontro el elemento
                if(start<0)
                    start+=size+1;
                if(end<0)
                    end+=size+1;
                for(int i=start;i<end;i++){
                    if(array[i]==data)
                        return i;
                }
                return -1;
            }
            long long len()const{
                return size;
            }
            int count(const T& data)const{
                int counter=0;
                for(int i=0;i<size;i++)
                    if(array[i]==data)
                        counter++;
                return counter;
            }
			bool has(const T& data)const{
				for(int i=0;i<size;i++){
					if(array[i]==data)
						return true;
				}
				return false;
			}
            unsigned int remove(const T& data,bool all=false){
                int found=0;
                for(int i=0;i<size;i++){
                    if(array[i]==data){
                        ++found;
                        mpv::memmove(array+i,array+i+1,(--size)-i);
                        array[size].~T();
                        if(not all)
                            return 1;
                    }
                }
                return found;
            }
            void sort(bool reverse=false){
                mpv::insertion(array,size,reverse);
            }
            void reverse(){
                mpv::reverse(array,size);
            }
			bool empty()const{
				return size==0;
			}
            void clear(){
                memdestructor(array,size);
                size=0;
            }
            ~AList(){
                memdestructor(array,size);
                ::operator delete(array,maxSize*sizeof(T));
            }
            class iterator{
                private:
                    T* ptr;
                public:
                    iterator(T* ptr):ptr(ptr){}
                    T& operator*(){
                        return *ptr;
                    }
                    T* operator->(){
                        return ptr;
                    }
                    iterator& operator++(){
                        ++ptr;
                        return *this;
                    }
                    iterator operator++(int){
                        iterator aux=*this;
                        ++ptr;
                        return aux;
                    }
                    iterator& operator--(){
                        --ptr;
                        return *this;
                    }
                    iterator operator--(int){
                        iterator aux=*this;
                        --ptr;
                        return aux;
                    }
                    bool operator==(const iterator& other)const{
                        return this->ptr==other.ptr;
                    }
                    bool operator!=(const iterator& other)const{
                        return this->ptr!=other.ptr;
                    }
            };
            iterator begin()const{
                return iterator(array);
            }
            iterator end()const{
                return iterator(array+size);
            }
            iterator rbegin()const{
                return iterator(array+size-1);
            }
            iterator rend()const{
                return iterator(array-1);
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
}