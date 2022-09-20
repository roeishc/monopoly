#include "gameEngine.h"
#include "Asset.h"
#include "Instruction.h"
using namespace std;

int main() {

	try {

//check necessary constants for required values
#ifdef INTEREST
		if (INTEREST < 0)
			throw INVALID_INTEREST;
#endif
#ifdef DECK_SIZE
		if (DECK_SIZE < 1)
			throw INVALID_DECK_SIZE;
#endif
#ifdef STARTING_BALANCE
		if (STARTING_BALANCE < 0)
			throw INVALID_STARTING_BALANCE;
#endif
		//initialize game
		gameEngine Monopoly;
		Monopoly.game();
	}

	catch (const char* exe) {
		cout << exe << endl;
	}

	catch (...) {
		cout << "Unhandled exception.\n";
	}

	return 0;

}