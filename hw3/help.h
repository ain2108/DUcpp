#ifndef HELP_H
#define HELP_H

#include <string>
#include <vector>

/* Input parsing */
bool is_int(const std::string& N);
bool cmd_args_good(int argc, char **argv);

/* Random sequence generation */
std::vector<int> generate_random_sequence(int n);

/* Testing */
void test_vector(std::vector<int>& sequence);
void test_list(std::vector<int>& sequence);
void test_map(std::vector<int>& sequence);
void test(std::vector<int>& sequence);

//void runtest(std::vector<int>& sequence, std::vector<int>& test_vector);

#endif
