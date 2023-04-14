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
				Node(T dat):data(dat){}
				Node(){}
			};
				Node* head;//	Apunta al nodo que encabeza la lista. 
				Node* tail;//	Apunta al ultimo nodo de la lista. 
		public:
			List():head(nullptr),tail(nullptr){											//Constructor por defecto
				INCLISTS
			}
			List(const List& other):head(nullptr),tail(nullptr){						//Constructor de copia
				for(Node* current=other.head;current!=nullptr;current=current->next){
					__APPEND(current->data)
					//this->append(current->data);
				}
				INCLISTS
			}
			template<typename... Args>
			List(Args... args):head(nullptr),tail(nullptr){								//Constructor de inicializacion
				for(const T& dat:{static_cast<T>(args)...}){
					__APPEND(dat)
					//this->append(dat);
				}
				INCLISTS
			}
			List(List&& other):head(other.head),tail(other.tail){						//Constructor de movimiento
				other.head=nullptr;
				other.tail=nullptr;
				INCLISTS
			}
			void operator=(const List& other){											//Operador de copia(profunda)
				if(this!=&other){
					this->clear();
					for(Node* current=other.head;current!=nullptr;current=current->next){
						__APPEND(current->data)
						//this->append(current->data);
					}
				}
			}
			void operator=(List&& other){												//Operador de movimiento
				this->clear();
				this->head=other.head;
				this->tail=other.tail;
				other.head=nullptr;
				other.tail=nullptr;
			}
			List operator+(const List& other)const{
				List<T> new_list=*this;
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
				int sz=other.len(),i=0;
				for(Node* current=other.head;i<sz;i++,current=current->next){
					__APPEND(current->data)
					//this->append(current->data);
				}
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
			}
			void print(bool reverse=false,int start=0,int end=-1){
				if(not this->head){
					printf("[]");
					return;
				}
				Node* aux_start;
				Node* aux_end;
				if(start>=0){
					aux_start=this->head;
					for(int i=0;i<start;i++)
						aux_start=aux_start->next;
				}
				else{
					aux_start=this->tail;
					for(int i=-1;i>start;i--)
						aux_start=aux_start->prev;
				}
				if(end>=0){
					aux_end=this->head;
					for(int i=0;i<end;i++)
						aux_end=aux_end->next;
				}
				else{
					aux_end=this->tail;
					for(int i=-1;i>end;i--)
						aux_end=aux_end->prev;
				}
				printf("[");
				if(reverse==false){
					while(aux_start!=aux_end->next){
						std::cout<<aux_start->data;
						if(aux_start!=aux_end)
							printf(", ");
						aux_start=aux_start->next;
					}
				}
				else{
					while(aux_end!=aux_start->prev){
						std::cout<<aux_end->data;
						if(aux_end!=aux_start)
							printf(", ");
						aux_end=aux_end->prev;
					}
				}
				printf("]");
			}
			void println(bool reverse=false,int start=0,int end=-1){
				this->print(reverse,start,end);
				printf("\n");
			}			
			int len()const{
				int i=0;
				for(Node* current=this->head;current!=nullptr;i++){
					current=current->next;
				}
				return i;
			}		
			void setSize_full(int size,T dat,bool clear=true){
				if(clear){
					this->clear();
					for(int i=0;i<size;i++){
						__APPEND(dat)
					}
				}
				else{
					int length=this->len();
					if((size-length)>=0){
						for(int i=0;i<size-length;i++){	
							__APPEND(dat)
						}
					}
					else{
						for(int i=0;i>size-length;i--){
							__DEL(-1)
						}
					}
				}
			}
			void setSize(int size,bool clear=false){
				if(clear){
					this->clear();
					for(int i=0;i<size;i++){
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
					}
				}
				else{
					int length=this->len();
					if((size-length)>=0){
						for(int i=0;i<size-length;i++){	
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
						}
					}
					else{
						for(int i=0;i>size-length;i--){
							__DEL(-1)
						}
					}
				}
			}
			template<typename D>
 			int index(D dat,int start=0,int end=-1)const{	//retorna -1 si no se encontro el elemento
				int this_size=this->len();
				if(((start>=0 and end>=0 or start<0 and end<0) and start>end) or (start>=0 and end<0 and start>this_size+end) or (start<0 and end>=0 and this_size+start>end))
					return -1;
				Node* aux_start;
				Node* aux_end;
				if(start>=0){
					aux_start=this->head;
					for(int i=0;i<start;i++)
						aux_start=aux_start->next;
				}
				else{
					aux_start=this->tail;
					for(int i=-1;i>start;i--)
						aux_start=aux_start->prev;
					start=this_size+start;
				}
				if(end>=0){
					aux_end=this->head;
					for(int i=0;i<end;i++)
						aux_end=aux_end->next;
				}
				else{
					aux_end=this->tail;
					for(int i=-1;i>end;i--)
						aux_end=aux_end->prev;
				}
			
				for(int i=0;aux_start!=aux_end->next;i++,aux_start=aux_start->next){
					if(aux_start->data==dat)
						return i+start;
				}
				return -1;
			}
			template<typename D>			
			int count(D dat)const{
				int counter=0;
				Node* current=this->head;
				while(current!=nullptr){
					if(current->data==dat)
						counter++;
					current=current->next;
				}
				return counter;
			}
			template<typename D>			
			void remove(D dat,bool all=false){
				Node* aux,* current=this->head;
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
						if(all==false)
							break;
						current=aux;
					}
					else
						current=current->next;
				}
			}
			template<typename D>
			bool has(D dat)const{
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
			}
 			void input(int n,bool clear=true){
				T dat;
				if(clear)
					this->clear();
				for(int i=0;i<n;i++){
					std::cin>>dat;
					__APPEND(dat)
				}
			}			
			template<typename ...Args>
			void extend(Args... args){
				for(const T& dat:{static_cast<T>(args)...}){
					__APPEND(dat)
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
			struct iterator{
				Node* ptr;
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
				bool operator==(const iterator other)const{
					return this->ptr==other.ptr;
				}
				bool operator!=(const iterator other)const{
					return this->ptr!=other.ptr;
				}
			};
			iterator begin(){
				return iterator(head);
			}
			iterator end(){
				return iterator(nullptr);
			}
	};
	template<typename T>
	std::ostream& operator<<(std::ostream& stream,List<T>& list){
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