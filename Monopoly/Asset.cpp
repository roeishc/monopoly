#include "Asset.h"

Asset::Asset(string asset_group, string name, int price, int rent): Slot(name){
	this->price = price;
	this->rent = rent;
	this->asset_group = asset_group;
	pawn_years = 0;
	owner = NULL;
}
float Asset::getRetrievalPrice() const{
	return INTEREST * price * (float)pawn_years;
}
void Asset::setOwner(const Player* new_owner){
	owner = (Player*)new_owner;
}
void Asset::printSlot(int idx) const{
	printNameIdx(idx);
	cout << "Asset group name: " << asset_group << ".\n";
	if (owner)
		cout << "Owner name: " << owner->getName() << ".\n";
}