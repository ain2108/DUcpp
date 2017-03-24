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

// Managing the local counters, to avoid pointers "array of pointers"
#define GET_COUNTER(i,j) *(local_counters + columns * (i) + (j))
#define SET_COUNTER(i,j, value) (*(local_counters + columns * (i) + (j)) = (value));

// Few definitions for the 2-bit counter case
#define SNT 0   // Strongly Not Taken
#define WNT 1   // Weakly Not Taken 
#define WT 2    // Weakly Taken
#define ST 3    // Strongly Taken 
#define TWO 2   // :)

// To avoid changin Image code we gonna swap the pointer
VOID (*DoBranch)(ADDRINT pc, BOOL taken);

typedef unsigned int uint;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "bpred.out", "specify file name for branch predictor output");
KNOB<UINT32> KnobM(KNOB_MODE_WRITEONCE, "pintool", "m", "0", "Global history size 0 <= m <= 16");
KNOB<UINT32> KnobN(KNOB_MODE_WRITEONCE, "pintool", "n", "1", "Counter width n >= 1");
KNOB<UINT32> KnobK(KNOB_MODE_WRITEONCE, "pintool", "k", "0", "Branch PC bits to use k, 0 <= k <= 16");

// These variables are my placeholders.  You may replace or modify 
// their usage, as needed.  However the final output format (see Fini, 
// below) should be unchanged.
uint total_bits = 0;
uint correctly_predicted = 0;
float accuracy = 0;

// Counter FSM
uint n = 0;
uint top_n;
uint taken_starts;

// History
uint m = 0;
int nub; // not_used_bytes
uint hist_state; // global history counter
int columns;

// Related to number of entries in the table
uint k = 0;
int rows;

// The local state
int *local_counters;

uint total_branches = 0;
uint total_taken = 0;
uint total_fallthru = 0;

void print_local_counters(){

  cout << "print counter table:\n";
  
  for(int i = 0; i < rows; i++){
    for (int j = 0; j < columns; j++){
      cout << " " << GET_COUNTER(i, j);
    }
      cout << endl;
  } 
}

/*  Since two bit counters transition differently from the 
    general n counters, we want to have a separate definition for them */
// Invoked once per dynamic branch instruction
// pc: The address of the branch
// taken: Non zero if a branch is taken
// 2-bit counter version
VOID DoBranch2BIT(ADDRINT pc, BOOL taken) {
  total_branches++;
  if(taken){
    total_taken++;
    GHIST_TAKE(hist_state);
  }else{
    total_fallthru++;
    GHIST_NTAKE(hist_state);
  }
}

// the general case
VOID DoBranchGeneral(ADDRINT pc, BOOL taken) {
  // We know that this is a branch, so increment
  total_branches++;
  // We want to get the counter on which we are going to base the prediction
  int loc_counter = GET_COUNTER(pc % rows, hist_state);
  // Make the prediction
  bool predict_taken = (loc_counter >= taken_starts);
  // Lets also calculate if the counter is in saturate state
  bool interstate = (0 < loc_counter && loc_counter < top_n);

  // If the branch was actually taken
  if(taken){
    total_taken++;

    // We predicted the branch correctly
    if(predict_taken){
      correctly_predicted++;
    }
    // If counter is in a state that will be changed
    if(interstate){
      SET_COUNTER(pc % rows, hist_state, loc_counter + 1);
    }
    // Change the history to reflect that the branch was TAKEN
    GHIST_TAKE(hist_state);

  // Branch was not taken 
  }else{
    total_fallthru++;

    // We predicted the branch correctly
    if(!predict_taken){
      correctly_predicted++;
    }
    // If counter is in a state that will be changed
    if(interstate){
      SET_COUNTER(pc % rows, hist_state, loc_counter - 1);
    }
    // Change the history to reflect that the branch was NOT TAKEN
    GHIST_NTAKE(hist_state);
  }
}

void init_globals(){

  // Counter related stuff
  n = KnobN.Value();
  top_n = (int) pow(2, (double) n) - 1;
  taken_starts = (top_n + 1) / 2;

  cout << "n: " << n << " top_n: "; 
  cout << top_n << " taken_starts: " << taken_starts << endl;

  // We need to change the function pointer here for two bit counter
  if(n == TWO){
    DoBranch = DoBranch2BIT;
  }else{
    DoBranch = DoBranchGeneral;
  }

  // History related
  m = KnobM.Value();
  nub = sizeof(int) * 8 - m;
  hist_state = 0; //Initialize the counter to 0
  columns = (int) pow(2, (double) m);

  // Table
  k = KnobK.Value();
  rows = (int) pow(2, (double) k);

  cout << "rows: " << rows << " columns: " << columns << endl;

  local_counters = (int *) malloc(sizeof(int) * rows * columns);
  assert(local_counters != NULL);
  memset(local_counters, 0, sizeof(int) * rows * columns);

  print_local_counters();
  SET_COUNTER(1, 1, 10);
  print_local_counters();

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

    accuracy = (float) correctly_predicted / total_branches;

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

