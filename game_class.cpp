// Lyam Lim Jin Sing 18/04/2020
// Implementation file for game_class.h

#include "game_class.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>


// Start an instance of the game
bool game::play_game() {

	int first_player;

	std::unique_ptr<player> player_attacked_on_pointer;
	std::unique_ptr<board> board_attacked_on_pointer;
	std::unique_ptr<player> player_attacking_pointer;
	std::unique_ptr<board> board_attacking_pointer;
	std::string play_again_string;

	// Get players name
	std::string temp_name;

	// Set player number
	player_1.set_player_number(1);
	player_2.set_player_number(2);
	// Obtain player names from input
	std::cout << "Please enter Player 1's name (max 32 characters): ";
	do {
		std::cerr << "Input is empty. Please reenter: ";
		player_1.set_name(get_string(32));
	} while (all_space_check(player_1.get_name()));
	std::cout << "Welcome, " << player_1.get_name() << std::endl;

	std::cout << "Please enter Player 2's name (max 32 characters): ";
	do {
		std::cerr << "Input is empty. Please reenter: ";
		player_2.set_name(get_string(32));
	} while (all_space_check(player_2.get_name()));	
	std::cout << "Welcome, " << player_2.get_name() << std::endl;

	// Initialize boards
	std::cout << "Setting up board for Player 1: " << player_1.get_name() << std::endl;
	initialize_board(board_1);
	std::cout << "Setting up board for Player 2: " << player_2.get_name() << std::endl;
	initialize_board(board_2);

	// Determine which player make the first move
	std::cout << "Which player will make the first move (1 or 2)?\n";
	first_player = get_int(1, 2); // Can only be 1 or 2

	// Hold pointers for the current player and board
	if (first_player == 1) {
		player_attacked_on_pointer = std::make_unique<player>(player_2);
		player_attacking_pointer = std::make_unique<player>(player_1);
		board_attacked_on_pointer = std::make_unique<board>(board_2);
		board_attacking_pointer = std::make_unique<board>(board_1);
	}
	else {
		player_attacked_on_pointer = std::make_unique<player>(player_1);
		player_attacking_pointer = std::make_unique<player>(player_2);
		board_attacked_on_pointer = std::make_unique<board>(board_1);
		board_attacking_pointer = std::make_unique<board>(board_2);
	}
	
	// For the first turn, set all to true
	for (int i = 0; i < no_of_ships; i++) {
		ship_valid_move_possible.push_back(true);
	}

	// Main game loop
	do{
		// Start player's turn
		new_turn(player_attacking_pointer->get_name());
		print_game_state(*player_attacking_pointer, *board_attacking_pointer, *board_attacked_on_pointer);
		board_attacking_pointer->print_ship_status();
		board_attacking_pointer->print_previous_move();
		get_next_move(*board_attacked_on_pointer, *board_attacking_pointer);
		print_game_state(*player_attacking_pointer, *board_attacking_pointer, *board_attacked_on_pointer);
		end_turn(player_attacking_pointer->get_name());
		
		// Check if player has won after his latest move
		if (get_game_state() == game_state::player_1_win) {
			std::cout << "Congratualations " << player_1.get_name() << "! You have won the game.\n";
			std::cout << "You won after " << board_2.get_no_of_moves() << " moves.\n";
			return 1;
		}
		else if (get_game_state() == game_state::player_2_win) {
			std::cout << "Congratualations " << player_2.get_name() << "! You have won the game.\n";
			std::cout << "You won after " << board_1.get_no_of_moves() << " moves.\n";
			return 1;
		}
	
		// Noone has won
		// Switch player and board pointers
		swap(player_attacked_on_pointer, player_attacking_pointer);
		swap(board_attacked_on_pointer, board_attacking_pointer);

		// Check if next player has a valid attack
		for (int i = 0; i < no_of_ships; i++) {
			// Check ammo and afloat
			if (afloat_and_ammo_check(i, *board_attacking_pointer)) {
				// Check if valid move possible
				if (check_if_valid_move_possible(*board_attacking_pointer, *board_attacked_on_pointer, i)) {
					ship_valid_move_possible[i] = true;
					ship_valid_move_counter++;
				}
				else {
					ship_valid_move_possible[i] = false;
				}
			}
		}
		// Game ends if there is no possible move for player
		if (ship_valid_move_counter == 0) {
			// Compare the no of successful hits between the players. The player with the most successfull hits wins.

			// board_1 has more hits than board_2, so player_2 wins
			if (board_1.get_no_of_hits() > board_2.get_no_of_hits()) {
				current_game_state = game_state::player_2_win;
				std::cout << "Congratualations " << player_2.get_name() << "! You have won the game by default as " << player_1.get_name() << " does not have any more moves possible and you have more successful hits.\n";
				std::cout << "You won with " << board_1.get_no_of_hits() << " hits compared to your opponent's " << board_2.get_no_of_hits() << " hits.\n";
			}
			// board_2 has more hits than board_1, so player_1 wins
			else if (board_2.get_no_of_hits() > board_1.get_no_of_hits()) {
				current_game_state = game_state::player_1_win;
				std::cout << "Congratualations " << player_1.get_name() << "! You have won the game by default as " << player_2.get_name() << " does not have any more moves possible and you have more successful hits.\n";
				std::cout << "You won with " << board_2.get_no_of_hits() << " hits compared to your opponent's " << board_1.get_no_of_hits() << " hits.\n";
			}
			// No of hits are equal
			else {
				current_game_state = game_state::draw;
				std::cout << "The game has ended in a draw as " << player_attacking_pointer->get_name() << " has no more possible moves and both players has an equal amount of successful hits(" 
					<< board_attacking_pointer->get_no_of_hits() << ").\n";
			}
		}
	} while ((game::get_game_state() == game_state::ongoing));
	return 0;
}
// Check if selected ship has a valid move
bool game::check_if_valid_move_possible(board& attacking_board, board& attacked_on_board, const int input_ship_no) {
	std::pair<int, int> ship_attacking_range{ attacking_board.get_attack_range(input_ship_no) };

	// Ship is afloat and has ammo as previously checked
	// Check whether selected ship has a valid move
	// For each row within ship's range
	for (int i = ship_attacking_range.first; i <= ship_attacking_range.second; i++) {
		// For each column
		for (int j = 0; j < dimension; j++) {
			// Check each char of attacked_on_board
			// If any is W or S, that means there is a valid attack possible
			if ((attacked_on_board.get_location_status(j, i) == 'W') || (attacked_on_board.get_location_status(j, i) == 'S')) {
				return true;
			}
		}
	}
	return false;
}

