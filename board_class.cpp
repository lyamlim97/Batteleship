// Lyam Lim Jin Sing 18/04/2020
// Implementation file for board_class.h

#include "board_class.h"
#include "ship_class.h"
#include <vector>
#include <iostream>

// Default constructor
board::board() {
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			board_matrix[i][j] = 'W';
}
// Copy constructor
board::board(const board& original_board) {
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			board_matrix[i][j] = original_board.board_matrix[i][j];
	ship_list = original_board.ship_list;
}
// Destructor
board::~board() {
	// No dynamically allocted memory
	return;
}
// Copy assignment operator
board& board::operator=(const board& input) {
	if (&input == this)
		return *this;
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			board_matrix[i][j] = input.board_matrix[i][j];
	ship_list = input.ship_list;
	return *this;
}
// Initiailise ship list
void board::initialize_ship_list() {
	ship_list.push_back(std::make_shared<carrier>());
	ship_list.push_back(std::make_shared<battleship>());
	ship_list.push_back(std::make_shared<destroyer>());
	ship_list.push_back(std::make_shared<submarine>());
	ship_list.push_back(std::make_shared<patrol_boat>());
}
// Access functions
int board::get_no_of_hits() const {
	return no_of_hits;
}
int board::get_no_of_moves() const {
	return no_of_moves;
}
// Function to print shadow board. Shadow board is the opponent's board but without displaying location of ships
void board::print_shadow_board() const {
	std::cout << "  A B C D E F G H I J\n";
	// For every row
	for (int i = 0; i < dimension; i++) {
		std::cout << i << " ";
		// For every column
		for (int j = 0; j < dimension; j++) {
			// Check char and apply colour
			switch (board_matrix[j][i])
			{
			case 'X':
				std::cout << "\033[38;5;160mX\033[0m" << " ";
				break;
			case 'O':
				std::cout << "\033[38;5;11mO\033[0m" << " ";
				break;
			default:
				std::cout << "\033[38;5;27m?\033[0m" << " ";
				break;
			}
		}
		std::cout << i << std::endl;
	}
	std::cout << "  A B C D E F G H I J\n";
}
void board::print_own_board() const {
	std::cout << "  A B C D E F G H I J\n";
	// For every row
	for (int i = 0; i < dimension; i++) {
		std::cout << i << " ";
		// For every column
		for (int j = 0; j < dimension; j++) {
			// Check char and apply colour
			switch (board_matrix[j][i])
			{
			case 'W':
				std::cout << "\033[38;5;27mW\033[0m" << " ";
				break;
			case 'X':
				std::cout << "\033[38;5;160mX\033[0m" << " ";
				break;
			case 'O':
				std::cout << "\033[38;5;11mO\033[0m" << " ";
				break;
			case 'C':
				std::cout << "\033[38;5;34mC\033[0m" << " ";
				break;
			case 'B':
				std::cout << "\033[38;5;40mB\033[0m" << " ";
				break;
			case 'D':
				std::cout << "\033[38;5;46mD\033[0m" << " ";
				break;
			case 'S':
				std::cout << "\033[38;5;106mS\033[0m" << " ";
				break;
			case 'P':
				std::cout << "\033[38;5;118mP\033[0m" << " ";
				break;
			default:
				std::cout << "\033[38;5;106mQ\033[0m" << " "; // Should not get here
				break;
			}
		}
		std::cout << i << std::endl;
	}
	std::cout << "  A B C D E F G H I J\n";
}

