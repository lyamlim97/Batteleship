// Lyam Lim Jin Sing 18/04/2020
// Implementation file for ship_class.h


#include "ship_class.h"
#include <utility>
#include <iostream>
#include <string>
#include <string>

// Default constructor
ship::ship(int input_length, std::string input_type) {
	length = input_length;
	type = input_type;
	ship_status = new char[length];
	for (int i = 0; i < length; i++)
		ship_status[i] = 'S';
	location.first = -1; // -1 indicates ship has not been placed yet
	location.second = -1; // -1 indicates ship has not been placed yet
	is_afloat = true;
	is_horizontal = true;
}
// Parameterized constuctor
ship::ship(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal) {
	length = input_length;
	location = input_location;
	ship_status = new char[length];
	for (int i = 0; i < length; i++)
		ship_status[i] = 'S'; // Initialize all squares of the ship to miss
	type = input_type;
	is_afloat = input_afloat;
	is_horizontal = input_horizontal;
};
// Copy constructor
ship::ship(const ship& original_ship) {
	length = original_ship.length;
	location = original_ship.location;
	ship_status = new char[length];
	for (int i = 0; i < length; i++)
		ship_status[i] = original_ship.ship_status[i];
	type = original_ship.type;
	is_afloat = original_ship.is_afloat;
	is_horizontal = original_ship.is_horizontal;
}
// Destructor 
ship::~ship() {
	// Clear dynamic memory
	delete[] ship_status;
}
// Copy assignment operator
ship& ship::operator=(const ship& input) {
	// No self assignment
	if (&input == this)
		return *this;
	length = input.length;
	location = input.location;
	delete[] ship_status;
	ship_status = 0;
	if (length > 0) {
		ship_status = new char[length];
		for (int i = 0; i < length; i++)
			ship_status[i] = input.ship_status[i];
	}
	return *this;
}
// Access functions
// Return length of a ship
int ship::get_length() const {
	return length;
}
// Return type of a ship
std::string ship::get_type() const {
	return type;
}
// Return location of a ship
std::pair<int, int> ship::get_location() const {
	return location;
}
// Return x location of ship
int ship::get_x() const {
	return location.first;
}
// Return y location of ship
int ship::get_y() const {
	return location.second;
}
// Return whether ship is afloat or not
bool ship::is_ship_afloat() {
	for (int i = 0; i < length; i++)
		if (ship_status[i] == 'S') {
			is_afloat = true;
			return is_afloat;
		}
	is_afloat = false;
	return is_afloat;
}
// Return whether ship is placed horizontally or not
bool ship::is_ship_horizontal() const {
	return is_horizontal;
}
// Edit functions
void ship::set_location(int input_x, int input_y, bool input_horizontal) {
	location.first = input_x;
	location.second = input_y;
	is_horizontal = input_horizontal;
	return;
}
bool ship::record_hit(int hit_x, int hit_y) {
	// Check if the hit missed
	if ((is_horizontal && (hit_x < location.first || hit_x >= location.first + length || hit_y != location.second)) 
		|| (!is_horizontal && (hit_y < location.second || hit_y >= location.second + length || hit_x != location.first)))
		return false;
	else 
	{	// Record the hit
		if (is_horizontal)
			ship_status[hit_x - location.first] = 'X';
		else
			ship_status[hit_y - location.second] = 'X';		
	}
	// Check if ship is still afloat
	is_afloat = false;
	for (int i = 0; i < length; i++)
		if (ship_status[i] == 'S')
			is_afloat = true;

	return true;
}

// Derived classes
carrier::carrier() : ship(5, "Carrier") {}
carrier::carrier(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal)
	: ship(5, input_location, "Carrier", true, input_horizontal) {}
int carrier::get_ammo_left() const {
	return no_of_general_ammo;
}
void carrier::reduce_ammo() {
	no_of_general_ammo--;
}
std::pair<int, int> carrier::get_attack_range() const {
	return attack_range;
}


battleship::battleship() : ship(4, "Battleship") {}
battleship::battleship(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal)
	: ship(4, input_location, "Battleship", true, input_horizontal) {}
int battleship::get_ammo_left() const {
	return no_of_long_range_ammo;
}
void battleship::reduce_ammo() {
	no_of_long_range_ammo--;
}
std::pair<int, int> battleship::get_attack_range() const {
	return attack_range;
}

destroyer::destroyer() : ship(3, "Destroyer") {}
destroyer::destroyer(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal)
	: ship(3, input_location, "Destroyer", true, input_horizontal) {}
int destroyer::get_ammo_left() const {
	return no_of__short_range_ammo;
}
void destroyer::reduce_ammo() {
	no_of__short_range_ammo--;
}
std::pair<int, int> destroyer::get_attack_range() const {
	return attack_range;
}

submarine::submarine() : ship(3, "Submarine") {}
submarine::submarine(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal)
	: ship(3, input_location, "Submarine", true, input_horizontal) {}
int submarine::get_ammo_left() const {
	return no_of_general_ammo;
}
void submarine::reduce_ammo() {
	no_of_general_ammo--;
}
std::pair<int, int> submarine::get_attack_range() const {
	return attack_range;
}

patrol_boat::patrol_boat() : ship(2, "Patrol Boat") {}
patrol_boat::patrol_boat(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal)
	: ship(2, input_location, "Patrol Boat", true, input_horizontal) {}
int patrol_boat::get_ammo_left() const {
	return no_of_very_short_range_ammo;
}
void patrol_boat::reduce_ammo() {
	no_of_very_short_range_ammo--;
}
std::pair<int, int> patrol_boat::get_attack_range() const {
	return attack_range;
}

