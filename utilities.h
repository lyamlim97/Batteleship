// utilities.h
// utilities

// Lyam Lim Jin Sing 18/04/2020
#include <string>

#ifndef utilities_h
#define utilities_h

// Function to check if integer is a number (only positive integers)
bool positive_int_check(std::string input_string);
// Function to check if entire string is white space
bool all_space_check(std::string input_string);
// Function to input a string with a maximum length (inclusive)Fa
std::string get_string(size_t max_length);
// Function to input a positive integer within a certain range (inclusive)
int get_int(int min_val, int max_val);
// Function to add spaces to a string untill it reaches a specified length
std::string add_spaces(size_t final_length, std::string input_string);
// Function to add spaces to an integer untill it reaches a specified length, return a string
std::string add_spaces(size_t final_length, int input_number);

#endif /* utilities_h */
