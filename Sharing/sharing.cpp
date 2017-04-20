#include <stdio.h>
#include "pin.H"

#define MAX_THREAD_ID 32

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "sharing.out", "file name for falsely-shared cache block list");

// This analysis routine is called on every memory reference.
VOID MemRef(THREADID tid, VOID* addr) {
}

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
	fprintf(stdout, "%p\n", v);
	cout << "hello?\n";
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

    TRACE_AddInstrumentFunction(Trace, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}
