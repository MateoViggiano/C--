#pragma once
namespace mpv{
	template<typename T=long double>
	class Queue{
		private:
			struct Node{
				T data;
				Node* next;
			};
			Node* front;
			Node* back;
		public:
			void operator=(const Queue& other)=delete;		
			Queue(const Queue& other)=delete;
			Queue():front(nullptr),back(nullptr){
				INCQUEUES
			}
			void push(const T& dat){
				Node* new_node=new Node;
				new_node->data=dat;
				new_node->next=nullptr;
				if(this->front==nullptr)
					this->front=new_node;	
				else
					this->back->next=new_node;
				this->back=new_node;	
			}
			T& Front(){
				return this->front->data;
			}
			bool empty(){
				return this->front==nullptr;
			}
			T pop(){
				Node* aux=this->front;
				T aux_data=this->front->data;
				this->front=this->front->next;
				delete aux;
				return aux_data;
			}
			~Queue(){
				while(this->empty()==false)
					this->pop();
				DECQUEUES
				REMAININGQUEUES
			}
			class iterator{
				private:
					Node* ptr;
				public:
				iterator(Node* p):ptr(p){}
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
					Node* aux=*this;
					ptr=ptr->next;
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
				return iterator(front);
			}
			iterator end()const{
				return iterator(nullptr);
			}
	};
	template<typename T=long double>
	class Stack{
		private:
			struct Node{
				T data;
				Node* next;
			};
			Node* top;
		public:
			void operator=(const Stack& refStack)=delete;			
			Stack(const Stack& refStack)=delete;
			Stack():top(nullptr){
				INCSTACKS
			}
			void push(T dat){
				Node* new_node=new Node;
				new_node->data=dat;
				new_node->next=this->top;
				this->top=new_node;
			}
			T& Top(){
				return this->top->data;
			}
			bool empty(){
				return this->top==nullptr;
			}
			T pop(){
				Node* aux=this->top;
				T aux_data=top->data;
				this->top=this->top->next;
				delete aux;
				return aux_data;
			}
			~Stack(){
				while(this->empty()==false)
					this->pop();
				DECSTACKS
				REMAININGSTACKS
			}
			class iterator{
				private:
					Node* ptr;
				public:
				iterator(Node* p):ptr(p){}
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
					Node* aux=*this;
					ptr=ptr->next;
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
				return iterator(top);
			}
			iterator end()const{
				return iterator(nullptr);
			}
	};
}