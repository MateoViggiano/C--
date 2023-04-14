//#include<iostream>
#include"viggianolib/viggiano.h"
#define NEG 1
#define POS 0
template<uint64_t B>
bool isEqual(const mpv::AList<uint64_t>& a,const mpv::AList<uint64_t>& b){
	if(a.len()!=b.len())
		return false;
	else{
		for(mpv::AList<uint64_t>::iterator i=a.rbegin(),j=b.rbegin();i!=a.rend();i--,j--){
			if(*i!=*j)
				return false;
		}
		return true;
	}

}
template<uint64_t B>
bool isBigger(const mpv::AList<uint64_t>& a,const mpv::AList<uint64_t>& b){
	if(a.len()>b.len())
		return true;
	else if(a.len()<b.len())
		return false;
	else{
		for(mpv::AList<uint64_t>::iterator i=a.rbegin(),j=b.rbegin();i!=a.rend();i--,j--){
			if(*i>*j)
				return true;
			else if(*i<*j)
				return false;
		}
		return false;
	}

}
template<uint64_t B>
bool isSmaller(const mpv::AList<uint64_t>& a,const mpv::AList<uint64_t>& b){
	if(a.len()<b.len())
		return true;
	else if(a.len()>b.len())
		return false;
	else{
		for(mpv::AList<uint64_t>::iterator i=a.rbegin(),j=b.rbegin();i!=a.rend();i--,j--){
			if(*i<*j)
				return true;
			else if(*i>*j)
				return false;
		}
		return false;
	}
}
template<uint64_t B>
bool isBigger_eq(const mpv::AList<uint64_t>& a,const mpv::AList<uint64_t>& b){
	if(a.len()>b.len())
		return true;
	else if(a.len()<b.len())
		return false;
	else{
		for(mpv::AList<uint64_t>::iterator i=a.rbegin(),j=b.rbegin();i!=a.rend();i--,j--){
			if(*i>*j)
				return true;
			else if(*i<*j)
				return false;
		}
		return true;
	}

}
template<uint64_t B>
bool isSmaller_eq(const mpv::AList<uint64_t>& a,const mpv::AList<uint64_t>& b){
	if(a.len()<b.len())
		return true;
	else if(a.len()>b.len())
		return false;
	else{
		for(mpv::AList<uint64_t>::iterator i=a.rbegin(),j=b.rbegin();i!=a.rend();i--,j--){
			if(*i<*j)
				return true;
			else if(*i>*j)
				return false;
		}
		return true;
	}
}
template<uint64_t B>
mpv::AList<uint64_t> add(const mpv::AList<uint64_t>& a,const mpv::AList<uint64_t>& b){
	uint64_t digit;
	bool carry=0;
	mpv::AList<uint64_t> res;
	mpv::AList<uint64_t>::iterator i=a.begin(),j=b.begin();
	for(;i!=a.end() and j!=b.end();i++,j++){
		digit=(*i+*j+carry)%B;
		carry=(*i+*j+carry)/B;
		res.append(digit);
	}
	while(i!=a.end()){
		digit=(*i+carry)%B;
		carry=(*i+carry)/B;
		res.append(digit);
		i++;
	}
	while(j!=b.end()){
		digit=(*j+carry)%B;
		carry=(*j+carry)/B;
		res.append(digit);
		j++;
	}
	if(carry)
		res.append(1);
	return res;
}
template<uint64_t B>
mpv::AList<uint64_t> sub(const mpv::AList<uint64_t>& a,const mpv::AList<uint64_t>& b){// a debe ser mayor a b(ni menor ni igual)
	uint64_t digit;
	bool borrow=0;
	mpv::AList<uint64_t> res;
	mpv::AList<uint64_t>::iterator i=a.begin(),j=b.begin();
	for(;j!=b.end();i++,j++){
		if(*i>=*j+borrow){//	*i-borrow>=*j  no funcionaria porque se estan usando enteros sin signo y si i fuese 0 generaria un overflow
			digit=*i-borrow-*j;//Esta resta es segura, no puede dar negativo
			borrow=0;
		}
		else{
			digit=*i+B-borrow-*j;//segura
			borrow=1;
		}
		res.append(digit);
	}
	while(i!=a.end()){
		if(*i>=borrow){//	*i-borrow>=0  tambien podria generar un overflow
			digit=*i-borrow;//segura
			borrow=0;
		}
		else{
			digit=*i+B-borrow;//segura
			borrow=1;
		}
		res.append(digit);
		i++;
	}
	while(res[-1]==0 and res.len()>1)
		res.del(-1);
	return res;
}
template<uint64_t B>
void inc(mpv::AList<uint64_t>& a){
	bool carry=1;
	for(mpv::AList<uint64_t>::iterator i=a.begin();i!=a.end() and carry==1;i++){
		*i+=carry;
		if(*i/B==0)
			carry=0;
		else
			*i=0;
	}
	if(carry)
		a.append(1);
}
template<uint64_t B>
void dec(mpv::AList<uint64_t>& a){
	bool borrow=1;
	for(mpv::AList<uint64_t>::iterator i=a.begin();i!=a.end() and borrow==1;i++){
		*i-=borrow;
		if(*i>=0){
			borrow=0;
		}
		else{
			*i+=B;
		}
	}
	if(a[-1]==0 and a.len()!=1)
		a.del(-1);
}
template<uint64_t B>
mpv::AList<uint64_t> mul(mpv::AList<uint64_t> a,mpv::AList<uint64_t> b){
	uint64_t digit, carry=0;
	int k=0;
	mpv::AList<uint64_t> res,aux;
	res.append(0);
	mpv::AList<uint64_t>::iterator i=a.begin(),j=b.begin();
	for(auto i:b){
		aux.clear();
		int K=k;
		while(K--){
			aux.append(0);
		}
		for(auto j:a){
			digit=((i*j)+carry)%B;
			carry=((i*j)+carry)/B;
			aux.append(digit);
		}
		if(carry){
			aux.append(carry);
			carry=0;
		}
		res=add<B>(aux,res);
		k++;
	}
	return res;
}

