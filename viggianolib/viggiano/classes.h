#pragma once
#ifdef SHOWREMAININGOBJECTS
#define SETCOUNTERS		int remainingQueues=0;\
						int remainingStacks=0;\
						int remainingLists=0;\
						int remainingStrings=0;\
						int remainingControlBlocks=0;\
						int remainingStrongPointers=0;\
						int remainingWeakPointers=0;\
						int remainingUniquePointers=0;\
						int remainingTrees=0;\
						int remainingListNodes=0;
						
#define INCQUEUES 					remainingQueues++;
#define DECQUEUES					remainingQueues--;
#define REMAININGQUEUES 			printf("\nREMAINING QUEUES: %d\n",remainingQueues);
#define INCSTACKS 					remainingStacks++;
#define DECSTACKS 					remainingStacks--;
#define REMAININGSTACKS	 			printf("\nREMAINING STACKS: %d\n",remainingStacks);
#define INCLISTS  					remainingLists++;
#define DECLISTS  					remainingLists--;
#define REMAININGLISTS 				printf("\nREMAINING LISTS: %d\n",remainingLists);
#define INCSTRINGS 					remainingStrings++;
#define DECSTRINGS					remainingStrings--;
#define REMAININGSTRINGS 			printf("\nREMAINING STRINGS: %d\n",remainingStrings);
#define INCCTRLBLOCKS				remainingControlBlocks++;
#define DECCTRLBLOCKS				remainingControlBlocks--;
#define REMAININGCTRLBLOCKS 		printf("\nREMAINING CONTROL BLOCKS: %d\n",remainingControlBlocks);
#define INCSTRONGPOINTERS 			remainingStrongPointers++;
#define DECSTRONGPOINTERS 			remainingStrongPointers--;
#define REMAININGSTRONGPOINTERS 	printf("\nREMAINING STRONG POINTERS: %d\n",remainingStrongPointers);
#define INCWEAKPOINTERS				remainingWeakPointers++;
#define DECWEAKPOINTERS				remainingWeakPointers--;
#define REMAININGWEAKPOINTERS		printf("\nREMAINING WEAK POINTERS: %d\n",remainingWeakPointers);
#define INCUNIQUEPOINTERS			remainingUniquePointers++;
#define DECUNIQUEPOINTERS			remainingUniquePointers--;
#define REMAININGUNIQUEPOINTERS		printf("\nREMAINING UNIQUE POINTERS: %d\n",remainingUniquePointers);
#define INCTREES					remainingTrees++;
#define DECTREES					remainingTrees--;
#define REMAININGTREES				printf("\nREMAINING TREES: %d\n",remainingTrees);
#define INCLNODES					remainingListNodes++;
#define DECLNODES					remainingListNodes--;
#define REMAININGLNODES				printf("\nREMAINING LIST NODES: %d\n",remainingListNodes);
#else
#define SETCOUNTERS
#define INCQUEUES
#define DECQUEUES
#define REMAININGQUEUES
#define INCSTACKS
#define DECSTACKS
#define REMAININGSTACKS
#define INCLISTS
#define DECLISTS
#define REMAININGLISTS
#define INCSTRINGS
#define DECSTRINGS
#define REMAININGSTRINGS
#define INCCTRLBLOCKS
#define DECCTRLBLOCKS
#define REMAININGCTRLBLOCKS
#define INCSTRONGPOINTERS
#define DECSTRONGPOINTERS
#define REMAININGSTRONGPOINTERS
#define INCWEAKPOINTERS
#define DECWEAKPOINTERS
#define REMAININGWEAKPOINTERS
#define INCUNIQUEPOINTERS
#define DECUNIQUEPOINTERS
#define REMAININGUNIQUEPOINTERS
#define INCTREES
#define DECTREES
#define REMAININGTREES
#define INCLNODES
#define DECLNODES
#define REMAININGLNODES
#endif
SETCOUNTERS
namespace mpv{
	template<typename T1,typename T2>
	struct Pair{
		T1 d1;
		T2 d2;
		Pair(){}
		Pair(T1 data1,T2 data2):d1(data1),d2(data2){}
	};
}
#include"Classes/Lists.h"
#include"Classes/ArrayLists.h"
#include"Classes/Stacks_Queues.h"
#include"Classes/AutoPtr.h"
#include"Classes/Strings.h"
#include"Classes/Red-Black Tree.h"
