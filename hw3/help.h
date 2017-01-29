#ifndef HELP_H
#define HELP_H

#include <string>
#include <vector>

bool is_int(const std::string& N);
std::vector<int> generate_random_sequence(int n);
bool cmd_args_good(int argc, char **argv);
void test_vector(std::vector<int>& sequence);
void test_list(std::vector<int>& sequence);
//void runtest(std::vector<int>& sequence, std::vector<int>& test_vector);

#endif
