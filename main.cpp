// Lyam Lim Jin Sing 18/04/2020
// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <functional>
#include <utility>

// Classes defined in header files
#include "player_class.h"
#include "board_class.h"
#include "game_class.h"
#include "constants.h"
#include "utilities.h"

int main()
{
	game current_game;
	std::string play_or_exit_string;
	bool play_or_exit{ true }; // True represents play, false represents exit
	bool play_or_exit_input_valid{ false }; // Check if its a valid input
	std::string play_again_string{};
	bool play_again_input_valid{ false }; // Check if its a valid input

	std::cout << "Welcome to Battlship.\n";
	std::cout << "In this version of the game, ships have a limited range and limited ammo.\n\n";
	std::cout << "There are 5 ships: Carrier, Battleship, Destroyer, Submarine and Patrol Boat.\n";
	std::cout << "    Ship     |     Range     | Ammo\n";
	std::cout << "------------------------------------\n";
	std::cout << "   Carrier   |  rows 0 to 9  | 15\n";
	std::cout << "  Battleship |  rows 0 to 4  | 25\n";
	std::cout << "  Destroyer  |  rows 5 to 9  | 25\n";
	std::cout << "  Submarine  |  rows 0 to 9  | 25\n";
	std::cout << " Patrol Boat |  rows 8 to 9  | 10\n\n";
	std::cout << "During your turn, you would be asked to choose a ship to attack with.\n";
	std::cout << "After that, you will choose the location you wish to fire on.\n";
	std::cout << "If any of your ships have been sunk, you will not be able to use them to attack.\n";
	std::cout << "Likewise, if a ship has ran out of ammo, you will not be able to use it to attack.\n\n";
	std::cout << "Enter 'P' to play or 'E' to exit: ";

	play_or_exit_string = get_string(1); // Get P or E
	do {
		if (play_or_exit_string[0] == 'P') {
			play_or_exit_input_valid = true;
			play_or_exit = true;
		}
		else if (play_or_exit_string[0] == 'E') {
			play_or_exit_input_valid = true;
			play_or_exit = false;
			std::cout << "Bye.\n";
		}
		else {
			std::cout << "Invalid input. Please enter 'P' to play or 'E' to exit.\n";
			play_or_exit_string = get_string(1);
		}
	} while (!play_or_exit_input_valid);

	while (play_or_exit)
	{
		current_game.play_game();

		// Ask if player wants to play again
		std::cout << "Would you like to play the game again? Enter 'Y' to play again or 'N' to exit.\n";
		play_again_string = get_string(1);
		do {
			if (play_again_string[0] == 'Y') {
				play_again_input_valid = true;
				play_or_exit = true;
			}
			else if (play_again_string[0] == 'N') {
				play_again_input_valid = true;
				play_or_exit = false;
				std::cout << "Thank you for playing. I hope you enjoyed it.\n";
			}
			else {
				std::cout << "Invalid input. Please enter 'Y' to play again or 'N' to exit.\n";
				play_again_string = get_string(1);
			}
		} while (!play_again_input_valid);
	}

	return 1;
}
