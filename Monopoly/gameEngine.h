#include "Player.h"
#include "Deck.h"
#include <list>
#include <fstream>
#include <istream>

#define STR_INT_CONV "Conversion of string to int failed."
#define INVALID_STARTING_BALANCE "Starting balance cannot be a negative value."
#define OPEN_FAILED "Failed to open file."
#define FILE_NAME "board.txt"
#define INVALID_NUM_OF_PLAYERS "Invalid number of players."
#define BAD_TYPE "Invalid slot type."
#define SIZE 101
#define STARTING_BALANCE 350

#define LOST cout << p.getName() << " has run out of golden nuggets and lost.\n"

class gameEngine{
	Board game_board;
	Deck game_deck;
	list<Player*> players_list;
public:
	gameEngine();
	~gameEngine();

	//getInfoFromFile
	//the functions reads each line from the file
	//and allocates memory in the game board accordingly
	void getInfoFromFile(const string&) throw (const char*);

	//getSlotName
	//the functions receives a line from the file
	//and returns a string with the file's name only
	string getSlotName(const string& line) const;

	//getInstructionSlotType
	//the functions receives a line from the file
	//and returns a character to define the slot's type
	char getInstructionSlotType(const string& line) const;

	//groupNameRentPrice
	//the function receives a line from the file and two references to int(s).
	//it assigns the price and rent values to the integers
	//and returns the asset's group name
	string groupNameRentPrice(const string& line, int& price, int& rent) throw (const char*);
	
	//getPlayers
	//a function meant to get information from the user
	//regarding how many players are playing and their names
	void getPlayers() throw (const char*);
	
	//turn
	//the function to play a player's turn
	bool turn(Player& p) throw (const char*);
	
	//yesNoChoice
	//return input from user - 1 for yes, 0 for no
	int yesNoChoice() const;
	
	//diceRoll
	//returns a value between 1 and 6
	int diceRoll() const;
	
	//deletePlayerFromGame
	//a function to remove a player from the players list
	//in case of a player quitting or a player losing
	void deletePlayerFromGame(Player& p);
	
	//game
	//the main function to run the Monopoly game
	void game();
};

