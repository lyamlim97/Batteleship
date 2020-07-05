// Lyam Lim Jin Sing 18/04/2020
// Implementation file for utilities.h

#include "utilities.h"
#include <iostream>

bool positive_int_check(std::string input_string) {
	return input_string.find_first_not_of("0123456789") == std::string::npos; // Returns true if positive integer
}

bool all_space_check(std::string input_string) {
	return input_string.find_first_not_of(' ') == std::string::npos; // Returns true if string is all spaces
}

std::string get_string(size_t max_length) {
	std::string input_string;
	std::getline(std::cin, input_string);

	// Check if more than max length
	while (input_string.length() > max_length) {
		std::cout << "String is too long. Please enter a string with less than " << max_length << " characters.\n";
		std::cout << "Please enter again: ";
		std::getline(std::cin, input_string);
	}
	return input_string;
}

int get_int(int min_val, int max_val) {
	std::string input_string;
	bool input_pass{ false };
	bool is_negative{ false };
	int temp_int{};
	
	do {
		std::getline(std::cin, input_string);

		if (all_space_check(input_string)){ // Check if input is empty
			std::cerr << "Input is empty. Please reenter: ";
		}
		else if (!positive_int_check(input_string)) { // Check if input is a positive integer
			std::cerr << "Input is not a positive integer. Please reenter: ";
		}
		else if (std::stoi(input_string) > max_val || std::stoi(input_string) < min_val) {
			std::cerr << "Input is not within specified range. Please reenter: ";
		}
		else {
			std::cout << "Accepted.\n";
			input_pass = true;
		}
	} while (!input_pass);

	temp_int = std::stoi(input_string);
	return temp_int;
}

std::string add_spaces(size_t final_length, std::string input_string) {
	std::string new_string{ input_string };
	int counter{ 0 };
	while (new_string.length() < final_length) {
		
		if (counter % 2 > 0) {
			new_string = ' ' + new_string;
		}
		else {
			new_string = new_string + ' ';
		}
		counter++;
	}
	return new_string;
}

std::string add_spaces(size_t final_length, int input_number) {
	std::string new_string{ std::to_string(input_number) };
	int counter{ 0 };
	while (new_string.length() < final_length) {

		if (counter % 2 > 0) {
			new_string = ' ' + new_string;
		}
		else {
			new_string = new_string + ' ';
		}
		counter++;
	}
	return new_string;
}