template<uint64_t B>
mpv::AList<uint64_t> Kmul(mpv::AList<uint64_t> a,mpv::AList<uint64_t> c){
	unsigned int size=a.len()>c.len()? a.len():c.len();
	if(size==1){
		mpv::AList<uint64_t> res;
		uint64_t digit=(a[0]*c[0])%B;
		uint64_t carry=(a[0]*c[0])/B;
		if(digit and carry){
			res.append(digit);
			res.append(carry);
		}
		else if(carry){
			res.append(0);
			res.append(carry);
		}
		else
			res.append(digit);
		return res;
	}
	else{
		
		while(a.len()<size)
			a.append(0);
		while(c.len()<size)
			c.append(0);
		mpv::AList<uint64_t> b=a.cut(0,size/2),d=c.cut(0,size/2);
		mpv::AList<uint64_t> ac=Kmul<B>(a,c),bd=Kmul<B>(b,d),ad_bc=sub<B>(sub<B>(Kmul<B>(add<B>(a,b),add<B>(c,d)),bd),ac);

		for(int i=0;i<size/2;i++){
			ad_bc.insert(0,0);
		}
/*		while(bd.len()<size)
			bd.append(0);
		bd+=ac;*/
		for(int i=0;i<b.len()*2;i++){
			ac.insert(0,0);
		}
		//cout<<"\na=";a.println(true);
		//cout<<"b=";b.println(true);
		//cout<<"c=";c.println(true);
		//cout<<"d=";d.println(true);
		//cout<<"ac=";ac.println(true);
		//cout<<"bd=";bd.println(true);
		//cout<<"ad_bc=";ad_bc.println(true);
		bd=add<B>(ac,bd);
		//cout<<"ac_bd=";bd.println(true);
		

		mpv::AList<uint64_t> res=add<B>(bd,ad_bc);
		while(res[-1]==0 and res.len()>1)
			res.del(-1);
		//cout<<"res=";res.println(true);cout<<endl;
		return res;
	}
}

