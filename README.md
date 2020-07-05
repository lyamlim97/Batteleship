# Battleship

Implementation of Battleship in C++ as the final project for a 3rd year university module "Object-Oriented Programming in C++". I also added my own modifications to the game. 

## Game Structure
### Traditional Game
The game is played on square grids of dimensions 10 by 10.
Columns are indicated by a letter and rows by a number.
Each player has two boards of square grids.
The first is for each player to place their ships and keep track of opponent's shots.
The ships can only be place horizontally and vertically and cannot overlap.
The second is for each player to record their own shots.
In a typical game, a player starts with 5 ships of various lengths.

### Modifications
During a players' turn, they choose a ship to attack with.
Each ship is assigned a range which restricts the rows on the board it is able to attack.
Each ship also has a limited amount of ammunition.
A ships would be unable to attack if is has been sunk or has run out of ammunition.


## Built with

- [Visual Studio 2019](https://visualstudio.microsoft.com/vs/) - IDE used

## Authors

- **Lyam Lim** - [lyamlim97](https://github.com/lyamlim97)