// Initilize board from user input
void game::initialize_board(board& input_board) {
	int input_x{};
	int	input_y{};
	int ship_counter{};
	bool is_input_horizontal{false};
	bool location_valid{false};
	std::string temp_entry;
	std::string temp_horizontal;

	// Call initialize ship list here
	input_board.initialize_ship_list();

	for (int i = 0; i < no_of_ships; i++) { // Do for each ship
		location_valid = false;

		do { // Check if each ship is placed in valid position
			input_board.print_own_board();
			std::cout << "Please enter position [Letter][Number] for the upper left most of your " << ship_names[i] << " that has length " << ship_lengths[i] << ":\n";
			temp_entry = get_location();
			// Accepted input location
			input_x = temp_entry[0] - 65;
			input_y = temp_entry[1] - 48;

			std::cout << "Please enter if ship is oriented horizontally (H) or vertically (V).\n";
			do { // Ask if ship is orientated horizontally or vertically
				temp_horizontal = get_string(1);
				// Input is correct size
				if (temp_horizontal == "H") {
					is_input_horizontal = true;
					location_valid = true;
				}
				else if (temp_horizontal == "V") {
					is_input_horizontal = false;
					location_valid = true;
				}
				else {
					location_valid = false;
					std::cout << "Please enter a valid input.\n";
				}
			} while (!location_valid);
		} while(!input_board.place_ship(i, input_x, input_y, is_input_horizontal));
	}

	std::cout << "This is your starting board:\n";
	input_board.print_own_board();
	std::cout << "Press ENTER to continue.";
	std::cin.get();
	std::cout << std::flush;
	std::cout << std::string(100, '\n');
	return;
}
// Returns enum stating state of game
game_state game::get_game_state() {
	// All ships on board_1 sunk, so player_2 wins
	if (board_1.get_no_of_hits() == 17) {
		current_game_state = game_state::player_2_win;
	}
	// All ships on board_2 sunk, so player_1 wins
	else if (board_2.get_no_of_hits() == 17) {
		current_game_state = game_state::player_1_win;
	}
	// Noone has won, game is still ongoing
	else {
		current_game_state = game_state::ongoing;
	}
	return current_game_state;
}
// Print game state, showing player's board (ships exposed) and opponent's board (ships hidden)
void game::print_game_state(player& attacking_player, board& attacking_board, board& attacked_on_board) {
	std::cout << attacking_player.get_name() << "'s current game state:\n\n";
	std::cout << "Your opponent's board:\n";
	attacked_on_board.print_shadow_board();
	std::cout << "Your board:\n";
	attacking_board.print_own_board();
	std::cout << "\n\n";
	return;
}