char board::get_location_status(int input_x, int input_y) const {
	return board_matrix[input_x][input_y];
}
bool board::record_hit(int input_x, int input_y) {
	for (int i = 0; i < no_of_ships; i++)
	{
		// Try to hit all ships
		// Should only match one ship
		if (ship_list[i]->record_hit(input_x, input_y))
		{	// Tell player if attack was a hit or miss
			std::cout << "Attack was a hit.\n";
			board_matrix[input_x][input_y] = 'X'; // Record hit on board
			no_of_hits++;
			// Check if ship has been sunk
			if (!ship_list[i]->is_ship_afloat())
				std::cout << "You have sunk your oppenent's " << ship_list[i]->get_type() << "!\n\n";
			return true;
		}
	}
	no_of_moves++;
	std::cout << "Attack was a miss.\n";

	board_matrix[input_x][input_y] = 'O';
	return false;
}
bool board::place_ship(const int input_ship_no, int input_x, int input_y, bool input_horizontal) {

	// Return false if x or y is out of bounds
	if ((input_x >= dimension) || (input_y >= dimension)) {
		std::cout << "Invalid space. Please try again.\n";
		return false;
	}

	// Return false if ship already been placed
	if (ship_list[input_ship_no]->get_x() >= 0 && ship_list[input_ship_no]->get_y() >= 0) {
		std::cout << "Ship has already been placed.\n";
		return false;
	}

	// Return false if any of the wanted spaces are out of bounds
	if ((input_horizontal && (input_x + ship_list[input_ship_no]->get_length()) > dimension) || (!input_horizontal && (input_y + ship_list[input_ship_no]->get_length()) > dimension)) {
		std::cout << "Invalid space. Please try again.\n";
		return false;
	}
	else {
		// Not out of the board, so check all spaces are available
		for (int i = 0; i < ship_list[input_ship_no]->get_length(); i++)
		{	// Return false if any of the wanted spaces filled
			// About the warning here, code should never run past the board array as we have already checked that it is not trying to place part of the ship outside
			if ((input_horizontal && board_matrix[input_x + i][input_y] != 'W') || (!input_horizontal && board_matrix[input_x][input_y + i] != 'W')) {
				std::cout << "Invalid space. Please try again.\n";
				return false;
			}

		}
	}
	// Gets here if all wanted spaces are available
	// Place the ship in the wanted space
	for (int i = 0; i < ship_list[input_ship_no]->get_length(); i++)
	{	// Assign character depending on the ship
		char ship_char{};
		switch (input_ship_no)
		{
		case 0:
			ship_char = 'C';
			break;
		case 1:
			ship_char = 'B';
			break;
		case 2:
			ship_char = 'D';
			break;
		case 3:
			ship_char = 'S';
			break;
		case 4:
			ship_char = 'P';
			break;
		default:
			ship_char = 'Q'; // Should not get here
			break;
		}
		// About the warning here, code should never run past the board array as the ship has already confirmed to be within the board
		if (input_horizontal)
			board_matrix[input_x + i][input_y] = ship_char;
		else
			board_matrix[input_x][input_y + i] = ship_char;
	}
	// Set the location for the ship
	ship_list[input_ship_no]->set_location(input_x, input_y, input_horizontal);
	// Return true to indicate ship has been placed successfully
	return true;
}

bool board::check_if_ship_afloat(int ship_no) const {
	bool is_afloat;
	is_afloat = ship_list[ship_no]->is_ship_afloat();
	return is_afloat;
}
int board::check_ammo_left(int ship_no) const {
	int ammo_left;
	ammo_left = ship_list[ship_no]->get_ammo_left();
	return ammo_left;
}

void board::reduce_ammo_of_ship(const int ship_no) {
	ship_list[ship_no]->reduce_ammo();
}

std::pair <int, int> board::get_attack_range(int ship_no) const {
	std::pair<int, int> attack_range;
	attack_range = ship_list[ship_no]->get_attack_range();
	return attack_range;
}
void board::update_previous_move(std::string input_move) {
	previous_move = input_move;
}
void board::print_previous_move() const {
	std::cout << "Your previous move was : " << previous_move << std::endl;
}
void board::print_ship_status() const {
	std::string is_afloat{};

	std::cout << "     Ship     |   Status   | Ammo \n";
	std::cout << "---------------------------------\n";
	for (int i = 0; i < no_of_ships; i++) {
		if (ship_list[i]->is_ship_afloat())
			is_afloat = "Afloat";
		else
			is_afloat = "Sunk";
		std::cout << "" << add_spaces(14, ship_names[i]) << "|" << add_spaces(12, is_afloat) << "|" << add_spaces(6, ship_list[i]->get_ammo_left()) << std::endl;
	}
}