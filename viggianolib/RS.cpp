#include"viggiano.h"
#include<memory>
#include<vector>
using namespace vgg;
using namespace std;
class obj{
	public:
		inline static unsigned long long remaining;
		shared_ptr<obj> next;
		obj():next(nullptr){
			cout<<"created object, remaining:"<<++remaining<<endl;	
		}
		~obj(){
			cout<<"destroyed object, remaining:"<<--remaining<<endl;
		}
		void set_next(shared_ptr<obj> next){
			this->next=next;
		}
};

#define MAIN 2
#if MAIN==0
int main(){
	sPtr<List<int>,1> sp1(new List<int>[10]{{6,2,4,5},{4,62,4},2,{52,6,24,5,1},52,-42,{5,2,62,4},{0,5,-243,4},43,{-54,90}});
	wPtr<List<int>,1> wp1=sp1;
	for range(i,10){
		wp1.share()[i].println();
	}
	wp1=nullptr;
	cout<<endl<<"Current owners:"<<wp1.share().currentOwners()<<endl;
	sp1=nullptr;
	sPtr<List<int>,1> sp2=sp1;
	wPtr<List<int>,1> wp2;
	wp2=wp1.share();
	wp2=wp2.share();
	cout<<endl<<"Current owners:"<<wp1.share().currentOwners()<<endl;
	List<int>* a=new List<int>;
	
}
#elif MAIN==1
int main(){
	shared_ptr<List<int>> sp1(new List<int>{6,4,2,465,1});
	weak_ptr<List<int>> wp1=sp1;
	sp1=nullptr;
	cout<<endl<<"Current owners:"<<wp1.lock().use_count()<<endl;
	sp1=nullptr;
	shared_ptr<List<int>> sp2=sp1;
	weak_ptr<List<int>> wp2;
	wp2=wp1.lock();
	wp2=wp2.lock();
	cout<<endl<<"Current owners:"<<wp1.lock().use_count()<<endl;
}
#elif MAIN==2
int main(){
	sPtr sp1=new List<List<int>>;
	wPtr wp1=sp1;
	wp1.share()->setSize(10);
	wPtr wp2=sp1;
	sPtr sp2=sp1;
	sp1=nullptr;
	sp2=new List<List<int>>;
	cout<<wp1.currentOwners()<<endl;
	cout<<wp1.share().currentOwners()<<endl;
	cout<<sp2.currentOwners()<<endl;
}
#endif