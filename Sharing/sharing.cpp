#include <stdio.h>
#include "pin.H"
#include <iostream>
#include <map>
#include <fstream>
#include <exception>
#include <memory>


#define MAX_THREAD_ID 32

#include <iostream>
#include <string.h>


//using namespace std;

#define BLOCK_SIZE_BYTES 64
#define WORD_SIZE_BYTES 4

#define PRIVATE 0
#define FALSE_SHARED 1
#define TRUE_SHARED 2
#define MAX_THREAD_ID 32
#define NO_THREAD -1

unsigned long word_mask = 0x3c;
class Block;

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
		std::cout << "Block accesses by tid:\n";
		for(int i = 0; i < BLOCK_SIZE_BYTES/WORD_SIZE_BYTES; i++){
			cout << (int) word_accessed[i] << " ";		
		}
		std::cout << "\nStatus: " << (int) status << "\tfirst_owner: " << (int) first_owner << endl;
	}
};

//LOCALVAR unordered_map <unsigned long, Block *> blocks;
LOCALVAR std::map<unsigned long, Block *> blocks;
LOCALVAR PIN_MUTEX map_lock;
//LOCALVAR int blocks_used = 0;
VOID MemRef(THREADID tid, VOID* addr) {

	PIN_MutexLock(&map_lock);
	//mem_ref_counter++;

	//unsigned long uaddr = ((unsigned long) addr);
	unsigned long block_addr = ((((unsigned long) addr) >> 6) << 6);
	int word_in_block = (((unsigned long) addr) & word_mask) >> 2;

	/* Check if we have that block in the map already */
	if(blocks.find(block_addr) == blocks.end()){
		Block *b = new Block((char) tid, word_in_block);
		b->word_accessed[word_in_block] = (char) tid;
		blocks[block_addr] = b;
		//blocks_used++;
		PIN_MutexUnlock(&map_lock);
		return;

	/* If the block is already in the map, we would like to work with it */
	}else{

		/* Lets get a pointer to that block so we can work with it*/
		Block *b = blocks[block_addr];


		/* If we know that a block is true shared already, we dont have to do anything, can go for a smoke. */
		if(b->status == TRUE_SHARED){
			//b->word_accessed[word_in_block] = (char) tid;
			PIN_MutexUnlock(&map_lock);
			return;
		}
		

		if(b->status == PRIVATE){

			/* If no other thread has accessed this block yet */
			if(b->first_owner == (char) tid){
		 		b->word_accessed[word_in_block] = (char) tid;
		 		PIN_MutexUnlock(&map_lock);
		 		return;
			}

			/* If we are a different thread, check if the word was not touched. 
			If so, touch and set shared */
			if(b->word_accessed[word_in_block] == (char) NO_THREAD){
				b->word_accessed[word_in_block] = (char) tid;
				b->status = FALSE_SHARED;
				b->first_owner = NO_THREAD;
				PIN_MutexUnlock(&map_lock);
				return;
			}

			/* If we collide with the thread, we should mark it TRUE_SHARED */
			//if(b->word_accessed[word_in_block] != (char) tid){
			//b->word_accessed[word_in_block] = (char) tid;
			b->status = TRUE_SHARED;
			//b->first_owner = NO_THREAD;
			PIN_MutexUnlock(&map_lock);
			return;
			//}

			// cout << "ERROR in Private" << endl;
			// std::exit(0);

		}

		//if(b->status == FALSE_SHARED){
			/* If we collide with the thread, we should mark it TRUE_SHARED */
			if(b->word_accessed[word_in_block] == (char) NO_THREAD || b->word_accessed[word_in_block] == (char) tid){
				b->word_accessed[word_in_block] = (char) tid;
				PIN_MutexUnlock(&map_lock);
				return;
			}

			// if(b->word_accessed[word_in_block] == (char) tid){
			// 	b->word_accessed[word_in_block] = (char) tid;
			// 	PIN_MutexUnlock(&map_lock);
			// 	return;
			// }

			//if(b->word_accessed[word_in_block] != (char) tid){
			//b->word_accessed[word_in_block] = (char) tid;
			b->status = TRUE_SHARED;
			PIN_MutexUnlock(&map_lock);
			return;
			//}

			// cout << "ERROR in FALSE_SHARED" << endl;
			// std::exit(0);


		//}


	}
	
	std::cout << "ERROR in General" << endl;
	std::exit(0);
	return;
}

void print_false_shared(){
	int count_false_shared = 0;
	int count_true_shared = 0;
	int count_private = 0;
	std::map<unsigned long, Block *>::iterator it;
	for(it = blocks.begin(); it != blocks.end(); ++it){
		if(it->second->status == FALSE_SHARED){
	 		//cout << it->first << endl;
	 		count_false_shared++; 
	 	}

	 	if(it->second->status == TRUE_SHARED){
	 		//cout << it->first << endl;
	 		count_true_shared++; 
	 	}

	 	if(it->second->status == PRIVATE){
	 		//cout << it->first << endl;
	 		count_private++; 
	 	}

	}
	cout << "total false shared: " << count_false_shared << endl;
	cout << "total true shared: " << count_true_shared << endl;
	cout << "total private: " << count_private << endl;

	//cout << "total blocks created: " << blocks_used << endl;
}

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "sharing.out", "file name for falsely-shared cache block list");


// Note: Instrumentation function adapted from ManualExamples/pinatrace.cpp
// It is called for each Trace and instruments reads and writes
VOID Trace(TRACE trace, VOID *v) {
  // Visit every basic block  in the trace
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

	string filename;
    std::ofstream out;
    filename =  KnobOutputFile.Value();
    out.open(filename.c_str());


    int count_false_shared = 0;

	std::map<unsigned long, Block *>::iterator it;
	for(it = blocks.begin(); it != blocks.end(); ++it){
		if(it->second->status == FALSE_SHARED){
	 		out << ((void *) it->first) << endl;
	 		count_false_shared++; 
	 	}
	}


    out.close();
	print_false_shared();
	//cout << "memref was called " << mem_ref_counter << " times " << endl;
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


    /* Init the lock */
    if(PIN_MutexInit(&map_lock) == false){
    	std::cout << "fire\n";
    	return 1;
    }

    TRACE_AddInstrumentFunction(Trace, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}
