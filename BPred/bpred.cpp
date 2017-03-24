/* Anton Nefedenkov ain2108
 * Computer Architecture HW2: Branch Prediction */

/* Notes:
  1) To keep high performace and minimize the number of instructions
  in DoBranch() code, I have 4 different functions out of which
  DoBranch function pointer is going to point to one. 
  2) Eventhough I have been reading contradicting information, I
  settled on implementing the 2-BIT counter according to the following
  table:
    +---------+-----+-----+
    | Current |  T  | NT  |
    +---------+-----+-----+
    | SNT     | WNT | SNT |
    | WNT     | ST  | SNT |
    | WT      | ST  | SNT |
    | ST      | ST  | WT  |
    +---------+-----+-----+
  3) I am aware that the code is a monstrosity. The reason for all these
  globals is to not pass states around. The table of counters is allocated
  in such weird manner to avoid int** (an array of integer pointers) setup,
  which would force me to jump an extra pointer in DoBranch() (that is to
  be kept as fast as possible).
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <assert.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "pin.H"

typedef unsigned int uint;

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "bpred.out", "specify file name for branch predictor output");
KNOB<UINT32> KnobM(KNOB_MODE_WRITEONCE, "pintool", "m", "0", "Global history size 0 <= m <= 16");
KNOB<UINT32> KnobN(KNOB_MODE_WRITEONCE, "pintool", "n", "1", "Counter width n >= 1");
KNOB<UINT32> KnobK(KNOB_MODE_WRITEONCE, "pintool", "k", "0", "Branch PC bits to use k, 0 <= k <= 16");

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////// VARS AND CPP ////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

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


uint total_bits = 0;
uint correctly_predicted = 0;   // Used to calculate accuracy
float accuracy = 0;
uint total_branches = 0;
uint total_taken = 0;
uint total_fallthru = 0;

// Counter FSM
uint n = 0;
uint top_n;
uint taken_starts;

// History
uint m = 0;
int nub;                        // not_used_bytes
uint hist_state;                // global history counter
int columns;

// Related to number of entries in the table
uint k = 0;
int rows;                       // Number of PC mod tracked

// The local state
int *local_counters;

// Little heler to get a visual of what is ging on
void print_local_counters(){
  cout << "print counter table:\n";
  for(int i = 0; i < rows; i++){
    for (int j = 0; j < columns; j++){
      cout << " " << GET_COUNTER(i, j);
    }
      cout << endl;
  } 
}

void print_globals(){
  cout << "n: " << n << ", m: " << m << ", k: " << k << endl << endl;  
  cout << "n: " << n << " top_n: "; 
  cout << top_n << " taken_starts: " << taken_starts << endl;
  cout << "m: " << m << " nub: " << nub << endl;
  cout << "rows: " << rows << " columns: " << columns << endl;
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////// DO BRANCHES /////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

/*  Since two bit counters transition differently from the 
    general n counters, we want to have a separate definition for them */
