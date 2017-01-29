
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "help.h"


#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define DEBUG 0

using namespace std;

int main(int argc, char *argv[]){

	/* Check the command line arguments */
	if (!cmd_args_good(argc, argv)) {
		cout << "usage: " << argv[0] <<" <number N>\n";
		return -EXIT_FAILURE;
	}

	vector<int> sequence = generate_random_sequence(atoi(argv[1]));

	if(DEBUG)
		print_sequence(sequence);

	test_vector(sequence);
	test_list(sequence);

	return EXIT_SUCCESS;	
}
