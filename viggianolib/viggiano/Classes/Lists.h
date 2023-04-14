#pragma once
#include<iostream>
#define __APPEND(DATA)  Node* new_node=new Node(DATA);\
						if(this->head==nullptr){\
							this->head=new_node;\
							this->tail=new_node;\
						}else{\
							this->tail->next=new_node;\
							new_node->prev=this->tail;\
							this->tail=new_node;\
						}
#define __DEL(INDEX)		Node* CURRENT;\
						if(INDEX>=0){	\
							CURRENT=this->head;\
							for(int I=0;I<INDEX;I++){\
								CURRENT=CURRENT->next;\
							}\
						}\
						else{\
							CURRENT=this->tail;\
							for(int I=-1;I>INDEX;I--)\
								CURRENT=CURRENT->prev;\
						}\
						if(CURRENT==this->tail and CURRENT==this->head){\
							delete CURRENT;\
							this->head=nullptr;\
							this->tail=nullptr;\
						}\
						else if(CURRENT==this->tail){\
							this->tail=CURRENT->prev;\
							this->tail->next=nullptr;\
							delete CURRENT;\
						}\
						else if(CURRENT==this->head){\
							this->head=CURRENT->next;\
							this->head->prev=nullptr;\
							delete CURRENT;\
						}\
						else{\
							CURRENT->prev->next=CURRENT->next;\
							CURRENT->next->prev=CURRENT->prev;\
							delete CURRENT;\
						}


