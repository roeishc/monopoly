//#include "Player.h"
#include "Asset.h"

Player::Player(string name){
	if (name.size() == 0)
		throw INVALID_PLAYER_NAME;
	this->name = name;
	balance = 0;
	position = 1;
	jail = false;
}
void Player::setBalance(const int& val) throw(const char*){
	if (val < 0)
		throw INVALID_BALANCE;
	balance = val;
}
bool Player::boolChargeRefund(const int& value) throw(const char*){
	if (!value)
		return false;
	int current_balance = getBalance();
	vector<Asset*>::iterator itr = assets_arr.begin();
	vector<Asset*>::iterator itr_end = assets_arr.end();
	//positive value - refund
	if (value > 0) {
		//update balance according to value
		setBalance(current_balance + value);
		//check if the new balance is enough
		//to retrieve a pawned asset
		for (; itr != itr_end; itr++)
			//check if itr points to a pawned asset
			if (itr.operator*()->getPawnYears())
				//if itr points to a pawned asset, check if
				//current balance is enough to retrieve it
				if (itr.operator*()->getRetrievalPrice() <= getBalance())
					retrieveAsset(itr.operator*());
	}
	//negative value - charge
	else {
		//use the value as a positive integer
		//int pos_value = value * (-1);
		if (current_balance >= (value * (-1)))
			setBalance(current_balance + value);
		else {
			//pawn the assets until balance is enough to pay value
			//note: since pawning assets is executed with respect
			//to the order in the vector, when the last asset
			//is pawned, if the balance still isn't enough to pay,
			//the player has lost
			while (getBalance() < (value * (-1))) {
				//if all the assets are pawned and the balance still
				//isn't enough to pay, return false
				if (itr == itr_end)
					return false;
				//check if current asset is pawned.
				//if it isn't, pawn it
				if (itr.operator*()->getPawnYears() == 0)
					pawnAsset(itr.operator*());
				itr++;
			}
			boolChargeRefund(value);
		}
	}
	return true;
}
void Player::retrieveAsset(Asset* const ptr){
	if (!ptr)
		return;
	//casting to int since balance is int
	setBalance((int)(getBalance() - ptr->getRetrievalPrice()));
	ptr->zeroPawnYears();
}
void Player::pawnAsset(Asset* const ptr){
	if (!ptr)
		return;
	//casting to int since balance is int
	setBalance((int)(getBalance() + ptr->getPrice()));
	ptr->pawnYearsPlusOne();
}
void Player::buyAsset(Asset* const ptr){
	int current_balance = getBalance();
	int price = ptr->getPrice();
	//if the balance isn't enough to buy, return false
	if (current_balance < price)
		return;
	//reduce balance
	setBalance(current_balance - price);
	//asset's owner set to this
	ptr->setOwner(this);
	//add the asset to the vector
	assets_arr.push_back(ptr);
}
void Player::updatePosition(const int& val, const int& board_size){
	position += val;
	//if the position surpassed board_size, start back from 1
	//refund the player accordingly
	//and update pawned years
	if (position > board_size) {
		boolChargeRefund(LAP_REFUND);
		//add one pawned year in case the asset is pawned
		for (int i = 0; i < assets_arr.size(); i++) {
			if (assets_arr[i]->getPawnYears())
				assets_arr[i]->pawnYearsPlusOne();
		}
		position = (position % board_size);
	}
}