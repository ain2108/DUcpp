#define T 1
#define NT 0


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int m = 0; // 8 bits to represent history
int nub = 0;

#define take(hist_state) ((((hist_state << 1) + 1) << nub) >> nub)
#define ntake(hist_state) (((hist_state << 1) << nub) >> nub)

#define GET_COUNTER(i,j) *(local_counters + columns * i + j)
#define SET_COUNTER(i,j, value) (*(local_counters + columns * i + j) = value);

int *local_counters;
int rows = 0;
int columns = 0;

void print_local_counters(){
  
  for(int i = 0; i < rows; i++){
    for (int j = 0; j < columns; j++){
    	//fprintf(stdout, " %d", ((int *[rows][columns])local_counters)[i][j]);
    	//fprintf(stdout, " %d", (*local_counters)[i][j]);
    	fprintf(stdout, " %d", GET_COUNTER(i, j));
    }
    fprintf(stdout, "\n");
  } 
}

void print_stuff(int taken, unsigned int hist_state){
	if(taken){
		fprintf(stdout, "T\t-> %d\n", hist_state);
	}else{
		fprintf(stdout, "NT\t-> %d\n", hist_state);
	}
	
}

void hello(){printf("called hello()\n");}
void helloSpecial(){printf("called helloSpecial()\n");}

int main(){

	// unsigned int hist_state = 0;
	// nub = sizeof(int) * 8 - m;

	// //T 0001 = 1
	// hist_state = take(hist_state);
	// print_stuff(T, hist_state);
	
	// //NT 0010 = 2
	// hist_state = ntake(hist_state);
	// print_stuff(NT, hist_state);

	// //T 0101 = 5
	// hist_state = take(hist_state);
	// print_stuff(T, hist_state);
	// //T 1011 = 10
	// hist_state = take(hist_state);
	// print_stuff(T, hist_state);

	// //T 0101 = 7
	// hist_state = take(hist_state);
	// print_stuff(T, hist_state);
	// //T 1011 = 15
	// hist_state = take(hist_state);
	// print_stuff(T, hist_state);

	// //T 0111 = 15
	// hist_state = take(hist_state);
	// print_stuff(T, hist_state);
	// //T 1111 = 15
	// hist_state = take(hist_state);
	// print_stuff(T, hist_state);

	// rows = 4;
	// columns = 16;

	// local_counters = malloc(sizeof(int) * rows * columns);
	// memset(local_counters, 0, sizeof(int) * rows * columns);

	// SET_COUNTER(1, 1, 7);
	// SET_COUNTER(3, 1, 9);

	// if(true) hello = helloSpecial;

	// hello();

	// print_local_counters();

	int b = 0;
	int n = 1;
	int m = 0;
	int k = 0;

	// 1 bit counter
	fprintf(stdout, "echo \"1-BIT counter\" >> data.sh\n");
	while(b <= 9){
		fprintf(stdout, "echo \"BUDGET: %d BITS\" >> data.sh\n", (int) pow(2, (double) b));
		if(b == 0){
			m = 0;
			k = 0;
			fprintf(stdout, "$PIN_ROOT/pin -t obj-intel64/bpred.so -n %d -m %d -k %d -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh\n", n, m, k);
			b++;
			continue;
		}
		while(m <= b){
			k = b - m;
			fprintf(stdout, "$PIN_ROOT/pin -t obj-intel64/bpred.so -n %d -m %d -k %d -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh\n", n, m, k);
			m++;
		}
		m = 0;
		k = 0;
		b++;
	}

	b = 1;
	n = 2;
	m = 0;
	k = 0;

	// 2 bit counter
	fprintf(stdout, "echo \"2-BIT counter\" >> data.sh\n");
	while(b <= 9){
		fprintf(stdout, "echo \"BUDGET: %d BITS\" >> data.sh\n", (int) pow(2, (double) b));
		if(b == 1){
			n = 2;
			m = 0;
			k = 0;
			fprintf(stdout, "$PIN_ROOT/pin -t obj-intel64/bpred.so -n %d -m %d -k %d -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh\n", n, m, k);
			b++;
			continue;
		}
		while(m <= (b - 1)){
			k = (b - 1) - m;
			fprintf(stdout, "$PIN_ROOT/pin -t obj-intel64/bpred.so -n %d -m %d -k %d -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh\n", n, m, k);
			m++;
		}
		m = 0;
		k = 0;
		b++;
	}



	return 0;
}