namespace mpv{
	template<typename T=int>
	class List{
		private:
			struct Node{
				T data;
				Node* next=nullptr;
				Node* prev=nullptr;
				Node(T dat):data(dat){INCLNODES}
				Node(){INCLNODES}
				~Node(){
					DECLNODES
					REMAININGLNODES
				}
			};
				Node* head;//	Apunta al nodo que encabeza la lista. 
				Node* tail;//	Apunta al ultimo nodo de la lista. 
				unsigned int sz;
		public:
			List():head(nullptr),tail(nullptr),sz(0){											//Constructor por defecto
				INCLISTS
			}
			List(const List& other):head(nullptr),tail(nullptr){						//Constructor de copia
				for(Node* current=other.head;current!=nullptr;current=current->next){
					__APPEND(current->data)
					//this->append(current->data);
				}
				this->sz=other.sz;
				INCLISTS
			}
			template<typename... Args>
			List(Args... args):head(nullptr),tail(nullptr),sz(0){								//Constructor de inicializacion
				for(const T& dat:{T(args)...}){
					__APPEND(dat)
					this->sz++;
					//this->append(dat);
				}
				INCLISTS
			}
			List(List&& other):head(other.head),tail(other.tail),sz(other.sz){						//Constructor de movimiento
				other.head=nullptr;
				other.tail=nullptr;
				other.sz=0;
				INCLISTS
			}
			void operator=(const List& other){											//Operador de copia(profunda)
				if(this!=&other){
					this->clear();
					for(Node* current=other.head;current!=nullptr;current=current->next){
						__APPEND(current->data)
						//this->append(current->data);
					}
					this->sz=other.sz;
				}
			}
			void operator=(List&& other){												//Operador de movimiento
				this->clear();
				this->head=other.head;
				this->tail=other.tail;
				this->sz=other.sz;
				other.head=nullptr;
				other.tail=nullptr;
				other.sz=0;
			}
			List operator+(const List& other)const{
				List<T> new_list=*this;
				new_list.sz=this->sz+other.sz;
				for(Node* current=other.head;current!=nullptr;current=current->next){
					Node* new_node=new Node(current->data);
					if(new_list.head==nullptr){
						new_list.head=new_node;
						new_list.tail=new_node;
					}
					else{
						new_list.tail->next=new_node;
						new_node->prev=new_list.tail;
						new_list.tail=new_node;
					}
				}
				return new_list;
			}
			void operator+=(const List& other){
				int sz=other.sz,i=0;
				for(Node* current=other.head;i<sz;i++,current=current->next){
					__APPEND(current->data)
					//this->append(current->data);
				}
				this->sz+=other.sz;
			}
			List operator*(unsigned int num)const{
				List<T> new_list;
				for(unsigned int i=0;i<num;i++)
					new_list+=*this;
				return new_list;
			}
			void operator*=(unsigned int num){
				List<T> aux_copy=*this;
				if(num==0)
					this->clear();
				else{
					for(unsigned int i=1;i<num;i++)
						*this+=aux_copy;
				}
			}
			T& operator[](int index)const{
				Node* current;
				if(index>=0){	
					current=this->head;
					for(int i=0;i<index;i++){
						current=current->next;
					}
				}
				else{
					current=this->tail;
					for(int i=-1;i>index;i--){
						current=current->prev;
					}
				}
				return current->data;
			}
			void append(const T& dat){
				__APPEND(dat)
				this->sz++;
			}
			void append(){
				Node* new_node=new Node;
				if(this->head==nullptr){
					this->head=new_node;
					this->tail=new_node;
				}
				else{
					this->tail->next=new_node;
					new_node->prev=this->tail;
					this->tail=new_node;
				}
				this->sz++;
			}
			void insert(int index,T dat){
				Node* new_node=new Node(dat);
				if(this->head==nullptr){
					if(index==0 or index==-1){
						this->head=new_node;
						this->tail=new_node;
					}
				}
				else{
					if(index>=0){
						Node* current=this->head;
						for(int i=0;i<index;i++)
							current=current->next;
						if(current==this->head){
							this->head->prev=new_node;
							new_node->next=this->head;
							this->head=new_node;
						}						
						else if(current==nullptr){
							this->tail->next=new_node;
							new_node->prev=this->tail;
							this->tail=new_node;
						}
						else{
							new_node->next=current;
							new_node->prev=current->prev;
							new_node->prev->next=new_node;
							new_node->next->prev=new_node;
						}
					}
					else{
						Node* current=this->tail;
						for(int i=-1;i>index;i--)
							current=current->prev;
						if(current==this->tail){
							this->tail->next=new_node;
							new_node->prev=this->tail;
							this->tail=new_node;
						}
						else if(current==nullptr){
							this->head->prev=new_node;
							new_node->next=this->head;
							this->head=new_node;
						}
						else{
							new_node->next=current->next;
							new_node->prev=current;
							new_node->prev->next=new_node;
							new_node->next->prev=new_node;							
						}
					}					
				}
				this->sz++;
			}			
			void insert(int index){
				Node* new_node=new Node;
				if(this->head==nullptr){
					if(index==0 or index==-1){
						this->head=new_node;
						this->tail=new_node;
					}
				}
				else{
					if(index>=0){
						Node* current=this->head;
						for(int i=0;i<index;i++)
							current=current->next;
						if(current==this->head){
							this->head->prev=new_node;
							new_node->next=this->head;
							this->head=new_node;
						}						
						else if(current==nullptr){
							this->tail->next=new_node;
							new_node->prev=this->tail;
							this->tail=new_node;
						}
						else{
							new_node->next=current;
							new_node->prev=current->prev;
							new_node->prev->next=new_node;
							new_node->next->prev=new_node;
						}
					}
					else{
						Node* current=this->tail;
						for(int i=-1;i>index;i--)
							current=current->prev;
						if(current==this->tail){
							this->tail->next=new_node;
							new_node->prev=this->tail;
							this->tail=new_node;
						}
						else if(current==nullptr){
							this->head->prev=new_node;
							new_node->next=this->head;
							this->head=new_node;
						}
						else{
							new_node->next=current->next;
							new_node->prev=current;
							new_node->prev->next=new_node;
							new_node->next->prev=new_node;							
						}
					}					
				}
				this->sz++;
			}
			T pop(int index=-1){
				Node* current;
				if(index>=0){	
					current=this->head;
					for(int i=0;i<index;i++){
						current=current->next;
					}
				}
				else{
					current=this->tail;
					for(int i=-1;i>index;i--){
						current=current->prev;
					}
				}
				T aux=current->data;
				if(current==this->tail and current==this->head){
					delete current;
					this->head=nullptr;
					this->tail=nullptr;
				}
				else if(current==this->tail){
					this->tail=current->prev;
					this->tail->next=nullptr;
					delete current;
				}
				else if(current==this->head){
					this->head=current->next;
					this->head->prev=nullptr;
					delete current;
				}
				else{
					current->prev->next=current->next;
					current->next->prev=current->prev;
					delete current;					
				}
				this->sz--;
				return aux;
			}
			void del(int index=-1){
				Node* current;
				if(index>=0){	
					current=this->head;
					for(int i=0;i<index;i++){
						current=current->next;
					}
				}
				else{
					current=this->tail;
					for(int i=-1;i>index;i--){
						current=current->prev;
					}
				}
				if(current==this->tail and current==this->head){
					delete current;
					this->head=nullptr;
					this->tail=nullptr;
				}
				else if(current==this->tail){
					this->tail=current->prev;
					this->tail->next=nullptr;
					delete current;
				}
				else if(current==this->head){
					this->head=current->next;
					this->head->prev=nullptr;
					delete current;
				}
				else{
					current->prev->next=current->next;
					current->next->prev=current->prev;
					delete current;					
				}
				this->sz--;
			}
			List sublist(int start, int end=-1){
				List<T> new_list;
				Node* ptr_start,* ptr_end;
				if(start>=0){
					ptr_start=this->head;
					for(int i=0;i<start;i++)
						ptr_start=ptr_start->next;
				}
				else{
					ptr_start=this->tail;
					for(int i=-1;i>start;i--)
						ptr_start=ptr_start->prev;
					if(ptr_start)
						ptr_start=ptr_start->next;
					else
						ptr_start=head;
				}
				if(end>=0){
					ptr_end=this->head;
					for(int i=0;i<end;i++)
						ptr_end=ptr_end->next;
				}
				else{
					ptr_end=this->tail;
					for(int i=-1;i>end;i--)
						ptr_end=ptr_end->prev;
					if(ptr_end)
						ptr_end=ptr_end->next;
					else
						ptr_end=head;
				}
				while(ptr_start!=ptr_end){
					new_list.append(ptr_start->data);
					ptr_start=ptr_start->next;
				}
				return new_list;
			}
			void wipe(int start, int end=-1){
				Node* ptr_start,* ptr_end;
				if(start>=0){
					ptr_start=this->head;
					for(int i=0;i<start;i++)
						ptr_start=ptr_start->next;
				}
				else{
					ptr_start=this->tail;
					for(int i=-1;i>start;i--)
						ptr_start=ptr_start->prev;
					if(ptr_start)
						ptr_start=ptr_start->next;
					else
						ptr_start=head;
				}
				if(end>=0){
					ptr_end=this->head;
					for(int i=0;i<end;i++)
						ptr_end=ptr_end->next;
				}
				else{
					ptr_end=this->tail;
					for(int i=-1;i>end;i--)
						ptr_end=ptr_end->prev;
					if(ptr_end)
						ptr_end=ptr_end->next;
					else
						ptr_end=head;
				}
				if(ptr_start==ptr_end)
					return;
				if(end<0)
					end=sz+end+1;
				if(start<0)
					start=sz+start+1;
				sz-=end-start;
				Node* start_prev=ptr_start->prev,* aux;
				while(ptr_start!=ptr_end){
					aux=ptr_start;
					ptr_start=ptr_start->next;
					delete aux;
				}
				if(start_prev and ptr_end){
					start_prev->next=ptr_end;
					ptr_end->prev=start_prev;
				}
				else if(start_prev){
					tail=start_prev;
					start_prev->next=nullptr;
				}
				else if(ptr_end){
					head=ptr_end;
					ptr_end->prev=nullptr;
				}
				else{
					head=nullptr;
					tail=nullptr;
				}
			}
			List cut(int start, int end=-1){
				List<T> new_list;
				Node* ptr_start,* ptr_end;
				if(start>=0){
					ptr_start=this->head;
					for(int i=0;i<start;i++)
						ptr_start=ptr_start->next;
				}
				else{
					ptr_start=this->tail;
					for(int i=-1;i>start;i--)
						ptr_start=ptr_start->prev;
					if(ptr_start)
						ptr_start=ptr_start->next;
					else
						ptr_start=head;
				}
				if(end>=0){
					ptr_end=this->head;
					for(int i=0;i<end;i++)
						ptr_end=ptr_end->next;
				}
				else{
					ptr_end=this->tail;
					for(int i=-1;i>end;i--)
						ptr_end=ptr_end->prev;
					if(ptr_end)
						ptr_end=ptr_end->next;
					else
						ptr_end=head;
				}
				if(ptr_start==ptr_end)
					return new_list;
				if(end<0)
					end=sz+end+1;
				if(start<0)
					start=sz+start+1;
				sz-=end-start;
				new_list.sz=end-start;
				Node* start_prev=ptr_start->prev;
				new_list.head=ptr_start;
				ptr_start->prev=nullptr;
				if(ptr_end){
					ptr_end->prev->next=nullptr;
					new_list.tail=ptr_end->prev;
				}
				else{
					while(ptr_start->next){
						ptr_start=ptr_start->next;
					}
					new_list.tail=ptr_start;
				}
				if(start_prev and ptr_end){
					start_prev->next=ptr_end;
					ptr_end->prev=start_prev;
				}
				else if(start_prev){
					this->tail=start_prev;
					start_prev->next=nullptr;
				}
				else if(ptr_end){
					this->head=ptr_end;
					ptr_end->prev=nullptr;
				}
				else{
					this->head=nullptr;
					this->tail=nullptr;
				}
				return new_list;
			}

