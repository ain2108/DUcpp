
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "help.h"


#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

using namespace std;

int main(int argc, char *argv[]){

	/* Check the command line arguments */
	if (!cmd_args_good(argc, argv)) {
		cout << "usage: " << argv[0] <<" <number N>\n";
		return -EXIT_FAILURE;
	}

	/* Generate the random sequence of requested size */
	vector<int> sequence = generate_random_sequence(atoi(argv[1]));

	/* Run the tests */
	test(sequence);

	return EXIT_SUCCESS;	
}
