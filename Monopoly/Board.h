#include "Slot.h"
#include <vector>

#define B_CPY_CON "No copy constructor created for Board class."
#define B_CAST_OP "No casting operator created for Board class."

class gameEngine;

class Board{
	vector<Slot*> board_arr;

	friend gameEngine;
public:
	//empty constructor for Board since gameEngine
	//requires an empty constructor for Board
	Board();

	//copy constructor
	//meant to overwrite the default copy constructor with an exception
	Board(const Board& other) throw (const char*) { throw B_CPY_CON; };
	
	//assignment operator
	//meant to overwrite the default assignment operator with an exception
	const Board& operator=(const Board& other) throw (const char*) { throw B_CAST_OP; };
	
	//destructor
	//vector<Slot*> board_arr is a vector of pointers to
	//allocated memory of assets and instructions
	//the destructor will free the allocated memory
	~Board();
	
	int getBoardSize() const { return board_arr.size(); };
};

