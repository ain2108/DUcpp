#include <string>
#include <regex>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <random>
#include <stdexcept>

#include "help.h"

using namespace std;

void print_sequence(vector<int>& sequence){

	for(auto x : sequence) {
		/*if(x == 0)
			break;
		*/
		cout << x << " ";
	}
	cout << '\n';
}

template <typename Container>
bool sequence_good(const Container& seq){
	int i = 0;
	for(auto a : seq){
		/*if (a == 0)
			break;*/

		if (a != i + 1)
			return false;
		i++; 
	}
	return true;
}


void test_vector(vector<int>& sequence){

	vector<int> test_vector;	
	//test_vector[0] = sequence[0];

	/* Start timer */
	auto start1 = chrono::high_resolution_clock::now();
	
	/* Iterate throug the input sequence, adding the elements sequentially
	 * to our array */
	for(int i = 0; i < sequence.size(); i++) {

		/* We find an element already in the vector that is bigger
		 * than the new element. */
		vector<int>::iterator pos = find_if(test_vector.begin(), 
			test_vector.end(), 
			[i, &sequence](int a){ return sequence[i] < a;});

		/* If such element was not found, we know that we should
		 * add the element in the end, since its the biggest */
		if(pos == test_vector.end()){
			test_vector.insert(test_vector.begin() + i, sequence[i]);
			continue;
		}

		test_vector.insert(pos, sequence[i]);

	}

	auto stop1 = chrono::high_resolution_clock::now();

	/* Quick check here to make sure logic was not wrong */
	if (!sequence_good(test_vector))
		throw logic_error("sequence not ordered as expected\n");

	auto start2 = chrono::high_resolution_clock::now();

	for(int i = 0; i < sequence.size(); i++) {
		test_vector.erase(test_vector.begin() + ((sequence[i] - 1)%test_vector.size()));
	}


	/* Stop timer */
	auto stop2 = chrono::high_resolution_clock::now();

	using namespace std::chrono;
	cout << duration_cast<nanoseconds>((stop1 - start1) + (stop2 - start2)).count() << "nsec\n";
	cout << duration_cast<milliseconds>((stop1 - start1) + (stop2 - start2)).count() << "msec\n";

	print_sequence(test_vector);

}

void test_list(vector<int>& sequence){
	
}

vector<int> generate_random_sequence(int n){

	vector<int> sequence(n);

	/* Populate the vector with n distinc integers */
	for (int i = 0; i < n; i++) {
		sequence[i] = i + 1; /* Note the start from 1*/
	}

	/* Shuffle the array randomly to get a random sequence */
	shuffle(sequence.begin(), sequence.end(), 
		default_random_engine(random_device()()));

	return sequence;
}

bool is_int(const string& N){
	return regex_match(N, regex("[0-9]+"));
}

bool cmd_args_good(int argc, char **argv){

	if (argc != 2) {
		return false;
	}
	string s(argv[1]);
	return is_int(s);
}