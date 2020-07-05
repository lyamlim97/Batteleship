// player_class.h
// Lyam Lim Jin Sing 18/04/2020

#ifndef player_h
#define player_h

#include <string>

class player
{
private:
	std::string player_name{}; // Name of player
	int player_number{}; // Player number
public:
	player();
	player(std::string input_player_name, int input_player_number);
	player(const player& original_player);
	~player() {}; // Standard destructor, no dynamic memory
	player& operator=(const player& input);

	// Access functions
	std::string get_name();
	int get_player_number();
	// Edit functions
	void set_name(std::string input_name);
	void set_player_number(int input_player_number);
};
#endif /* player_h */
