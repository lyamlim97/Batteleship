// Lyam Lim Jin Sing 18/04/2020
// Implementation file for player_class.h

#include "player_class.h"
#include <iostream>

// Default constructor
player::player() {
	player_name = "";
	player_number = -1;
};
// Parameterized constructor
player::player(std::string input_player_name, int input_player_number) {
	player_name = input_player_name;
	player_number = input_player_number;
}
// Copy constructor
player::player(const player& original_player) {
	player_name = original_player.player_name;
	player_number = original_player.player_number;
}
// Copy assignment operator
player& player::operator=(const player& input) {
	// No self assignment
	if (&input == this)
		return *this;
	player_name = input.player_name;
	player_number = input.player_number;
	return *this;
}
// Access functions
std::string player::get_name() {
	return player_name;
}
int player::get_player_number() {
	return player_number;
}
void player::set_name(std::string input_name) {
	player_name = input_name;
}
void player::set_player_number(int input_player_number) {
	player_number = input_player_number;
}