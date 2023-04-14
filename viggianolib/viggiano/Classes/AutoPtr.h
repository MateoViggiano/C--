#pragma once
namespace mpv{
	template<typename T,bool array>
	class sPtr;
	template<typename T,bool array>
	class wPtr;
	template<typename T,bool array>
	class uPtr;

	template<typename T,bool array>
	class Pointer{
		protected:
			T* data;
		public:
			Pointer(T* dat):data(dat){}
			T& operator*()const{
				return *this->data;
			}
			T* operator->()const{
				return this->data;
			}
			T& operator[](int index)const{
				return *(this->data+index);
			}
 			bool operator==(const Pointer<T,array>& other)const{		//Comparan las direcciones de memoria
				return this->data==other.data;
			}
			bool operator!=(const Pointer<T,array>& other)const{
				return this->data!=other.data;
			}
			bool operator<=(const Pointer<T,array>& other)const{
				return this->data<=other.data;
			}
			bool operator>=(const Pointer<T,array>& other)const{
				return this->data>=other.data;
			}
			bool operator<(const Pointer<T,array>& other)const{
				return this->data<other.data;
			}
			bool operator>(const Pointer<T,array>& other)const{
				return this->data>other.data;
			}
	};
	struct CtrlBlock{	
		unsigned int sharedCount;
		unsigned int weakCount;
		CtrlBlock():sharedCount(1),weakCount(1){
			INCCTRLBLOCKS
		}
		CtrlBlock(const CtrlBlock& other):sharedCount(other.sharedCount),weakCount(other.weakCount){
			INCCTRLBLOCKS
		}
		explicit CtrlBlock(unsigned int init_counters):sharedCount(init_counters),weakCount(init_counters){
			INCCTRLBLOCKS
		}
		~CtrlBlock(){
			DECCTRLBLOCKS
			REMAININGCTRLBLOCKS
		}
	};
	template<typename T,bool array=false>
	class sPtr:public Pointer<T,array>{
		friend class wPtr<T,array>;
		private:
			CtrlBlock* refCount;
			void release_ownership(){	//se usa con this->release_ownership();
				if(this->refCount!=nullptr){//	El puntero actual deja de apuntar a la memoria dinamica de la que era dueño, si esta no tiene mas dueños la memoria que ocupaba es liberada
					if((--this->refCount->sharedCount)==0){	//Si sharedCount llega a 0 borra la memoria a la que apunta
						if(array)
							delete[] this->data;
						else
							delete this->data;
						if(--this->refCount->weakCount==0)	//Pero solo borra el contador de referencias si weakCount tambien es 0. En caso de que 
							delete this->refCount;			//weakCount no sea 0 refCount no se borrara y el destructor del wPtr se ocupara de esto
					}
				}
			}
			sPtr(wPtr<T,array> weakPtr):Pointer<T,array>(weakPtr.data),refCount(weakPtr.refCount){	//Constructor de copia de punteros debiles
				INCSTRONGPOINTERS
				if(weakPtr.data==nullptr)
					refCount=nullptr;
				else
					refCount->sharedCount++;
			}
		public:
			sPtr():Pointer<T,array>(nullptr),refCount(nullptr){										//Constructor por defecto
				INCSTRONGPOINTERS
			}
			sPtr(const sPtr& other):Pointer<T,array>(other.data),refCount(other.refCount){			//Constructor de copia
				if(this->refCount!=nullptr)
					this->refCount->sharedCount++;
				INCSTRONGPOINTERS
			}					  
			sPtr(T* dat):Pointer<T,array>(dat),refCount(nullptr){									//Constructor de inicializacion
				if(dat!=nullptr)
					this->refCount=new CtrlBlock;
				INCSTRONGPOINTERS	
			}
			sPtr(sPtr&& other):Pointer<T,array>(other.data),refCount(other.refCount){				//Constructor de movimiento
				other.refCount=nullptr;
				other.data=nullptr;
				INCSTRONGPOINTERS
			}
			void operator=(const sPtr& other){														//Operador de copia
				this->release_ownership();
				this->refCount=other.refCount;
				this->data=other.data;
				if(this->refCount!=nullptr)
					this->refCount->sharedCount++;
			}
			void operator=(T* dat){																	//Operador de asignacion
				this->release_ownership();
				if(dat!=nullptr){
					this->refCount=new CtrlBlock;
					this->data=dat;
				}
				else{
					this->refCount=nullptr;
					this->data=nullptr;
				}
			}
			void operator=(sPtr&& other){															//Operador de movimiento
				if(this==&other)
					return;
				this->release_ownership();
				this->refCount=other.refCount;
				this->data=other.data;
				other.refCount=nullptr;
				other.data=nullptr;
			}
			unsigned int currentOwners()const{
				return this->refCount==nullptr? 0 : this->refCount->sharedCount;
			}
			~sPtr(){
				DECSTRONGPOINTERS
				REMAININGSTRONGPOINTERS
				this->release_ownership();
			}
	};
	template<typename T,bool array=false>
	class wPtr:public Pointer<T,array>{
		friend class sPtr<T,array>;
		private:
			CtrlBlock* refCount;
		public:
			wPtr():Pointer<T,array>(nullptr),refCount(nullptr){										//Constructor por defecto
				INCWEAKPOINTERS
			}
			wPtr(const wPtr<T,array>& other):Pointer<T,array>(other.data),refCount(other.refCount){	//Constructor de copia
				if(this->refCount!=nullptr)
					this->refCount->weakCount++;
				INCWEAKPOINTERS
			}
			wPtr(const sPtr<T,array>& other):Pointer<T,array>(other.data),refCount(other.refCount){	//Constructor de copia(puntero fuerte)
				if(this->refCount!=nullptr)
					this->refCount->weakCount++;
				INCWEAKPOINTERS
			}
			void operator=(const wPtr<T,array>& other){												//Operador de copia
				if(this->refCount!=nullptr){
					if(--this->refCount->weakCount==0)
						delete refCount;
				}
				this->data=other.data;
				this->refCount=other.refCount;
				if(this->refCount!=nullptr)
					this->refCount->weakCount++;
			}
			void operator=(const sPtr<T,array>& other){												//Operador de copia(puntero fuerte)
				if(this->refCount!=nullptr){
					if(--this->refCount->weakCount==0)
						delete refCount;
				}
				this->data=other.data;
				this->refCount=other.refCount;
				if(this->refCount!=nullptr)
					this->refCount->weakCount++;
			}
			unsigned int currentOwners(){
				return this->refCount==nullptr? 0 : this->refCount->sharedCount;
			}
			sPtr<T,array> share(){
				if(not this->currentOwners())
					return sPtr<T,array>();
				else
					return sPtr<T,array>(*this);
			}
			~wPtr(){
				DECWEAKPOINTERS
				REMAININGWEAKPOINTERS
				if(this->refCount!=nullptr){
					if(--this->refCount->weakCount==0)
						delete refCount;
				}
			}
	};
	template<typename T,bool array=false>
	class uPtr:public Pointer<T,array>{
		public:
			uPtr(const uPtr&)=delete;
			void operator=(const uPtr&)=delete;
			uPtr():Pointer<T,array>(nullptr){														//Constructor por defecto
				INCUNIQUEPOINTERS
			}
			uPtr(T* dat):Pointer<T,array>(dat){														//Constructor de inicializacion
				INCUNIQUEPOINTERS
			}
			uPtr(uPtr&& other):Pointer<T,array>(other){												//Constructor de movimiento
				other.data=nullptr;
				INCUNIQUEPOINTERS
			}
			void operator=(T* dat){																	//Operador de asignacion
				if(array)
					delete[] this->data;
				else
					delete this->data;
				this->data=dat;
			}
			void operator=(uPtr&& other){															//Operador de movimiento
				if(array)
					delete[] this->data;
				else
					delete this->data;
				this->data=other.data;
				other.data=nullptr;
			}
			~uPtr(){
				DECUNIQUEPOINTERS
				REMAININGUNIQUEPOINTERS
				if(array)
					delete[] this->data;
				else
					delete this->data;
			}
	};
}