// Check ship if it is afloat and has ammo
bool game::afloat_and_ammo_check(const int ship_no, board& input_board){
	// Check if afloat
	if (input_board.check_if_ship_afloat(ship_no)) {
		// Check ammo
		if (input_board.check_ammo_left(ship_no) > 0)
			return  true;
		// No ammo
		else {
			return false;
		}
	}
	// Not afloat
	else {
		return  false;
	}
}
// Reduce ship ammo by 1
void game::reduce_ammo_after_attack(const int ship_no, board& input_board) {
	input_board.reduce_ammo_of_ship(ship_no);
}
// Get the attack range of ship
std::pair<int, int> game::get_range(int ship_no, board& attacking_board) const {
	std::pair<int,int> attack_range;
	attack_range = attacking_board.get_attack_range(ship_no);
	return attack_range;
}
// Get player's next move to fire
void game::get_next_move(board& attacked_on_board, board& attacking_board) {

	int input_x{};
	int input_y{};
	bool is_move_valid{ false };
	bool attacking_ship_valid{ false };
	bool ship_option_valid{ false };
	std::string temp_string{};
	std::pair<int, int> attack_range{};
	int ship_no{-1};
	
	std::cout << "Please enter the ship you would like to fire with. C - Carrier, B - Battleship, D - Destroyer, S - Submarine, P - Patrol Boat\n";
	do {
		temp_string = get_string(1);

		// Check if valid ship
		switch (temp_string[0])
		{
		case 'C':
			std::cout << "You have selected the Carrier to attack with.\n";
			ship_no = 0;
			ship_option_valid = true;
			break;

		case 'B':
			std::cout << "You have selected the Battleship to attack with.\n";
			ship_no = 1;
			ship_option_valid = true;
			break;

		case 'D':
			std::cout << "You have selected the Destroyer to attack with.\n";
			ship_no = 2;
			ship_option_valid = true;
			break;

		case 'S':
			std::cout << "You have selected the Submarine to attack with.\n";
			ship_no = 3;
			ship_option_valid = true;
			break;

		case 'P':
			std::cout << "You have selected the Patrol Boat to attack with.\n";
			ship_no = 4;
			ship_option_valid = true;
			break;

		default:
			std::cout << "You have entered an invalid ship. Please renter.\n";
			ship_option_valid = false;
			break;
		}

		if ((ship_no <= 4) && (ship_no >= 0)) {
			if (ship_valid_move_possible[ship_no]) {
				attacking_ship_valid = true;
			}
			else {
				attacking_ship_valid = false;
				std::cout << "The ship you have selected is either not afloat, has no ammo or does not have a possible move.\n";
				std::cout << "Please select another ship.\n";
			}
		}
		
		// Loop again if not afloat or has no ammo or has no valid attack
	} while ((!attacking_ship_valid) || (!ship_option_valid));

	// Ship selected and approved
	// Get attack location now
	std::cout << "Please enter location you want to fire.\n";
	do {
		// Check location is valid on the board
		temp_string = get_location();
			
		input_x = temp_string[0] - 65;
		input_y = temp_string[1] - 48;

		// Check location is within the range for the ships
		// Range is defined as how many rows from the bottom that ship can attack
		attack_range = get_range(ship_no,attacking_board);

		// Check input location is within max and min of range inclusive
		if ((input_y >= attack_range.first) && (input_y <= attack_range.second)) {
			// Range check pass
			// Check if location has already been fired on
			if ((attacked_on_board.get_location_status(input_x, input_y)) != 'X' && (attacked_on_board.get_location_status(input_x, input_y) != 'O')) {
				// Location valid
				// Record move to show player on next move
				attacking_board.update_previous_move(temp_string);
				// Reduce ammo
				attacking_board.reduce_ammo_of_ship(ship_no);
				attacked_on_board.record_hit(input_x, input_y);
				is_move_valid = true;
			}
			else if (input_x >= dimension || input_y >= dimension) {
				std::cout << "Invalid space. Please try again.\n";
			}
			else {
				std::cout << "Location has already been fired on.\n";
			}
		}
		else {
			std::cout << "Location out of range of ship. Please try again.\n";
		}
	} while (!is_move_valid);
	return;
}
// Get location input and validate
std::string game::get_location() const {
	std::string input_string;
	bool is_location_valid{false};
	do {
		std::getline(std::cin, input_string);
		std::string x_location;
		std::string y_location;

		// Only split it up if more than 2 chars long due to error if its empty space
		if (input_string.length() >= 2) {
			x_location = input_string.substr(0, 1);
			y_location = input_string.substr(1, 1);
		}

		if (all_space_check(input_string)){ // Check if input is empty
			std::cerr << "Input is empty. Please reenter: ";
		}
		else if (input_string.length() != 2) { // CHeck if correct length
			std::cerr << "Input is not of correct format. Please reenter: ";
		}
		else if (!(x_location.find_first_not_of("ABCDEFGHIJ")== std::string::npos)||!(y_location.find_first_not_of("0123456789") == std::string::npos)) {
			std::cerr << "Input is not of correct format. Please reenter: ";
		}
		else {
			std::cout << "Accepted.\n";
			is_location_valid = true;
		}
	} while (!is_location_valid);

	return input_string;
}

// Ends a player's turn
void game::end_turn(std::string player_from) const {
	std::cout << player_from << ", press ENTER to end your turn.";
	std::cin.get();
	std::cout << std::flush;
	std::cout << std::string(100, '\n');
	return;
}

// Starts a new turn
void game::new_turn(std::string player_to) const {
	std::cout << player_to << ", press ENTER to start your turn.";
	std::cin.get();
	std::cout << std::flush;
	std::cout << std::string(100, '\n');
	return;
}