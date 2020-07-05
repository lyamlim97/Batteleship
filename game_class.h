// game_class.h
// Lyam Lim Jin Sing 18/04/2020

#ifndef game_h
#define game_h

#include "player_class.h"
#include "board_class.h"

// Enum for game states
enum class game_state { player_1_win, player_2_win, ongoing, draw };

class game
{
private:
	player player_1;
	player player_2;
	board board_1;
	board board_2;
	game_state current_game_state{ game_state::ongoing }; // Current game state
	std::vector<bool> ship_valid_move_possible{}; // Indicates for each ship whether a valid move is possible
	int ship_valid_move_counter{ 0 }; // Indicates how many ships have a valid move. If it is zero, means no valid move.
public:
	game() {}; // Constructor
	~game() {}; // Destructor

	// Accessor functions
	std::pair<int, int> get_range(int ship_no, board& attacking_board) const; // Returns range of ship
	std::string get_location() const; // Return location
	game_state get_game_state(); // Return game state
	bool check_if_valid_move_possible(board& attacking_board, board& attacked_on_board, const int input_ship_no); // Check if a ship can perform a valid attack
	bool afloat_and_ammo_check(const int ship_no, board& input_board); // Check if the ship has ammo and is afloat

	// Edit fucntions
	void initialize_board(board &input_board); // Set up the board for a player
	void print_game_state(player& attacking_player, board& attacking_board, board& attacked_on_board); // Calls the board printing functions of board class
	void get_next_move(board &attacked_on_board, board& attacking_board); // Asks the user for a ship and location to attack
	void reduce_ammo_after_attack(const int ship_no, board& input_board); // Reduce ammo of the ship

	// Other
	bool play_game(); // Start an instance of the game
	void end_turn(std::string player_from) const; // Function to comfirm the end of the player's turn and print out empty rows to prevent accidental cheating
	void new_turn(std::string player_to) const; // Function to confirm the start of the player's turn and print out empty rows to prevent accidental cheating
};
#endif /* game_h */
