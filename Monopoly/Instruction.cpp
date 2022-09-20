#include "Instruction.h"

Instruction::Instruction(string name, char type): Slot(name){
	this->type = type;
}
void Instruction::printSlot(int idx) const{
	printNameIdx(idx);
	cout << "Slot type: Instruction.\n";
}