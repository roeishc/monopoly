#include "Slot.h"

#define I_CPY_CON "Cannot copy instruction."
#define I_CAST_OP "No casting operator created for Instruction class."

class Instruction: public Slot{
	char type;
public:
	Instruction(string name, char type);

	//copy constructor
	//meant to overwrite the default copy constructor with an exception
	Instruction(const Instruction& other) throw (const char*) { throw I_CPY_CON; };

	//assignment operator
	//meant to overwrite the default assignment operator with an exception
	const Instruction& operator=(const Instruction& other) throw (const char*) { throw I_CAST_OP; };

	//destructor - meant to keep the right order for calling destructors
	//for virtual function and its derivative classes
	//virtual ~Instruction() {/* cout << "In Instruction's destructor.\n"; */};

	//printSlot
	//instruction's implementation for the virual function printSlot
	virtual void printSlot(int idx) const;

	//get
	char getType() const { return type; };
};