//template<uint64_t B>
//mpv::AList<uint64_t> div(const mpv::AList<uint64_t>& a,const mpv::AList<uint64_t>& b){using namespace std;
//	mpv::AList<uint64_t> res(0),acum(b);
//	//acum=add<B>(acum,b);
//	while(isSmaller_eq<B>(acum,a)){
//		acum=add<B>(acum,b);//cout<<"acumulador: "<<acum<<endl;
//		inc<B>(res);//cout<<"contador: "<<res<<endl;
//	}
//	return res;
//}
template<uint64_t B>
mpv::AList<uint64_t> div(const mpv::AList<uint64_t>& a,const mpv::AList<uint64_t>& b){//using namespace std;
	mpv::AList<uint64_t> res(0),acum(a);
	//acum=add<B>(acum,b);
	while(isBigger_eq<B>(acum,b)){
		acum=sub<B>(acum,b);//cout<<"acumulador: ";acum.println(true);
		inc<B>(res);//cout<<"contador: ";res.println(true);
	}
	return res;
}
template<uint64_t base=1073741824>
class Int{
	public:
		mpv::AList<uint64_t> list;
		bool sign;
	public:
		Int(long long n):sign(POS){
			if(n<0){
				n*=-1;
				sign=NEG;
			}
			do{
				list.append(n%base);
				n/=base;
			}while(n!=0);
		} 
		Int():sign(POS){}
		Int operator+(const Int& other)const{
			Int new_Int;
			if(this->sign==other.sign){
				new_Int.sign=this->sign;
				new_Int.list=add<base>(this->list,other.list);
			}
			else if(isBigger<base>(this->list,other.list)){
				new_Int.sign=this->sign;
				new_Int.list=sub<base>(this->list,other.list);
			}
			else if(isSmaller<base>(this->list,other.list)){
				new_Int.sign=other.sign;
				new_Int.list=sub<base>(other.list,this->list);
			}
			else
				new_Int.list.append(0);
			return new_Int;
		}
		void operator+=(const Int& other){
			if(this->sign==other.sign){
				this->list=add<base>(this->list,other.list);
			}
			else if(isBigger<base>(this->list,other.list)){
				this->list=sub<base>(this->list,other.list);
			}
			else if(isSmaller<base>(this->list,other.list)){
				this->sign=other.sign;
				this->list=sub<base>(other.list,this->list);
			}
			else{
				this->list.clear();
				this->list.append(0);
			}
		}
		Int& operator++(){
			if(this->sign==POS)
				inc<base>(this->list);
			else if(this->sign==NEG and this->list.len()==1 and this->list[0]==1){
				this->list[0]=0;
				this->sign=POS;
			}
			else
				dec<base>(this->list);
			return *this;
		}
		Int operator++(int){
			Int aux=*this;
			if(this->sign==POS)
				inc<base>(this->list);
			else if(this->sign==NEG and this->list.len()==1 and this->list[0]==1){
				this->list[0]=0;
				this->sign=POS;
			}
			else
				dec<base>(this->list);
			return aux;
		}
		Int& operator+(){
			return *this;
		}
		Int operator-(const Int& other){
			Int new_Int;
			if(this->sign!=other.sign){
				new_Int.sign=this->sign;
				new_Int.list=add<base>(this->list,other.list);
			}
			else if(isBigger<base>(this->list,other.list)){
				new_Int.sign=this->sign;
				new_Int.list=sub<base>(this->list,other.list);
			}
			else if(isSmaller<base>(this->list,other.list)){
				new_Int.sign=not this->sign;
				new_Int.list=sub<base>(other.list,this->list);
			}
			else
				new_Int.list.append(0);
			return new_Int;
		}
		void operator-=(const Int& other){
			if(this->sign!=other.sign){
				this->list=add<base>(this->list,other.list);
			}
			else if(isBigger<base>(this->list,other.list)){
				this->list=sub<base>(this->list,other.list);
			}
			else if(isSmaller<base>(this->list,other.list)){
				this->sign=not this->sign;
				this->list=sub<base>(other.list,this->list);
			}
			else{
				this->list.clear();
				this->list.append(0);
			}
		}
		Int& operator--(){
			if(this->sign==POS and this->list.len()==1 and this->list[0]==0){
				this->list[0]=1;
				this->sign=NEG;
			}
			else if(this->sign==POS)
				dec<base>(this->list);
			else
				inc<base>(this->list);
			return *this;
		}
		Int operator--(int){	//Deberia retornar un rvalue(no lo hace)
			Int aux=*this;
			if(this->sign==POS and this->list.len()==1 and this->list[0]==0){
				this->list[0]=1;
				this->sign=NEG;
			}
			else if(this->sign==POS)
				dec<base>(this->list);
			else
				inc<base>(this->list);
			return aux;
		}
		Int& operator-(){
			if(not(this->list.len()==1 and this->list[0]==0))
				this->sign=not this->sign;
			return *this;
		}
		Int operator*(const Int& other)const{
			Int new_Int;
			if(this->list.len()==1 and this->list[0]==0 or other.list.len()==1 and other.list[0]==0)
				new_Int.list.append(0);
			else{
				if(this->sign!=other.sign)
					new_Int.sign=NEG;
				new_Int.list=mul<base>(this->list,other.list);
			}
			return new_Int;
		}
		void operator*=(const Int& other){
			if(this->list.len()==1 and this->list[0]==0 or other.list.len()==1 and other.list[0]==0){
				this->list.clear();
				this->list.append(0);
				this->sign=POS;
			}
			else{
				if(this->sign!=other.sign)
					this->sign=NEG;
				else
					this->sign=POS;
				this->list=mul<base>(this->list,other.list);
			}
		}
		Int operator/(const Int& other)const{
			if(other.list.len()==1 and other.list[0]==0){
				return 0;
			}
			Int new_Int;
			if(this->list.len()==1 and this->list[0]==0)
				new_Int.list.append(0);
			else if(this->sign!=other.sign)
				new_Int.sign=NEG;
			new_Int.list=div<base>(this->list,other.list);
			return new_Int;
		}
		void operator/=(const Int& other){
			if(other.list.len()==1 and other.list[0]==0){
				return;
			}
			if(this->list.len()==1 and this->list[0]==0){
				this->list.clear();
				this->list.append(0);
				this->sign=POS;
			}
			else if(this->sign!=other.sign)
				this->sign=NEG;
			else
				this->sign=POS;
			this->list=div<base>(this->list,other.list);
		}
		//#define POW
		#ifndef POW
		Int operator^(const Int& other)const{
			if(other.sign==NEG)
				return 0;
			Int new_Int=1;
			// if(this->sign==POS)
			// 	new_Int.sign=NEG;
			// else if(this->sign==NEG and other.even())
			// 	new_Int.sign=POS;
			// else 
			// 	new_Int.sign=NEG;
			for(Int i=0;i<other;i++)
				new_Int*=*this;
			return new_Int;
		}
		#else
		struct lookup{
			uint64_t cont;
			Int num;
			lookup(uint64_t cont,Int num):cont(cont),num(num){}
			lookup():cont(0),num(0){}
		};
		Int operator^(const Int& other)const{
			if(other.sign==NEG)
				return 0;
			Int acum=0;
			mpv::AList<lookup> list;
			list.append(lookup(1,*this));
			while((Int)list[-1].cont<=other){
				list.append(lookup(list[-1].cont*2,list[-1].num*list[-1].num));
			}
			Int new_Int=1;
			for(auto i=list.rbegin();i!=list.rend() and acum!=other;i--){
				if(acum+i->cont<=other){
					acum+=i->cont;
					new_Int*=i->num;
				}
			}
			return new_Int;
		}
		#endif
		bool operator==(const Int& other)const{
			if(this->sign!=other.sign)
				return false;
			else return isEqual<base>(this->list,other.list);
		}
		bool operator!=(const Int& other)const{
			if(this->sign!=other.sign)
				return true;
			else return not isEqual<base>(this->list,other.list);
		}
		bool operator>=(const Int& other)const{
			if(this->sign==POS and other.sign==NEG)
				return true;
			else if(this->sign==NEG and other.sign==POS)
				return false;
			else if(this->sign==POS and other.sign==POS)
				return isBigger_eq<base>(this->list,other.list);
			else 
				return isSmaller_eq<base>(this->list,other.list);
		}
		bool operator>(const Int& other)const{
			if(this->sign==POS and other.sign==NEG)
				return true;
			else if(this->sign==NEG and other.sign==POS)
				return false;
			else if(this->sign==POS and other.sign==POS)
				return isBigger<base>(this->list,other.list);
			else 
				return isSmaller<base>(this->list,other.list);
		}
		bool operator<=(const Int& other)const{
			if(this->sign==POS and other.sign==NEG)
				return false;
			else if(this->sign==NEG and other.sign==POS)
				return true;
			else if(this->sign==POS and other.sign==POS)
				return isSmaller_eq<base>(this->list,other.list);
			else
				return isBigger_eq<base>(this->list,other.list);	
		}
		bool operator<(const Int& other)const{
			if(this->sign==POS and other.sign==NEG)
				return false;
			else if(this->sign==NEG and other.sign==POS)
				return true;
			else if(this->sign==POS and other.sign==POS)
				return isSmaller<base>(this->list,other.list);
			else
				return isBigger<base>(this->list,other.list);	
		}
		bool even()const{			//solo funciona si la base es par
			return this->list[0]%2==0;
		}
		bool odd()const{			//solo funciona si la base es par
			return this->list[0]%2==1;
		}
		template<uint64_t b>
		friend std::ostream& operator<<(std::ostream& stream,Int<b> n);
};
#define Y 1
#if Y==0
template<uint64_t b>
std::ostream& operator<<(std::ostream& stream,Int<b> n){
	if(n.sign==NEG)
		stream<<'-';
	for(int i=n.list.len()-1;i>=0;i--){
		stream<<(uint64_t)n.list[i];
	}
	return stream;
}
#else

