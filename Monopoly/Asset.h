#include "Slot.h"
#include "Player.h"

#define A_CPY_CON "Cannot copy assets."
#define A_CAST_OP "No casting operator created for Asset class."
#define INVALID_INTEREST "Interest value cannot be negative."
#define INTEREST 2

class Player;

class Asset: public Slot{
	string city_name;
	int price;
	int rent;
	Player* owner;
	int pawn_years;
	string asset_group;
public:
	Asset(string asset_group, string name, int price, int rent);

	//copy constructor
	//meant to overwrite the default copy constructor with an exception
	Asset(const Asset& other) throw (const char*) { throw A_CPY_CON; };

	//assignment operator
	//meant to overwrite the default assignment operator with an exception 
	const Asset& operator=(const Asset& other) throw (const char*) { throw A_CAST_OP; };

	//destructor - meant to keep the right order for calling destructors
	//for virtual function and its derivative classes
	//virtual ~Asset() {/* cout << "In Asset's destructor.\n"; */};

	//getRetrievalPrice
	//function to calculate the price to unpawn the asset
	float getRetrievalPrice() const;
	
	//setOwner
	//function to set the owner of the current asset
	void setOwner(const Player* new_owner);
	
	//printSlot
	//print the information according to an asset slot
	virtual void printSlot(int idx) const;

	//get and set methods
	int getPawnYears() const { return pawn_years; };
	int getPrice() const { return price; };
	int getRent() const { return rent; };
	Player* getOwner() const { return owner; };

	void zeroPawnYears() { pawn_years = 0; };
	void pawnYearsPlusOne() { ++pawn_years; };
};