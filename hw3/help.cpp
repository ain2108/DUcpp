#include <string>
#include <regex>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <random>
#include <stdexcept>
#include <list>

#include "help.h"

using namespace std;


template <typename Container>
void print_sequence(const Container& seq){
	for(auto a : seq){
		/*if (a == 0)
			break;*/
		cout << a << " ";
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

template <typename Container>
void runtest(vector<int>& sequence, Container& test_container){


	/* Part 1: */
	auto start1 = chrono::high_resolution_clock::now();
	typename Container::iterator temp;
	
	/* Iterate throug the input sequence, adding the elements sequentially
	 * to our array */
	for(int i = 0; i < sequence.size(); i++) {

		/* We find an element already in the Container that is bigger
		 * than the new element. */
		typename Container::iterator pos = find_if(test_container.begin(), 
			test_container.end(), 
			[i, &sequence](int a){ return sequence[i] < a;});

		/* If such element was not found, we know that we should
		 * add the element in the end, since its the biggest */
		if(pos == test_container.end()){

			/* Have to do this weird thing to avoid operator+ since it is not
			 * defined for list iterators */
			temp = test_container.begin();
			for (int j = 0; j < i; j++) {
				temp++;
			}
			test_container.insert(temp, sequence[i]);
			continue;
		}

		test_container.insert(pos, sequence[i]);

	}

	auto stop1 = chrono::high_resolution_clock::now();

	/* Quick check here to make sure logic was not wrong */
	if (!sequence_good(test_container))
		throw logic_error("sequence not ordered as expected\n");


	/* Part 2: */
	auto start2 = chrono::high_resolution_clock::now();
	for(int i = 0; i < sequence.size(); i++) {
		/* For the same reason as above */
		temp = test_container.begin();
		for (int j = 0; j < ((sequence[i] - 1)%test_container.size()); j++) {
			temp++;
		}
		test_container.erase(temp);
	}
	auto stop2 = chrono::high_resolution_clock::now();

	using namespace std::chrono;
	cout << duration_cast<nanoseconds>((stop1 - start1) + (stop2 - start2)).count() << " ";
	//cout << duration_cast<milliseconds>((stop1 - start1) + (stop2 - start2)).count() << "msec\n";

}


void test_vector(vector<int>& sequence){

	vector<int> test_vector;	
	runtest(sequence, test_vector);

	list<int> test_list;
	runtest(sequence, test_list);

	cout << '\n';

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
