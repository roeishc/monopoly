#include "Deck.h"

Deck::Deck(){
	srand(std::time(nullptr));
	int random_value;
	for (int i = 0; i < DECK_SIZE; i++) {
		//assuming a value of 0 is valid for a card
		random_value = rand() % (2 * MAX_CARD_VAL);
		random_value -= MAX_CARD_VAL;
		cards_deck.push(random_value);
	}
}
int Deck::getFirstCard(){
	//get the first card's value in the deck, place it at the bottom
	//of the deck and return the value
	int first = cards_deck.front();
	cards_deck.pop();
	cards_deck.push(first);
	return first;
}