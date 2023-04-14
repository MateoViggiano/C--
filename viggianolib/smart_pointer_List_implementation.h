#pragma once
#include "viggiano.h"
using vgg::sPtr;
template<typename T=int>
class List{
	private:
		struct Node{
			T data;
			sPtr<Node> next;
			sPtr<Node> prev;
			void set_null(){
				next=nullptr;
				prev=nullptr;
			}
		};
			sPtr<Node> header;/*			Apunta al nodo que encabeza la lista. 
								Este no tiene ni dato ni nodo anterior(ambos son null),
								solo tiene un nodo siguiente que apunta al primer elemento de la lista(indice[0])
		*/
			sPtr<Node> trailer;/*		Apunta al ultimo nodo de la lista. 
								Este no tiene ni dato ni nodo siguiente(ambos son null),
								solo tiene un nodo anterior que apunta al ultimo elemento de la lista(indice[-1])
		*/
			sPtr<unsigned int> refCount;/*	Apunta a la cantidad de listas con punteros que apuntan a las mismas direcciones.
								Estas son creadas por el constructor de copia o por la funcion que sobrecarga el "="
								El contador de referencias se inicializa como "1" al llamar al constructor por defecto
								o al constructor de inicializacion.
								En los objetos copiados, al tener todos los punteros el mismo valor, *refCount puede 
								ser modificado desde cualquiera de estos objetos.
								*refCount se va incrementando(llamando al constructor de copia o al operador "="),
								y decrementando(llamando al destructor).
								Cada vez que se llama al destructor, este decrementa el contador de referencias
								y evalua si el objeto debe ser destruido(*refCount==0) o no.
								De esta forma se evitan errores de segmentacion al intentar liberar 2 veces la misma 
								memoria.
		*/
	public:
		List():header(new Node),trailer(new Node),refCount(new unsigned int(1)){						//Constructor por defecto
			this->trailer->prev=this->header;
			this->header->next=this->trailer;
			this->header->prev=nullptr;
			this->trailer->next=nullptr;
			INCLISTS
		}
		List(const List& other):header(other.header),trailer(other.trailer),refCount(other.refCount){	//Constructor de copia
			(*this->refCount)++;
			INCLISTS
		}
		template<typename... Args>
		List(Args... args):header(new Node),trailer(new Node),refCount(new unsigned int(1)){			//Constructor de inicializacion
			this->trailer->prev=this->header;
			this->header->next=this->trailer;
			this->header->prev=nullptr;
			this->trailer->next=nullptr;
			for(const T& dat:{static_cast<T>(args)...})
				this->append(dat);
			INCLISTS
		}
		void Init(){//Su usa para construir un objeto sobre memoria reinterpretada(como la que se reserva con un malloc). No con el new, que llama al constructor automaticamente
/*				header=reinterpret_cast<sPtr<Node>>(malloc(sizeof(Node)));
			trailer=reinterpret_cast<sPtr<Node>>(malloc(sizeof(Node)));
			refCount=reinterpret_cast<unsigned int*>(malloc(sizeof(Node)));
			*refCount=1;*/
			header=new Node;
			trailer=new Node;
			refCount=new unsigned int(1);
			this->trailer->prev=this->header;
			this->header->next=this->trailer;
			this->header->prev=nullptr;
			this->trailer->next=nullptr;
			INCLISTS
		}
		void operator=(const List& other){																//Operador de copia(no profunda)
			if(this!=&other){
				if(--(*this->refCount)==0){
					this->clear();
					this->header->set_null();
					this->trailer->set_null();
					this->refCount=nullptr;					
				}
				this->header=other.header;
				this->trailer=other.trailer;
				this->refCount=other.refCount;
				(*this->refCount)++;
			}
		}
		List operator+(const List& other){
			List<T> new_list=this->copy();
			sPtr<Node> current=other.header->next;
			while(current!=other.trailer){
				new_list.append(current->data);
				current=current->next;
			}
			return new_list;
		}
		void operator+=(List other){
			List<T> other_cpy=other.copy();
			sPtr<Node> current=other_cpy.header->next;
			while(current!=other_cpy.trailer){
				this->append(current->data);
				current=current->next;
			}
		}
		List operator*(const unsigned int& num){
			List<T> aux_copy=this->copy();
			List<T> new_list=this->copy();
			if(num==0)
				new_list.clear();
			else if(num>0){
				for(int i=1;i<num;i++){
					new_list=new_list+aux_copy;
				}
			}
			return new_list;
		}
		void operator*=(const unsigned int& num){
			List<T> aux_copy=this->copy();
			if(num==0)
				this->clear();
			else if(num>0){
				for(int i=1;i<num;i++){
					*(this)=*(this)+aux_copy;
				}
			}
		}
		T& operator[](int index){
			int i;
			sPtr<Node> current;
			if(index>=0){	
				current=this->header->next;
				for(i=0;i<index;i++){
					current=current->next;
				}
			}
			else{
				current=this->trailer->prev;
				for(i=-1;i>index;i--){
					current=current->prev;
				}
			}
			return current->data;
		}
		void append(const T& dat){
			sPtr<Node> new_node=new Node;
			new_node->data=dat;
			new_node->next=this->trailer;
			new_node->prev=this->trailer->prev;
			this->trailer->prev->next=new_node;
			this->trailer->prev=new_node;
		}
		void append_none(){
			sPtr<Node> new_node=new Node;
			new_node->next=this->trailer;
			new_node->prev=this->trailer->prev;
			this->trailer->prev->next=new_node;
			this->trailer->prev=new_node;
		}
		void insert(T dat,int index=0){
			int i;
			sPtr<Node> new_node=new Node;
			new_node->data=dat;
			sPtr<Node> current;
			if(index>=0){
				current=this->header->next;
				for(i=0;i<index;i++)
					current=current->next;
				new_node->next=current;
				new_node->prev=current->prev;
				new_node->prev->next=new_node;
				new_node->next->prev=new_node;
			}
			else{
				current=this->trailer->prev;
				for(i=-1;i>index;i--)
					current=current->prev;
				new_node->next=current->next;
				new_node->prev=current;
				new_node->prev->next=new_node;
				new_node->next->prev=new_node;
			}				
		}			
		void insert_none(int index=0){
			int i;
			sPtr<Node> new_node=new Node;
			sPtr<Node> current;
			if(index>=0){
				current=this->header->next;
				for(i=0;i<index;i++)
					current=current->next;
				new_node->next=current;
				new_node->prev=current->prev;
				new_node->prev->next=new_node;
				new_node->next->prev=new_node;
			}
			else{
				current=this->trailer->prev;
				for(i=-1;i>index;i--)
					current=current->prev;
				new_node->next=current->next;
				new_node->prev=current;
				new_node->prev->next=new_node;
				new_node->next->prev=new_node;
			}				
		}			
		T get(int index){
			int i;
			sPtr<Node> current;
			if(index>=0){	
				current=this->header->next;
				for(i=0;i<index;i++){
					current=current->next;
				}
			}
			else{
				current=this->trailer->prev;
				for(i=-1;i>index;i--){
					current=current->prev;
				}
			}
			return current->data;
		}			
		void set(T dat,int index){
			int i;
			sPtr<Node> current;
			if(index>=0){	
				current=this->header->next;
				for(i=0;i<index;i++){
					current=current->next;
				}
			}
			else{
				current=this->trailer->prev;
				for(i=-1;i>index;i--){
					current=current->prev;
				}
			}
			current->data=dat;
		}			
		T pop(int index=-1){
			int i;
			sPtr<Node> current;
			if(index>=0){	
				current=this->header->next;
				for(i=0;i<index;i++){
					current=current->next;
				}
			}
			else{
				current=this->trailer->prev;
				for(i=-1;i>index;i--){
					current=current->prev;
				}
			}
			T aux=current->data;
			current->prev->next=current->next;
			current->next->prev=current->prev;
			current->set_null();
			return aux;
		}			
		void del(int index=-1){
			int i;
			sPtr<Node> current;
			if(index>=0){	
				current=this->header->next;
				for(i=0;i<index;i++){
					current=current->next;
				}
			}
			else{
				current=this->trailer->prev;
				for(i=-1;i>index;i--){
					current=current->prev;
				}
			}
			current->prev->next=current->next;
			current->next->prev=current->prev;
			current->set_null();
		}			
		void print(bool reverse=false,int start=0,int end=-1){
			int i;
			sPtr<Node> aux_start;
			sPtr<Node> aux_end;
			if(start>=0){
				aux_start=this->header->next;
				for(i=0;i<start;i++)
					aux_start=aux_start->next;
			}
			else{
				aux_start=this->trailer->prev;
				for(i=-1;i>start;i--)
					aux_start=aux_start->prev;
			}
			if(end>=0){
				aux_end=this->header->next;
				for(i=0;i<end;i++)
					aux_end=aux_end->next;
			}
			else{
				aux_end=this->trailer->prev;
				for(i=-1;i>start;i--)
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
		int len(){
			int i;
			sPtr<Node> current=this->header->next;
			for(i=0;current!=this->trailer;i++){
				current=current->next;
			}
			return i;
		}			
		void setSize_full(int size,int dat){
			this->clear();
			for(int i=0;i<size;i++){
				this->append(dat);
			}
		}			
		void setSize(int size,bool clear=false){
			int i;
			if(clear){
				this->clear();
				for(i=0;i<size;i++){
					sPtr<Node> new_node=new Node;
					new_node->prev=this->trailer->prev;
					new_node->next=this->trailer;
					this->trailer->prev->next=new_node;
					this->trailer->prev=new_node;
				}
			}
			else{
				int length=this->len();
				if((size-length)>=0){
					for(i=0;i<size-length;i++){	
						sPtr<Node> new_node=new Node;
						new_node->prev=this->trailer->prev;
						new_node->next=this->trailer;
						this->trailer->prev->next=new_node;
						this->trailer->prev=new_node;
					}
				}
				else{
					for(i=0;i>size-length;i--){
						this->del();
					}
				}
			}
		}			
		int index(T dat,int start=0,int end=-1){	//retorna -1 si el elemento no es encontrado
			int i;
			sPtr<Node> aux_start;
			sPtr<Node> aux_end;
			if(start>=0){
				aux_start=this->header->next;
				for(i=0;i<start;i++)
					aux_start=aux_start->next;
			}
			else{
				aux_start=this->trailer->prev;
				for(i=-1;i>start;i--)
					aux_start=aux_start->prev;
			}
			if(end>=0){
				aux_end=this->header->next;
				for(i=0;i<end;i++)
					aux_end=aux_end->next;
			}
			else{
				aux_end=this->trailer->prev;
				for(i=-1;i>start;i--)
					aux_end=aux_end->prev;
			}
			for(i=0;aux_start!=aux_end->next;i++,aux_start=aux_start->next){
				if(aux_start->data==dat)
					return i+start;
			}
			return -1;
		}			
		int count(T dat){
			int counter=0;
			sPtr<Node> current=this->header->next;
			while(current!=this->trailer){
				if(current->data==dat)
					counter++;
				current=current->next;
			}
			return counter;
		}			
		void remove(T dat,bool all=false){
			sPtr<Node> aux;
			sPtr<Node> current=this->header->next;
			while(current!=this->trailer){
				if(current->data==dat){
					aux=current->prev;
					current->prev->next=current->next;
					current->next->prev=current->prev;
					current->set_null();
					if(all==false)
						break;
					current=aux;
				}
			current=current->next;
			}
		}			
		bool has(T dat){
			sPtr<Node> i;
			for(i=this->header->next;i!=this->trailer;i=i->next){
				if(i->data==dat)
					return true;
			}
			return false;
		}
		bool empty(){
			return this->header->next==this->trailer and this->trailer->prev==this->header;
		}			
		void clear(){
			while(this->empty()==false)
				this->del();
		}			
		void input(int n,bool clear=true){
			T dat;
			if(clear)
				this->clear();
			for(int i=0;i<n;i++){
				std::cin>>dat;
				this->append(dat);
			}
		}			
		template<typename ...Args>
		void extend(Args... args){
			for(const T& dat:{static_cast<T>(args)...}){
				this->append(dat);
			}
		}			
		List copy(){
			sPtr<Node> current=this->header->next;
			List<T> new_list;
			while(current!=this->trailer){
				new_list.append(current->data);
				current=current->next;
			}
			return new_list;
		}			
		void sort(bool reverse=false){
			sPtr<Node> i;
			sPtr<Node> j;
			T aux;
			if(reverse==false){
				for(i=this->header->next;i!=this->trailer;i=i->next){
					for(j=i,aux=i->data;j!=this->header->next and aux<j->prev->data;j=j->prev){
						j->data=j->prev->data;
					}
					j->data=aux;
				}
			}
			else{
				for(i=this->header->next;i!=this->trailer;i=i->next){
					for(j=i,aux=i->data;j!=this->header->next and aux>j->prev->data;j=j->prev){
						j->data=j->prev->data;
					}
					j->data=aux;
				}
			}
		}
		void reverse(){
			sPtr<Node> i;
			sPtr<Node> j;
			T aux;
			for(i=this->header->next,j=this->trailer->prev;i!=j and i->prev!=j;i=i->next,j=j->prev){
				aux=i->data;
				i->data=j->data;
				j->data=aux;
			}
		}
		~List(){
			if(--(*this->refCount)==0){
				this->clear();
				this->header->set_null();
				this->trailer->set_null();
				this->refCount=nullptr;
			}
			DECLISTS
			REMAININGLISTS
		}
};
namespace matrixFeatures{
	template<typename T>
	void setSize(List<List<T>>& list,const int row,const int col){
		list.clear();
		for(int i=0;i<row;i++){
			List<T> new_list;
			new_list.setSize(col);
			list.append(new_list);
		}
	}
	template<typename T>
	void setSize_full(List<List<T>>& list,const int row,const int col,T dat){
		list.clear();
		for(int i=0;i<row;i++){
			List<int> new_list;
			new_list.setSize_full(col,dat);
			list.append(new_list);
		}
	}
	template<typename T>
	void input(List<List<T>>& list,const int row,const int col){
		list.clear();
		for(int i=0;i<row;i++){
			List<int> new_list;
			new_list.input(col);
			list.append(new_list);
		}
	}
	template<typename T>
	void print(List<List<T>>& list){
		int len=list.len();
		for(int i=0;i<len;i++){
			list[i].println();
		}
	}
}
