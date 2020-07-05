// ships_class.h
// Lyam Lim Jin Sing 18/04/2020

#ifndef ships_class_h
#define ships_class_h

#include"constants.h"
#include <utility>
#include <string>

// Abstract base class of a ship
class ship
{
protected:
	int length{}; // Length of the ship
	std::pair<int, int> location; // Location of upper left most of the ship is
	char* ship_status; // Stores status of each square of the ship. Miss = O, Hit = X
	std::string type{}; // Indicates type of ship: Carrier, Battleship, Destroyer, Submarine, Patrol Boat
	bool is_afloat{}; // Boolean to identify if ship is afloat
	bool is_horizontal{}; // Boolean to identify is ship is placed horizontal or vertical
public:
	ship(int input_length, std::string input_type); // Default constructor
	ship(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal); // Parameterized constructor
	ship(const ship& original_ship); // Copy constructor
	~ship(); // Destructor
	ship& operator=(const ship& input); // Copy assignment operator

	// Accessor functions
	int get_length() const;
	std::string get_type() const;
	std::pair<int, int> get_location() const; // Return location
	int get_x() const; // Return x location
	int get_y() const; // Return y location
	bool is_ship_afloat();
	bool is_ship_horizontal() const;
	virtual int get_ammo_left() const = 0; // Overridden in derived classes
	virtual std::pair<int, int> get_attack_range() const = 0; // Overridden in derived classes
	
	// Edit functions
	void set_location(int input_x, int input_y, bool input_horizontal); // Set the location of the upper left most of the ship
	bool record_hit(int hit_x, int hit_y); // Record a hit on the corresponding square grid of the ship
	virtual void reduce_ammo() = 0; // Reduces the ammo of the ship after attack, overridden in derived classes
};

// CBDSP
// Derived classes for all ships
class carrier : public ship {
private:
	int no_of_general_ammo{ 15 };
	std::pair<int, int> attack_range{ 0,9 };
public:
	carrier();
	carrier(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal);
	int get_ammo_left() const;
	void reduce_ammo();
	std::pair<int, int> get_attack_range() const;
};

class battleship : public ship {
private:
	int no_of_long_range_ammo{ 25 };
	std::pair<int, int> attack_range{ 0,4 };
public:
	battleship();
	battleship(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal);
	int get_ammo_left() const;
	void reduce_ammo();
	std::pair<int, int> get_attack_range() const;
};

class destroyer :public ship {
private:
	int no_of__short_range_ammo{ 25 };
	std::pair<int, int> attack_range{ 5,9 };
public:
	destroyer();
	destroyer(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal);
	int get_ammo_left() const;
	void reduce_ammo();
	std::pair<int, int> get_attack_range() const;
};

class submarine :public ship {
private:
	int no_of_general_ammo{ 25 };
	std::pair<int, int> attack_range{ 0,9 };
public:
	submarine();
	submarine(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal);
	int get_ammo_left() const;
	void reduce_ammo();
	std::pair<int, int> get_attack_range() const;
};

class patrol_boat :public ship {
private:
	int no_of_very_short_range_ammo{ 10 };
	std::pair<int, int> attack_range{ 8,9 };
public:
	patrol_boat();
	patrol_boat(int input_length, std::pair<int, int> input_location, std::string input_type, bool input_afloat, bool input_horizontal);
	int get_ammo_left() const;
	void reduce_ammo();
	std::pair<int, int> get_attack_range() const;
};
#endif /* ships_class_h */
