#ifndef __SLOT
#define __SLOT

#include <iostream>
#include <cstring>
#include <string>
#include <ios>
#include <iomanip>

using namespace std;

#define INVALID_SLOT_NAME "Invalid slot name."

class Slot{
	string name;
public:
	//empty constructor
	//creates a slot with an empty string as a name
	//to enable both asset's and instruction's constructors
	//to create a new object
	Slot();

	Slot(string name);

	//virtual destructor
	//meant to keep the right order for calling destructors
	//for virtual function and its derivative classes
	virtual ~Slot() {/* cout << "In Slot's destructor.\n"; */};

	//printNameIdx
	//used in both asset and instruction slots, hence placed here for both
	void printNameIdx(int idx) const;

	//printSlot
	//pure virtual function - makes this current class a pure virtual class
	//will be implemented in both instruction.cpp and in asset.cpp
	virtual void printSlot(int idx) const = 0;

	string getName() const { return name; };
};

#endif