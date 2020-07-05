// board_class.h
// Lyam Lim Jin Sing 18/04/2020

#ifndef board_h
#define board_h

#include "ship_class.h"
#include "constants.h"
#include "player_class.h"
#include "utilities.h"
#include <vector>
#include <string>
#include <memory>

class board
{
private:
	char board_matrix[10][10]{ }; // Board, Water = W, Hit = X, Miss = O
	std::vector<std::shared_ptr<ship>> ship_list; // List of ships in play during the game
	int no_of_hits{ 0 }; // Tracks the no of hits
	int no_of_moves{ 0 }; // Tracks the no of moves
	std::string previous_move{ "No previous move" }; // Stores the previous move
public:
	board(); // Constructor
	board(const board& original_board); // Copy Constructor
	~board(); // Destructor
	board& operator=(const board& input); // Copy assignment operator

	// Accessor functions
	int get_no_of_hits() const;
	int get_no_of_moves() const;
	void print_shadow_board() const; // Displays the board but does not show the locations of the ships. Used to show the player's board during the opponet's turn
	void print_own_board() const; // Displays the board and shows everything on the board. Used to show the player his own board during his turn
	char get_location_status(int input_x, int input_y) const;
	bool check_if_ship_afloat(int ship_no) const;
	int check_ammo_left(int ship_no) const;
	std::pair <int, int> get_attack_range(int ship_no) const;
	void print_previous_move() const;
	void print_ship_status() const; // Displays the ships name, status (aflaot or sunk) and ammo

	// Edit functions
	void initialize_ship_list(); // Initializes the vector of ships with one of each ship
	bool record_hit(int input_x, int input_y); // Records a hit on the corresponding square grid on the board
	bool place_ship(const int input_ship_no, int input_x, int input_y, bool input_horizontal); // Marks the location of the ships on the board
	void reduce_ammo_of_ship(const int ship_no);
	void update_previous_move(std::string input_move);
};
#endif /* board_h */