			void print(bool reverse=false){
				if(not head){
					printf("[]");
					return;
				}
				std::cout<<'[';
				if(not reverse){
					for(Node* i=head;i!=tail->next;i=i->next){
						std::cout<<i->data;
						if(i!=tail)
							std::cout<<", ";
					}					
				}
				else{
					for(Node* i=tail;i!=head->prev;i=i->prev){
						std::cout<<i->data;
						if(i!=head)
							std::cout<<", ";
					}
				}
				std::cout<<']';
			}
			void println(bool reverse=false){
				this->print(reverse);
				printf("\n");
			}			
			int len()const{
				int i=0;
				for(Node* current=this->head;current!=nullptr;i++){
					current=current->next;
				}
				return i;
			}
			inline int size()const{
				#ifdef DEBUG
				if(this->len()!=sz){
					std::cout<<"\nSIZE AND LEN DO NOT MATCH\n";
					std::cout<<"size: "<<sz<<"\nlen: "<<len()<<std::endl;
					exit(-1);
				}
				#endif
				return sz;
			}
			void setSize_full(int size,const T& data){
				Node* p=head;
				for(int i=0;p!=nullptr and i<size;p=p->next,i++)
					p->data=data;
				while(this->sz<size){
					__APPEND(data)
					this->sz++;
				}
				while(this->sz>size){
					__DEL(-1);
					this->sz--;
				}
			}
			void setSize(int size){
				while(this->sz<size){
					Node* new_node=new Node;
					if(this->head==nullptr){
						this->head=new_node;
						this->tail=new_node;
					}
					else{
						this->tail->next=new_node;
						new_node->prev=this->tail;
						this->tail=new_node;
					}
					this->sz++;
				}
				while(this->sz>size){
					__DEL(-1)
					this->sz--;
				}
			}
 			int index(const T& data,int start=0,int end=-1)const{	//retorna -1 si no se encontro el elemento
				if(start<0)
					start+=this->sz+1;
				if(end<0)
					end+=this->sz+1;
				if(start>=end)
					return -1;
				Node* ptr_start=this->head,* ptr_end=this->head;
				for(int i=0;i<start;i++)
					ptr_start=ptr_start->next;
				for(int i=0;i<end;i++)
					ptr_end=ptr_end->next;
				for(int i=0;ptr_start!=ptr_end;ptr_start=ptr_start->next,i++){
					if(ptr_start->data==data)
						return i+start;
				}
				return -1;
			}
			int count(const T& dat)const{
				int counter=0;
				Node* current=this->head;
				while(current!=nullptr){
					if(current->data==dat)
						counter++;
					current=current->next;
				}
				return counter;
			}		
			unsigned int remove(const T& dat,bool all=false){	//devuelve la cantidad removida
				Node* aux,* current=this->head;
				unsigned int found=0;
				while(current!=nullptr){
					if(current->data==dat){
						if(current==this->tail and current==this->head){
							delete current;
							this->head=nullptr;
							this->tail=nullptr;
							aux=nullptr;
						}
						else if(current==this->tail){
							this->tail=current->prev;
							this->tail->next=nullptr;
							delete current;
							aux=nullptr;
						}
						else if(current==this->head){
							aux=this->head->next;
							this->head=current->next;
							this->head->prev=nullptr;
							delete current;
						}
						else{
							aux=current->next;
							current->prev->next=current->next;
							current->next->prev=current->prev;
							delete current;					
						}
						this->sz--;
						
						if(all==false)
							return 1;
						current=aux;
						found++;
					}
					else
						current=current->next;
				}
				return found;
			}
			bool has(const T& dat)const{
				for(Node* i=this->head;i!=nullptr;i=i->next){
					if(i->data==dat)
						return true;
				}
				return false;
			}
			bool empty()const{
				return this->head==nullptr;
			}
			void clear(){
				while(this->head!=nullptr){
					__DEL(-1)
				}
				this->sz=0;
			}
			template<typename ...Args>
			void extend(Args... args){
				for(const T& dat:{T(args)...}){
					__APPEND(dat)
					this->sz++;
				}
			}				
			void sort(bool reverse=false){
				Node* i;
				Node* j;
				T aux;
				if(reverse==false){
					for(i=this->head;i!=nullptr;i=i->next){
						for(j=i,aux=i->data;j!=this->head and aux<j->prev->data;j=j->prev){
							j->data=j->prev->data;
						}
						j->data=aux;
					}
				}
				else{
					for(i=this->head;i!=nullptr;i=i->next){
						for(j=i,aux=i->data;j!=this->head and aux>j->prev->data;j=j->prev){
							j->data=j->prev->data;
						}
						j->data=aux;
					}
				}
			}
			void reverse(){
				T aux;
				for(Node* i=this->head,* j=this->tail;i!=j and i->prev!=j;i=i->next,j=j->prev){
					aux=i->data;
					i->data=j->data;
					j->data=aux;
				}
			}
			~List(){
				while(this->head!=nullptr){
					__DEL(-1)
				}
				DECLISTS
				REMAININGLISTS
			}
			class iterator{
				private:
					Node* ptr;
				public:
					iterator(Node* ptr):ptr(ptr){}
					T& operator*(){
						return ptr->data;
					}
					T* operator->(){
						return &(ptr->data);
					}
					iterator& operator++(){
						ptr=ptr->next;
						return *this;
					}
					iterator operator++(int){
						iterator aux=*this;
						ptr=ptr->next;
						return aux;
					}
					iterator& operator--(){
						ptr=ptr->prev;
						return *this;
					}
					iterator operator--(int){
						iterator aux=*this;
						ptr=ptr->prev;
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
				return iterator(head);
			}
			iterator end()const{
				return iterator(nullptr);
			}
			iterator rbegin()const{
				return iterator(tail);
			}
			iterator rend()const{
				return iterator(nullptr);
			}
	};
	template<typename T>
	std::ostream& operator<<(std::ostream& stream,const List<T>& list){
		stream<<'[';
		for(auto i=list.begin();i!=list.end();i++){
			stream<<*i;
			if(i!=list.rbegin())
				std::cout<<", ";		
		}
		stream<<']';
		return stream;
	}
	// template<typename T>
	// std::ostream& operator<<(std::ostream& stream,const List<T>& list){
	// 	stream<<'[';
	// 	for(int i=0,size=list.len();i<size;i++){
	// 		stream<<list[i];
	// 		if(i<size-1)
	// 			std::cout<<", ";		
	// 	}
	// 	stream<<']';
	// 	return stream;
	// }
}