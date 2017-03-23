#include <iostream>
#include <iomanip>
#include <fstream>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include "pin.H"

// Macros to update global history
#define GHIST_TAKE(h) (h = (((h << 1) + 1) << nub) >> nub)
#define GHIST_NTAKE(h) (h = ((h << 1) << nub) >> nub)

typedef unsigned int uint;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "bpred.out", "specify file name for branch predictor output");
KNOB<UINT32> KnobM(KNOB_MODE_WRITEONCE, "pintool", "m", "0", "Global history size 0 <= m <= 16");
KNOB<UINT32> KnobN(KNOB_MODE_WRITEONCE, "pintool", "n", "1", "Counter width n >= 1");
KNOB<UINT32> KnobK(KNOB_MODE_WRITEONCE, "pintool", "k", "0", "Branch PC bits to use k, 0 <= k <= 16");

// These variables are my placeholders.  You may replace or modify 
// their usage, as needed.  However the final output format (see Fini, 
// below) should be unchanged.
uint total_bits = 0;
float accuracy = 0;

// Counter FSM
uint n = 0;
uint top_n;

// History
uint m = 0;
int nub; // not_used_bytes
uint hist_state; // global history counter
uint columns;

// Related to number of entries in the table
uint k = 0;
uint rows;

// The local state
int *local_counters;

uint total_branches = 0;
uint total_taken = 0;
uint total_fallthru = 0;


void init_globals(){

  n = KnobN.Value();
  top_n = pow(2, n);

  // History related
  m = KnobM.Value();
  nub = sizeof(int) * 8 - m;
  hist_state = 0; //Initialize the counter to 0
  columns = pow(2, m);

  // Table
  k = KnobK.Value();
  rows = pow(2, k);

  local_counters = malloc(sizeof(int) * rows * columns);
  assert(local_counters != NULL);
  memset(local_counters, 0, sizeof(int) * rows * columns);

  cout << local_counters[0][1]; 
  local_counters[0][3]++;
  cout << local_counters[0][1]; 


}

// Invoked once per dynamic branch instruction
// pc: The address of the branch
// taken: Non zero if a branch is taken
VOID DoBranch(ADDRINT pc, BOOL taken) {
  total_branches++;
  if(taken){
    total_taken++;
    //cout << "T ";
    GHIST_TAKE(hist_state);
  }else{
    total_fallthru++;
    //cout << "NT ";
    GHIST_NTAKE(hist_state);
  }
  //cout << hist_state << endl;
}

// Called once per runtime image load
VOID Image(IMG img, VOID * v) {
  // find and instrument branches
  for (SEC sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec)) {
    for (RTN rtn = SEC_RtnHead(sec); RTN_Valid(rtn); rtn = RTN_Next(rtn)) {
      RTN_Open(rtn);
      for (INS ins = RTN_InsHead(rtn); INS_Valid(ins); ins = INS_Next(ins)) {
	if (INS_IsBranch(ins) && INS_HasFallThrough(ins)) {
	  INS_InsertCall( ins, IPOINT_BEFORE, (AFUNPTR)DoBranch, IARG_INST_PTR, IARG_BRANCH_TAKEN, IARG_END);
	}
      }
      RTN_Close(rtn);
    }
  }
}

INT32 Usage() {
  cerr << "This pin tool simulates an (m,n,k) branch predictor." << endl;
  cerr << KNOB_BASE::StringKnobSummary();
  cerr << endl;
  return -1;
}

// Called once upon program exit
VOID Fini(int, VOID * v) {

    string filename;
    std::ofstream out;
    filename =  KnobOutputFile.Value();

    out.open(filename.c_str());
    out << "m: " << KnobM.Value() << endl;
    out << "n: " << KnobN.Value() << endl;
    out << "k: " << KnobK.Value() << endl;
    out << "total_branches: " << total_branches << endl;
    out << "total_taken: " << total_taken << endl;
    out << "total_fallthru: " << total_fallthru << endl;
    out << "total_bits: " << total_bits << endl;
    out << "accuracy: " << setprecision(3) << accuracy << endl;

    out.close();

    // Cleanuup
    free(local_counters);
}

bool check_input(){
  
  // Make sure provided k makes sense
  if(k > 16 || k < 0)
    return false;

  // Make sure provided m makes sense
  if(m > 16 || m < 0)
    return false;

  // Since we are using ints to represent the counter,
  // it better be that the counter fits into an int
  if(n > (sizeof(int) * 8) || n < 0)
    return false;

  if(local_counters == NULL)
    return false;


  return true;
}

// Called once prior to program execution
int main(int argc, CHAR *argv[]) {
    PIN_InitSymbols();

    if (PIN_Init(argc, argv)) {
        return Usage();
    }

    init_globals();
    if(!check_input()){
      return Usage();
    }

    cout << "n = " << n << ", m = " << m << ", k = " << k << endl;
    cout << "nub = " << nub << " h -> " << hist_state << endl;

    IMG_AddInstrumentFunction(Image, 0);
    PIN_AddFiniFunction(Fini, 0);

    PIN_StartProgram();

    return 0;
}

