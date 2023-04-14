#include"viggiano.h"
using namespace std;
using namespace vgg;
struct retCycle{
	wPtr<retCycle> next;
};
int main(){
	sPtr<retCycle> sp1;
	sPtr<retCycle> sp2;
	sp1= new retCycle;
	sp2= new retCycle;
	
	sp2->next=sp1;
	sp1->next=sp2;
	uPtr<List<int>,1> up1= new List<int>[3]{4,5,25};
	uPtr<List<int>,1> up2;
	up2=new List<int>[5]{4,2,-54,6,243};
	//up2=(uPtr<List<int>,1>&&)up1;
	for range(i,5){
		up2[i].print();
	}
}