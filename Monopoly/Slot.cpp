#include "Slot.h"

Slot::Slot(){
	name = "";
}
Slot::Slot(string name){
	if (name.size() == 0)
		throw INVALID_SLOT_NAME;
	this->name = name;
}
void Slot::printNameIdx(int idx) const{
	cout << "Slot number: " << idx << ".\n";
	cout << "Slot name: " << name << ".\n";
}