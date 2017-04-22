#include <stdio.h>
#include "pin.H"
#include <iostream>
#include <map>

#define MAX_THREAD_ID 32

#include <iostream>
#include <map>
#include <string.h>


using namespace std;

#define BLOCK_SIZE_BYTES 64
#define WORD_SIZE_BYTES 4

#define PRIVATE 0
#define FALSE_SHARED 1
#define TRUE_SHARED 2
#define MAX_THREAD_ID 32
#define NO_THREAD -1

unsigned long word_mask = 0x3c;

class Block;
static map<unsigned long, Block *> blocks;
static PIN_MUTEX map_lock;


class Block{
public:
	/* This array represents the accesses of the word, 
	entry in this array will store the thread id that has accessed it */
	char word_accessed[BLOCK_SIZE_BYTES / WORD_SIZE_BYTES];
	char status;
	char first_owner;

	Block(char owner, int owned_word_index){
		memset(&word_accessed, -1, BLOCK_SIZE_BYTES / WORD_SIZE_BYTES);
		word_accessed[owned_word_index] = owner;
		status = PRIVATE;
		first_owner = owner;
	}

	~Block(){

	}

	void print_Block(){
		cout << "Block accesses by tid:\n";
		for(int i = 0; i < BLOCK_SIZE_BYTES/WORD_SIZE_BYTES; i++){
			cout << (int) word_accessed[i] << " ";		
		}
		cout << "\nStatus: " << (int) status << "\tfirst_owner: " << (int) first_owner << endl;
	}
};

vector<vector<unsigned long> > accesses(MAX_THREAD_ID);


static int mem_ref_counter = 0;
VOID MemRef(THREADID tid, VOID* addr) {
	PIN_MutexLock(&map_lock);
	accesses[(int) tid].push_back((unsigned long) addr);
	mem_ref_counter++;
	PIN_MutexUnlock(&map_lock);
	//cout << tid << endl;
}

static int blocks_used = 0;
VOID MemRefProcess(THREADID tid, VOID* addr) {

	// PIN_MutexLock(map_lock);
	// cout << "locked by " << tid << endl;
	unsigned long uaddr = (unsigned long) addr;
	unsigned long block_addr = ((uaddr >> 6) << 6);
	int word_in_block = (uaddr & word_mask) >> 2;
	//cout << uaddr << " " << block_addr << " " << word_in_block << endl;

	//cout << "locked " << (char) tid << " vs " << tid << endl;

	/* Check if we have that block in the map already */
	if(blocks.find(block_addr) == blocks.end()){
		Block *b = new Block((char) tid, word_in_block);
		b->word_accessed[word_in_block] = (char) tid;
		blocks[block_addr] = b;
		blocks_used++;
		//cout << "created new block " << block_addr << endl;
	/* If the block is already in the map, we would like to work with it */
	}else{

		/* Lets get a pointer to that block so we can work with it*/
		Block *b = blocks[block_addr];
		
		/* If we know that a block is true shared already, we dont have to do anything, can go for a smoke. */
		if(b->status == TRUE_SHARED){
			//TODO: unlock 
			// cout << "unlocked by " << tid << endl;
			// PIN_MutexUnlock(map_lock);
			return;
		}

		/* Lets check who the owner is. If we are that owner, then we are done. Notice, that when a block becomes shared,
		ownership is set NO_THREAD */
		if(b->first_owner == (char) tid){
			//TODO: unlock
			// cout << "unlocked by " << tid << endl;
			// PIN_MutexUnlock(map_lock);
			return;
		}

		/* At this point it is left to decide if we true share or fake share */
		/* We want to check if the word has been accessed by not us. Need to check against other threads as well as no thread */
		if((b->word_accessed[word_in_block] != (char) NO_THREAD) && (b->word_accessed[word_in_block] != (char) tid)){
			b->status = TRUE_SHARED;
		/* We know that this is not a true shared block, but we need to make sure everyone knows that we use the word */
		}else{
			b->word_accessed[word_in_block] = (char) tid;
			b->status = FALSE_SHARED;
			b->first_owner = NO_THREAD;
		}
	}

	//TODO: Unlock
	// cout << "unlocked by " << tid << endl;
	// PIN_MutexUnlock(map_lock);
	return;
}

void print_false_shared(){
	int count = 0;
	map<unsigned long, Block *>::iterator it;
	for(it = blocks.begin(); it != blocks.end(); ++it){
		if(it->second->status == FALSE_SHARED){
	 		cout << it->first << endl;
	 		count++; 
	 	}
	}
	cout << "total false shared: " << count << endl;
	cout << "total blocks created: " << blocks_used << endl;
}

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "sharing.out", "file name for falsely-shared cache block list");

// This analysis routine is called on every memory reference.
// VOID MemRef(THREADID tid, VOID* addr) {
// 	unsigned long uaddr = (unsigned long) addr;
// 	cout << uaddr << " by thread " << tid << endl;
// }

// Note: Instrumentation function adapted from ManualExamples/pinatrace.cpp
// It is called for each Trace and instruments reads and writes
VOID Trace(TRACE trace, VOID *v) {
  // Visit every basic block  in the trace
	cout << " trace was called\n";
  for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl)) {
      for (INS ins = BBL_InsHead(bbl); INS_Valid(ins); ins = INS_Next(ins)) {

	UINT32 memOperands = INS_MemoryOperandCount(ins);
	//    cout << "memOperands=" << memOperands << endl;
	for (UINT32 memOp = 0; memOp < memOperands; memOp++){
	  if (INS_MemoryOperandIsRead(ins, memOp)) {
	    //	  cout << "INS: " << INS_Disassemble(ins) << endl;
	    INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR)MemRef, 
				     IARG_THREAD_ID,
				     IARG_MEMORYOP_EA, memOp,
				     IARG_END);
	  }
	  if (INS_MemoryOperandIsWritten(ins, memOp)) {
	    INS_InsertPredicatedCall(ins, IPOINT_BEFORE, (AFUNPTR)MemRef, 
				     IARG_THREAD_ID,
				     IARG_MEMORYOP_EA, memOp,
				     IARG_END);
	  }
	}
      }
  }
}

VOID Fini(INT32 code, VOID *v) {

	vector<unsigned long>::iterator it_inner;
	int total_memrefs = 0;

	for(int i = 0; i < MAX_THREAD_ID; ++i){
		if(accesses[i].empty()){
			cout << "skip\n";
			continue;
		}

		cout << i << " has " << accesses[i].size() << endl;
		total_memrefs+= accesses[i].size();
		for(it_inner = accesses[i].begin(); it_inner != accesses[i].end(); ++it_inner){
			MemRefProcess((THREADID) i, (VOID *) (*it_inner));
		}
	}
	cout << "total accesses " << total_memrefs << endl;


	print_false_shared();

	cout << "memref was called " << mem_ref_counter << " times " << endl;
}

INT32 Usage()
{
    PIN_ERROR("This Pintool prints list of falsely-shared cache blocks\n"
              + KNOB_BASE::StringKnobSummary() + "\n");
    return -1;
}

int main(int argc, char *argv[])
{
    if (PIN_Init(argc, argv)) return Usage();

    cout << "morning!!!!!\n";

    /* Init the lock */
    if(PIN_MutexInit(&map_lock) == false){
    	cout << "fire\n";
    	return 1;
    }
    cout << "morning!\n";

    TRACE_AddInstrumentFunction(Trace, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}