// Invoked once per dynamic branch instruction
// pc: The address of the branch
// taken: Non zero if a branch is taken
// 2-bit counter version
VOID DoBranch2BIT(ADDRINT pc, BOOL taken) {
  // We know that this is a branch, so increment
  total_branches++;
  int entry_row = pc % rows;
  // We want to get the counter on which we are going to base the prediction
  uint loc_counter = GET_COUNTER(entry_row, hist_state);
  // Make the prediction
  bool predict_taken = (loc_counter >= taken_starts);

  // If the branch was actually taken
  if(taken){
    total_taken++;
    // We predicted the branch correctly
    if(predict_taken){
      correctly_predicted++;
    }
    // Only when we are Strongly Not Taken do we change NOT to
    // Strongly Taken. Therefore simple conditinal suffices.
    if(loc_counter == SNT){
      SET_COUNTER(entry_row, hist_state, WNT);
    }else{
      SET_COUNTER(entry_row, hist_state, ST);
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
    // Similarly, only when we are in ST and we do not take the 
    // branch do we go into not SNT.
    if(loc_counter == ST){
      SET_COUNTER(entry_row, hist_state, WT);
    }else{
      SET_COUNTER(entry_row, hist_state, SNT);
    }

    // Change the history to reflect that the branch was NOT TAKEN
    GHIST_NTAKE(hist_state);
  }
}

// the general case
VOID DoBranchGeneral(ADDRINT pc, BOOL taken) {
  // We know that this is a branch, so increment
  total_branches++;
  
  int entry_row = pc % rows;
  // We want to get the counter on which we are going to base the prediction
  uint loc_counter = GET_COUNTER(entry_row, hist_state);
  // Make the prediction
  bool predict_taken = (loc_counter >= taken_starts);
  // Lets also calculate if the counter is in saturate state
  bool not_floor = (loc_counter > 0);
  bool not_ceiling = (loc_counter < top_n);

  // If the branch was actually taken
  if(taken){
    total_taken++;

    // We predicted the branch correctly
    if(predict_taken){
      correctly_predicted++;
    }
    // If counter is in a state that will be changed
    if(not_ceiling){
      loc_counter++;
      SET_COUNTER(entry_row, hist_state, loc_counter);
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
    if(not_floor){
      loc_counter--;
      SET_COUNTER(entry_row, hist_state, loc_counter);
    }
    // Change the history to reflect that the branch was NOT TAKEN
    GHIST_NTAKE(hist_state);
  }
}

/* These function as for the global-history-less option */
// 2-bit counter historyless version
VOID DoBranch2BITNoHist(ADDRINT pc, BOOL taken) {
  // We know that this is a branch, so increment
  total_branches++;
  int entry_row = pc % rows;
  // We want to get the counter on which we are going to base the prediction
  uint loc_counter = GET_COUNTER(entry_row, 0);
  // Make the prediction
  bool predict_taken = (loc_counter >= taken_starts);

  // If the branch was actually taken
  if(taken){
    total_taken++;
    // We predicted the branch correctly
    if(predict_taken){
      correctly_predicted++;
    }
    // Only when we are Strongly Not Taken do we change NOT to
    // Strongly Taken. Therefore simple conditinal suffices.
    if(loc_counter == SNT){
      SET_COUNTER(entry_row, 0, WNT);
    }else{
      SET_COUNTER(entry_row, 0, ST);
    }
  
  // Branch was not taken 
  }else{
    total_fallthru++;

    // We predicted the branch correctly
    if(!predict_taken){
      correctly_predicted++;
    }
    // Similarly, only when we are in ST and we do not take the 
    // branch do we go into not SNT.
    if(loc_counter == ST){
      SET_COUNTER(entry_row, 0, WT);
    }else{
      SET_COUNTER(entry_row, 0, SNT);
    }
  }
}

// the general case
VOID DoBranchGeneralNoHist(ADDRINT pc, BOOL taken) {
  // We know that this is a branch, so increment
  total_branches++;
  
  int entry_row = pc % rows;
  // We want to get the counter on which we are going to base the prediction
  uint loc_counter = GET_COUNTER(entry_row, 0);
  // Make the prediction
  bool predict_taken = (loc_counter >= taken_starts);
  // Lets also calculate if the counter is in saturate state
  bool not_floor = (loc_counter > 0);
  bool not_ceiling = (loc_counter < top_n);

  // If the branch was actually taken
  if(taken){
    total_taken++;

    // We predicted the branch correctly
    if(predict_taken){
      correctly_predicted++;
    }
    // If counter is in a state that will be changed
    if(not_ceiling){
      loc_counter++;
      SET_COUNTER(entry_row, 0, loc_counter);
    }

  // Branch was not taken 
  }else{
    total_fallthru++;

    // We predicted the branch correctly
    if(!predict_taken){
      correctly_predicted++;
    }
    // If counter is in a state that will be changed
    if(not_floor){
      loc_counter--;
      SET_COUNTER(entry_row, 0, loc_counter);
    }
  }
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
////////////////////////// OTHER /////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////



void init_globals(){

  // Counter related stuff
  n = KnobN.Value();
  top_n = (int) pow(2, (double) n) - 1;
  taken_starts = (top_n + 1) / 2;

  // History related
  m = KnobM.Value();
  nub = sizeof(int) * 8 - m;

  // We need to change the function pointer here for two bit counter
  if(n == TWO){
    if(m != 0){
      DoBranch = DoBranch2BIT;
    }else{
      DoBranch = DoBranch2BITNoHist;
    }
  }else{
    if(m != 0){
      DoBranch = DoBranchGeneral;
    }else{
      DoBranch = DoBranchGeneralNoHist;
    }
  }

  hist_state = 0; //Initialize the counter to 0
  columns = (int) pow(2, (double) m);

  // Table
  k = KnobK.Value();
  rows = (int) pow(2, (double) k);
  local_counters = (int *) malloc(sizeof(int) * rows * columns);
  assert(local_counters != NULL);
  memset(local_counters, 0, sizeof(int) * rows * columns);

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


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////// BARELY TOUCHED BELOW ////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


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

    // Calculate the accuracy here
    accuracy = (float) correctly_predicted / total_branches;
    // Calculate the size of the predictor
    total_bits = n * rows * columns;

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

    fprintf(stdout, "(%d, %d, %d)\t", n, m, k);
    cout << setprecision(3) << accuracy << endl;

    // print_local_counters();
    // Cleanuup
    free(local_counters);
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

    IMG_AddInstrumentFunction(Image, 0);
    PIN_AddFiniFunction(Fini, 0);

    PIN_StartProgram();

    return 0;
}

