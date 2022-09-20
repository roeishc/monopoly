#ifndef __PLAYER
#define __PLAYER

#include "Board.h"

using namespace std;

#define P_CPY_CON "No copy constructor created for Player class."
#define P_CAST_OP "No casting operator created for Player class."
#define INVALID_BALANCE "Balance cannot hold a negative value."
#define INVALID_PLAYER_NAME "Invalid player name."
#define LAP_REFUND 350

class Asset;

class Player{
	string name;
	int balance;
	int position;
	vector<Asset*> assets_arr;
	bool jail;
	
	friend gameEngine;
public:
	Player(string name);

	//copy constructor
	//meant to overwrite the default copy constructor with an exception
	Player(const Player& other) throw (const char*) { throw P_CPY_CON; };

	//assignment operator
	//meant to overwrite the default assignment operator with an exception
	const Player& operator=(const Player& other) throw (const char*) { throw P_CAST_OP; };

	//boolChargeRefund
	//a function to refund the player with a positive value
	//or to charge the player with a negative value
	bool boolChargeRefund(const int& value) throw (const char*);

	//retrieveAsset
	//a function to unpawn an asset
	void retrieveAsset(Asset* const ptr);
	
	//pawnAsset
	//a function to pawn an asset
	void pawnAsset(Asset* const ptr);
	
	//buyAsset
	//a function for purchasing an asset
	void buyAsset(Asset* const ptr);
	
	//updatePosition
	//the function receives the dice's roll
	//and updates the player's position.
	//check if the player has completed a lap around the board,
	//updates the pawned years of assets (if necessary)
	//and refunds a complete lap refund value
	void updatePosition(const int& val, const int& board_size);

	//get and set methods
	int getBalance() const { return balance; };
	string& getName() { return name; };
	void setBalance(const int& val) throw (const char*);
};


#endif