template<uint64_t b>
std::ostream& operator<<(std::ostream& stream,Int<b> n){
	if(n.sign==NEG)
		stream<<'-';
	mpv::AList<uint64_t> lista;
	Int<10> B=b;
	Int<10> x;
	Int<10> j=0;
	for(auto i:n.list){
		x+=Int<10>(i)*(B^(j++));
	}
	for(mpv::AList<uint64_t>::iterator i=x.list.rbegin();i!=x.list.rend();i--){
		stream<<*i;
	}
	return stream;
}
#endif
using namespace std;
using namespace mpv;
#include<math.h>
#define Z 0
#if Z==0
/*
	La basae de en la que se almacenan los enteros de Python es 2^30
	((2^30)^3)-1 es el maximo numero que se puede almacenar en un entero de 64 bits
*/
int main(){
	Int<> a=43563473,b=93;
	Int<> c=a^b;
	cout<<c;
}
#elif Z==1

int main(){
	//long long A=682465345,B=3567;
	long long A=3655434643,B=44343345;
	Int<> a(A),b(B);
	cout<<"a==b -> "<<(a==b)<<endl;
	cout<<"a!=b -> "<<(a!=b)<<endl;
	cout<<"a<=b -> "<<(a<=b)<<endl;
	cout<<"a>=b -> "<<(a>=b)<<endl;
	cout<<"a<b -> "<<(a<b)<<endl;
	cout<<"a>b -> "<<(a>b)<<endl;
}
#else
int main(){
	bool prev=0;

	for(Int<19> i=0;true;i++){
		if(prev==1 and i.even()==1)
			return -1;
		prev=i.even();
		cout<<i<<"-->"<<i.even()<<endl;
	}
}
#endif