#include "Board.h"

Board::Board(){
	board_arr.empty();
}
Board::~Board(){
	int size = board_arr.size();
	for (int i = 0; i < size; i++)
		delete board_arr[i];
}