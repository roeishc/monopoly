#include <queue>
#include "Slot.h"
#include <ctime>

#define INVALID_DECK_SIZE "Deck size cannot be smaller than 1."
#define DECK_SIZE 20
#define MAX_CARD_VAL 350

class Deck{
	queue<int> cards_deck;
public:
	//empty constructor
	//creates a deck with DECK_SIZE cards
	//each card holds a value between -MAX_CARD_VAL and +MAX_CARD_VAL
	Deck();

	//getFirstCard
	//function to draw the first card's value
	//and place it in the bottom of the deck
	int getFirstCard();
};

