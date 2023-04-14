#pragma once
#include"../arrays.h"
namespace mpv{
	inline int strsize(const char* str){
		int i=0;
		while(str[i]){
			++i;
		}	
		return i;
	}
	inline void strcopy(char* dest,const char* source){
		int i=0;
		while(source[i]){
			dest[i]=source[i];
			i++;
		}
	}
	inline short strcomp(const char* str1,const char* str2){
		int sz1=strsize(str1);
		int sz2=strsize(str2);
		if(sz1>sz2)
			return 1;
		if(sz1<sz2)
			return -1;
		else{
			for(int i=0;i<sz1;i++){
				if(str1[i]>str2[i])
					return 1;
				if(str1[i]<str2[i])
					return -1;
			}
			return 0;
		}
	}
	template<short small_buffer_capacity>
	union sbo{
		char stack[small_buffer_capacity];
		char* heap;
	};
	template<short ss_cap=32>
	class Str{
		private:
			int size;
			sbo<ss_cap> text;
		public:
			char* get_stack(){
				return this->text.stack;
			}
			char* get_heap(){
				return this->text.heap;
			}
			char* get_text()const{	//devuelve el tipo que se esta usando actualmente en la union. !! NO se debe modificar size antes de ser llamada.
				if(this->size>=ss_cap)
					return this->text.heap;
				else
					return const_cast<char*>(this->text.stack);		
			}
			Str():size(0),text{'\0'}{INCSTRINGS}									//Constructor por defencto
			explicit Str(int sz):size(sz){											//Constructor por tamaño
				INCSTRINGS
				if(sz>=ss_cap)
					this->text.heap=new char[sz+1];
				this->get_text()[this->size]='\0';
			}
			Str(const Str& other):size(other.size){									//Constructor de copia
				INCSTRINGS
				if(other.size>=ss_cap){
					this->text.heap=new char[size+1];
					strcopy(this->text.heap,other.get_text());
				}
				else
					strcopy(this->text.stack,other.get_text());
				this->get_text()[this->size]='\0';
			}
			Str(const char* str):size(strsize(str)){								//Constructor con parametors
				INCSTRINGS
				if(strsize(str)>=ss_cap){
					this->text.heap=new char[size+1];
					strcopy(this->text.heap,str);
				}
				else
					strcopy(this->text.stack,str);
				this->get_text()[this->size]='\0';
			}
			Str(Str&& other):size(other.size){										//Constructor de movimiento
				INCSTRINGS
				if(other.size>=ss_cap){
					this->text.heap=other.get_text();
					this->text.heap[this->size]='\0';
				}
				else{
					strcopy(this->text.stack,other.get_text());
					this->text.stack[this->size]='\0';
				}
				other.text.heap=nullptr;
				other.size=0;
			}
			void operator=(const Str& other){										//Operador de copia
				if(this!=&other){
					if(this->size>=ss_cap)
						delete[] this->text.heap;
					this->size=other.size;
					if(other.size>=ss_cap){
						this->text.heap=new char[other.size+1];
						strcopy(this->text.heap,other.get_text());
						this->text.heap[this->size]='\0';				
					}
					else{
						strcopy(this->text.stack,other.get_text());
						this->text.stack[this->size]='\0';
					}	
				}
			}
			void operator=(const char* str){										//Operador de asignacion
				if(this->size>=ss_cap)
					delete[] this->text.heap;
				this->size=strsize(str);
				if(this->size>=ss_cap){
					this->text.heap=new char[this->size+1];			
					strcopy(this->text.heap,str);
					this->text.heap[this->size]='\0';
				}
				else{
					strcopy(this->text.stack,str);
					this->text.stack[this->size]='\0';
				}
			}
			void operator=(Str&& other){											//Operador de movimiento	
				if(this->size>=ss_cap)
					delete[] this->text.heap;
				this->size=other.size;
				if(other.size>=ss_cap){
					this->text.heap=other.text.heap;
					this->text.heap[this->size]='\0';
				}
				else{
					strcopy(this->text.stack,other.get_text());
					this->text.stack[this->size]='\0';
				}
				other.text.heap=nullptr;
				other.size=0;
			}
			Str operator+(const Str& other)const{
				Str new_string(this->size+other.size);//No se le suma 1 porque el constructor ya tiene en cuenta el espacio extra y el \0 del final
				char* new_text=new_string.get_text();
				strcopy(new_text,this->get_text());
				strcopy(new_text+this->size,other.get_text());
/* 				if(new_string.size>=ss_cap){
					strcopy(new_string.text.heap,this->get_text());
					strcopy(new_string.text.heap+this->size,other.get_text());//igual que: strcopy(&new_string.text.heap[this->size],other.get_text());
				}
				else{
					strcopy(new_string.text.stack,this->get_text());
					strcopy(new_string.text.stack+this->size,other.get_text());
				} */
				return new_string;
			}
			Str operator+(const char* str)const{
				Str new_string(this->size+strsize(str));//No se le suma 1 porque el constructor ya tiene en cuenta el espacio extra y el \0 del final
				char* new_text=new_string.get_text();
				strcopy(new_text,this->get_text());
				strcopy(new_text+this->size,str);
/* 				if(new_string.size>=ss_cap){
					strcopy(new_string.text.heap,this->get_text());
					strcopy(new_string.text.heap+this->size,str);//igual que: strcopy(&new_string.text.heap[this->size],other.get_text());
				}
				else{
					strcopy(new_string.text.stack,this->get_text());
					strcopy(new_string.text.stack+this->size,str);
				} */
				return new_string;
			}
			void operator+=(const Str& other){
				int new_size=this->size+other.size;
				char* this_text=this->get_text();//siempre get_text() antes de modificar el tamaño, por esta razon this->size se modifica en la ultima linea
				if(new_size>=ss_cap){
					char* new_text=new char[new_size+1];//puntero auxiliar porque si escribo sobre this->text->heap_str, al ser una union, puedo estar sobreescribiendo aux ya que este podria ser this->text.stack
					strcopy(new_text,this_text);
					strcopy(new_text+this->size,other.get_text());
					this->text.heap=new_text;
					this->text.heap[new_size]='\0';
				}
				else{
					strcopy(this->text.stack+this->size,other.get_text());
					this->text.stack[new_size]='\0';
				}
				if(this->size>=ss_cap)
					delete[] this_text;
				this->size=new_size;		
			}
			void operator+=(const char* str){
				int new_size=this->size+strsize(str);
				char* this_text=this->get_text();//siempre get_text() antes de modificar el tamaño, por esta razon this->size se modifica en la ultima linea
				if(new_size>=ss_cap){
					char* new_text=new char[new_size+1];//puntero auxiliar porque si escribo sobre this->text->heap_str, al ser una union, puedo estar sobreescribiendo aux ya que este podria ser this->text.stack
					strcopy(new_text,this_text);
					strcopy(new_text+this->size,str);
					this->text.heap=new_text;
					this->text.heap[new_size]='\0';
				}
				else{
					strcopy(this->text.stack+this->size,str);
					this->text.stack[new_size]='\0';
				}
				if(this->size>=ss_cap)
					delete[] this_text;
				this->size=new_size;		
			}
			void operator+=(char chr){
				int new_size=this->size+1;
				char* this_text=this->get_text();//siempre get_text() antes de modificar el tamaño, por esta razon this->size se modifica en la ultima linea
				if(new_size>=ss_cap){
					char* new_text=new char[new_size+1];//puntero auxiliar porque si escribo sobre this->text->heap_str, al ser una union, puedo estar sobreescribiendo aux ya que este podria ser this->text.stack
					strcopy(new_text,this_text);
					new_text[this->size]=chr;
					this->text.heap=new_text;
					this->text.heap[new_size]='\0';
				}
				else{
					this->text.stack[this->size]=chr;
					this->text.stack[new_size]='\0';
				}
				if(this->size>=ss_cap)
					delete[] this_text;
				this->size++;		
			}
			Str operator*(unsigned int num)const{
				if(num){
					Str new_string(this->size*num);
					char* new_text=new_string.get_text();
					char* this_text=this->get_text();
					for(int index=0;index<new_string.size;index+=this->size)
						strcopy(new_text+index,this_text);
					return new_string;
				}
				else{
					Str new_string;
					return new_string;
				}
			}
			void operator*=(unsigned int num){
				if(num){
					int new_size=this->size*num;
					char* this_text=this->get_text();
					if(new_size>=ss_cap){
						char* new_text=new char[new_size+1];
						for(int index=0;index<new_size;index+=this->size)
							strcopy(new_text+index,this_text);
						this->text.heap=new_text;
						this->text.heap[new_size]='\0';
					}
					else{
						for(int index=this->size;index<new_size;index+=this->size)
							memcopy(this->text.stack+index,this_text,this->size);
						this->text.stack[new_size]='\0';
					}
					if(this->size>=ss_cap)
						delete[] this_text;
					this->size=new_size;
				}
				else{
					if(this->size>=ss_cap)
						delete[] this->text.heap;
					this->size=0;
					this->text.stack[0]='\0';
				}
			}
			void operator%(Str& other){
				sbo<ss_cap> string_aux=this->text;
				int size_aux=this->size;
				this->text=other.text;
				this->size=other.size;
				other.text=string_aux;
				other.size=size_aux;
			}
			bool operator==(const Str& other)const{
				return not strcomp(this->get_text(),other.get_text());
			}
			bool operator!=(const Str& other)const{
				return strcomp(this->get_text(),other.get_text());
			}
			bool operator>(const Str& other)const{
				return strcomp(this->get_text(),other.get_text())==1;
			}
			bool operator<(const Str& other)const{
				return strcomp(this->get_text(),other.get_text())==-1;
			}
			bool operator>=(const Str& other)const{
				return strcomp(this->get_text(),other.get_text())>=0 ;
			}
			bool operator<=(const Str& other)const{
				return strcomp(this->get_text(),other.get_text())<=0 ;
			}
			short cmp(const Str& other)const{
				return strcomp(this->get_text(),other.get_text());
			}
			char& operator[](int index)const{
				if(index>=0)
					return this->get_text()[index];
				else
					return this->get_text()[size+index];
			}
			void insert(unsigned int index,const Str& other){
				char* this_text=this->get_text();
				int new_size=this->size+other.size;
				if(new_size>=ss_cap){
					char* new_text=new char[new_size+1];
					memcopy(new_text,this_text,index);
					strcopy(new_text+index,other.get_text());
					strcopy(new_text+index+other.size,this_text+index);
					this->text.heap=new_text;
					this->text.heap[new_size]='\0';
				}
				else{
					char* insert_position=this->text.stack+index;
					int end_sz=this->size-index;
					memcopy(insert_position+other.size,insert_position,end_sz);
					strcopy(insert_position,other.get_text());
					this->text.stack[new_size]='\0';
				}
				if(this->size>=ss_cap)
					delete[] this_text;
				this->size=new_size;
			}
			void insert(unsigned int index,const char* str){
				char* this_text=this->get_text();
				int str_sz=strsize(str);
				int new_size=this->size+str_sz;
				if(new_size>=ss_cap){
					char* new_text=new char[new_size+1];
					memcopy(new_text,this_text,index);
					strcopy(new_text+index,str);
					strcopy(new_text+index+str_sz,this_text+index);
					this->text.heap=new_text;
					this->text.heap[new_size]='\0';
				}
				else{
					char* insert_position=this->text.stack+index;
					int end_sz=this->size-index;
					memcopy(insert_position+str_sz,insert_position,end_sz);
					strcopy(insert_position,str);
					this->text.stack[new_size]='\0';
				}
				if(this->size>=ss_cap)
					delete[] this_text;
				this->size=new_size;
			}
			void erase(int start,int end){
				int new_size=this->size-(end-start);
				char* this_text=this->get_text();
				if(new_size>=ss_cap){
					char* new_text=new char[new_size+1];
					memcopy(new_text,this_text,start);
					strcopy(new_text+start,this_text+end);
					new_text[new_size]='\0';
					this->text.heap=new_text;
				}
				else{
					if(this->size>=ss_cap)
						memcopy(this->text.stack,this_text,start);
					strcopy(this->text.stack+start,this_text+end);
					this->text.stack[new_size]='\0';
				}
				if(this->size>=ss_cap)
					delete[] this_text;
				this->size=new_size;
			}
			void remove(const Str& substring,int start=0,int end=-1){
				int index=this->find(substring,start,end);
				if(index>=0){
					this->erase(index,index+substring.size);	
				}
			}
			void rremove(const Str& substring,int start=0,int end=-1){
				int index=this->rfind(substring,start,end);
				if(index>=0){
					this->erase(index,index+substring.size);	
				}
			}
		 	void replace(const Str& substring1,const Str& substring2,int max_count=-1){
				int	count=this->count(substring1);
				if(count>max_count and max_count>=0)
					count=max_count;
				if(not count)
					return;				
				int array[count]={};
				for(int i=0,last=0;i<count;last=array[i++]+1)
					array[i]=this->find(substring1,array[i]+last);
				for(int i=0;i<count;i++)
					array[i]=array[i]+(substring2.size-substring1.size)*i;
 				char* this_text=this->get_text();
				int new_size=this->size+(count*substring2.size-count*substring1.size);
				char* substring2_text=substring2.get_text();//Para no andar llamando a get_text() todo el tiempo
				if(new_size>=ss_cap){
					char* new_string=new char[new_size+1];
					for(int i=0,j=0,k=0;i<new_size;){
						if(i==array[k]){
							strcopy(new_string+array[k++],substring2_text);
							i+=substring2.size;
							j+=substring1.size;
						}
						else{
							new_string[i]=this_text[j];
							i++;
							j++;
						}
					}
					this->text.heap=new_string;
					this->text.heap[new_size]='\0';
				}
				else{
					char aux[this->size+1];
					memcopy(aux,this_text,this->size+1);
					for(int i=array[0],j=array[0],k=0;i<new_size;){
						if(i==array[k]){
							strcopy(this->text.stack+array[k++],substring2_text);
							i+=substring2.size;
							j+=substring1.size;
						}
						else{
							this->text.stack[i]=aux[j];
							i++;
							j++;
						}
					}
					this->text.stack[new_size]='\0';
				}
				if(this->size>=ss_cap)
					delete[] this_text;
				this->size=new_size;
			}
			Str substr(int start,int end=-1)const{
				if(end<0)
					end=this->size;
				Str new_string(end-start);//el tamaño del nuevo string lo genera el constructor
				memcopy(new_string.get_text(),this->get_text()+start,new_string.size);
				return new_string;
			}
			Str extract(int index,int pos=-1)const{
				if(pos<0)
					pos=this->size-index;
				Str new_string(pos);//el tamaño del nuevo string lo genera el constructor
				memcopy(new_string.get_text(),this->get_text()+index,pos);
				return new_string;
			}
			void noExtraSpaces(){
				char* this_text=this->get_text();
				int new_size=0;//new_size empieza siendo un contador
				for(int i=0;i<this->size;i++)
					if(this_text[i]==' ' and this_text[i+1]==' ')
						new_size++;
				new_size=this->size-new_size;
				if(new_size>=ss_cap){
					char* new_text=new char[new_size+1];
					for(int i=0,j=0;i<this->size;i++){
						if(not(this_text[i]==' ' and this_text[i+1]==' ')){
							new_text[j]=this_text[i];
							j++;
						}
					}
					this->text.heap=new_text;
					this->text.heap[new_size]='\0';
				}
				else{
					char aux_cpy[this->size+1];
					memcopy(aux_cpy,this_text,this->size+1);
					for(int i=0,j=0;i<this->size;i++){
						if(not(this_text[i]==' ' and this_text[i+1]==' ')){
							this->text.stack[j]=this_text[i];
							j++;
						}
					}
					this->text.stack[new_size]='\0';		
				}
				if(this->size>=ss_cap)
					delete[] this_text;
				this->size=new_size;
			}
 			void lstrip(){
				char* this_text=this->get_text();
				if(this_text[0]!=' ')
					return;
				int count=0;
				while(this_text[count]==' ')
					count++;
				int new_size=this->size-count;
				if(new_size>=ss_cap){
					char* new_text=new char[new_size+1];
					for(int i=0;count<=this->size;i++,count++)//<= para que copie el \0
						new_text[i]=this_text[count];
					this->text.heap=new_text;
				}
				else
					for(int i=0;count<=this->size;i++,count++)
						this->text.stack[i]=this_text[count];
				if(this->size>=ss_cap)
					delete[] this_text;
				this->size=new_size;
			}
 			void rstrip(){
				char* this_text=this->get_text();
				if(this_text[this->size-1]!=' ')
					return;
				int count=this->size-1;
				while(this_text[count]==' ')
					count--;
				int new_size=count+1;
				if(new_size>=ss_cap){
					char* new_text=new char[new_size+1];
					for(count=0;count<new_size;count++)//reciclo count
						new_text[count]=this_text[count];
					new_text[new_size]='\0';
					this->text.heap=new_text;
					if(this->size>=ss_cap)
						delete[] this_text;					
				}
				else{
					if(this->size>=ss_cap){
						for(count=0;count<new_size;count++)//reciclo count
							this->text.stack[count]=this_text[count];
						delete[] this_text;
					}
					this->text.stack[new_size]='\0';
				}
				this->size=new_size;				
			}
			void strip(){
				char* this_text=this->get_text();
				if(this_text[0]=='\0' and this_text[this->size-1]=='\0')
					return;
				int lcount=0,rcount=this->size-1;
				while(this_text[lcount]==' ')
					lcount++;
				while(this_text[rcount]==' ')
					rcount--;
				int new_size=rcount+1-lcount;
				if(new_size>=ss_cap){
					char* new_text=new char[new_size+1];
					for(rcount=0;rcount<new_size;lcount++,rcount++)//reciclo rcount
						new_text[rcount]=this_text[lcount];
					new_text[new_size]='\0';
					this->text.heap=new_text;
				}
				else{
					for(rcount=0;rcount<new_size;lcount++,rcount++)//reciclo rcount
						this->text.stack[rcount]=this_text[lcount];
					this->text.stack[new_size]='\0';
				}
				if(this->size>=ss_cap)
					delete[] this_text;
				this->size=new_size;
			}
			void upper(){
				if(this->size>=ss_cap){
					for(int i=0;i<size;i++)
						if(this->text.heap[i]>=97 and this->text.heap[i]<=122)
							this->text.heap[i]-=32;
				}
				else{
					for(int i=0;i<size;i++)
						if(this->text.stack[i]>=97 and this->text.stack[i]<=122)
							this->text.stack[i]-=32;
				}
			}
			void lower(){
				if(this->size>=ss_cap){
					for(int i=0;i<size;i++)
						if(this->text.heap[i]>=65 and this->text.heap[i]<=90)
							this->text.heap[i]+=32;
				}
				else{
					for(int i=0;i<size;i++)
						if(this->text.stack[i]>=65 and this->text.stack[i]<=90)
							this->text.stack[i]+=32;
				}
			}
			Str noExtraSpaces_cpy()const{
				char* this_text=this->get_text();
				int count=0;
				for(int i=0;i<this->size;i++)
					if(this_text[i]==' ' and this_text[i+1]==' ')
						count++;
				Str new_string(this->size-count);
				char* new_text=new_string.get_text();
				for(int i=0,j=0;i<this->size;i++){
					if(not(this_text[i]==' ' and this_text[i+1]==' ')){
						new_text[j]=this_text[i];
						j++;
					}
				}
				new_text[new_string.size]='\0';
				return new_string;
			}
 			Str lstrip_cpy()const{
				char* this_text=this->get_text();
				int count=0;
				while(this_text[count]==' ')
					count++;
				Str new_string(this->size-count);
				char* new_text=new_string.get_text();
				for(int i=0;count<=this->size;i++,count++)//<= para que copie el \0
					new_text[i]=this_text[count];
				return new_string;
			}
 			Str rstrip_cpy()const{
				char* this_text=this->get_text();
				int count=this->size-1;
				while(this_text[count]==' ')
					count--;
				Str new_string(count+1);
				char* new_text=new_string.get_text();
				for(count=0;count<new_string.size;count++)//reciclo count
					new_text[count]=this_text[count];
				new_text[new_string.size]='\0';
				return new_string;
			}
			Str strip_cpy()const{
				char* this_text=this->get_text();
				int lcount=0,rcount=this->size-1;
				while(this_text[lcount]==' ')
					lcount++;
				while(this_text[rcount]==' ')
					rcount--;
				Str new_string(rcount+1-lcount);
				char* new_text=new_string.get_text();
				for(rcount=0;rcount<new_string.size;lcount++,rcount++)//reciclo rcount
					new_text[rcount]=this_text[lcount];
				new_text[new_string.size]='\0';
				return new_string;
			}
			Str upper_cpy()const{
				Str new_string(this->size);
				if(this->size>=ss_cap)
					for(int i=0;i<size;i++)
						new_string[i]=this->text.heap[i]>=97 and this->text.heap[i]<=122 ? this->text.heap[i]-32:this->text.heap[i];
				else
					for(int i=0;i<size;i++)
						new_string[i]=this->text.stack[i]>=97 and this->text.stack[i]<=122 ? this->text.stack[i]-32:this->text.stack[i];
				return new_string;
			}
			Str lower_cpy()const{
				Str new_string(this->size);
				if(this->size>=ss_cap)
					for(int i=0;i<size;i++)
						new_string[i]=this->text.heap[i]>=65 and this->text.heap[i]<=90 ? this->text.heap[i]+32:this->text.heap[i];
				else
					for(int i=0;i<size;i++)
						new_string[i]=this->text.stack[i]>=65 and this->text.stack[i]<=90 ? this->text.stack[i]+32:this->text.stack[i];
				return new_string;
			}
			int find(const Str& substring,int start=0,int end=-1)const{
				if(end==-1)
					end=this->size;
				char* substring_text=substring.get_text(),* this_text=this->get_text();
				for(int i=start;i<=this->size-substring.size and i<=end-substring.size;i++)
					if(not memcomp(substring_text,this_text+i,substring.size))
						return i;
				return -1;
			}
			int rfind(const Str& substring,int start=0,int end=-1)const{
				if(end==-1)
					end=this->size;
				char* substring_text=substring.get_text(),* this_text=this->get_text();
				int last_found=-1;
				for(int i=start;i<=this->size-substring.size and i<=end-substring.size;i++)
					if(not memcomp(substring_text,this_text+i,substring.size))
						last_found=i;
				return last_found;
			}
			int count(const Str& substring,int start=0,int end=-1)const{
				if(end==-1)
					end=this->size;
				char* substring_text=substring.get_text(),* this_text=this->get_text();
				int counter=0;
				while(start<=this->size-substring.size and start<=end-substring.size){
					if(not memcomp(substring_text,this_text+start,substring.size)){
						counter++;
						start+=substring.size;
					}
					else start++;
				}
				return counter;
			}
			int len()const{
				return this->size;
			}
			bool empty()const{
				return not this->size;
			}
			bool endswith(const Str& substring)const{
				return not strcomp(this->text+this->size-substring.size,substring.text);
			}
			bool startswith(const Str& substring)const{
				return not memcomp(this->get_text(),substring.get_text(),substring.size);
			}
			void print(){
				puts(this->get_text());
			}
			~Str(){
				DECSTRINGS
				REMAININGSTRINGS
				if(this->size>=ss_cap)
					delete[] this->text.heap;
			}
			class iterator{
				private:
					char* ptr;
				public:
					iterator(char* ptr):ptr(ptr){}
					char& operator*(){
						return *ptr;
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
				return &this->get_text()[0];
			}
			iterator end()const{
				return &this->get_text()[len()];
			}
			iterator rbegin()const{
				return &this->get_text()[len()-1];
			}
			iterator rend()const{
				return &this->get_text()[-1];
			}
	};
	template<short cap>
	std::ostream& operator<<(std::ostream& stream,const Str<cap>& string){
			stream<<string.get_text();
		return stream;
	}
	template<short cap>
	std::istream& operator>>(std::istream& stream,Str<cap>& string){
		string="";
		char c;
		while(stream.get(c)){
			if(c=='\n')
				break;
		string+=c;
		}
		return stream;
	}
}