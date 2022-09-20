#include "gameEngine.h"
#include "Instruction.h"
#include "Asset.h"

gameEngine::gameEngine(){
	getInfoFromFile(FILE_NAME);
	getPlayers();
}
gameEngine::~gameEngine(){
	while (!players_list.empty()) {
		delete players_list.front();
		players_list.pop_front();
	}
}
void gameEngine::getInfoFromFile(const string& file_name) throw (const char*) {
	ifstream file;
	file.open(file_name, ios::in);
	string line_input, asset_group, name;
	int price, rent;
	char type;
	if (file.is_open()) {
		//run through the file's lines
		while (file.cur != file.eof()) {
			getline(file, line_input);
			name = getSlotName(line_input);
			switch (line_input[0]) {
				//instrcution slot
			case 'I':
				type = getInstructionSlotType(line_input);
				game_board.board_arr.push_back(new Instruction(name, type));
				break;
				//asset slot
			case 'P':
				asset_group = groupNameRentPrice(line_input, price, rent);
				game_board.board_arr.push_back(new Asset(asset_group, name, price, rent));
				break;
			}
		}
	}
	else
		throw OPEN_FAILED;
	file.close();
}
string gameEngine::getSlotName(const string& line) const{
	//find second comma
	//return the string between second comma and third comma
	//in case there isn't a third comma, it's an instruction slot
	//and substr will return the rest of the string
	int second = line.find(',', line.find(',') + 1);
	return line.substr(second + 1, line.find(',', second + 1) - second - 1);
}
char gameEngine::getInstructionSlotType(const string& line) const{
	//return the first character after the first comma
	return line[line.find(',') + 1];
}
string gameEngine::groupNameRentPrice(const string& line, int& price, int& rent) throw (const char*) {
	int last_comma = line.find_last_of(',');
	//find the second to last comma
	int before_last_comma = last_comma - 1;
	int first_comma = line.find(',');
	int second_comma = line.find(',', line.find(',') + 1);
	while (line[before_last_comma--] != ',');
	try {
		//rent is the last number in the string, convert the rest of the string
		//after the last comma to an int
		rent = stoi(line.substr(last_comma + 1), 0, 10);
		//price is the number between the second to last
		//and the last comma
		price = stoi(line.substr(++before_last_comma + 1, last_comma - before_last_comma - 1), 0, 10);
	}
	catch (...) {
		throw STR_INT_CONV;
	}
	return line.substr(first_comma + 1, second_comma - first_comma - 1);
}
void gameEngine::getPlayers()
 throw (const char*) {
	int num_of_players;
	char temp_name[SIZE];
	//get number of players from user
	cin.ignore(cin.rdbuf()->in_avail());
	cout << "Enter number of players: ";
	cin >> num_of_players;
	if (num_of_players < 1)
		throw INVALID_NUM_OF_PLAYERS;
	//get names in a loop and refund STARTING_BALANCE to each player
	for (int i = 0; i < num_of_players; i++){
		cout << "Enter full name (up to " << SIZE - 1 << " characters): ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(temp_name, SIZE);
		//input of empty string - try again
		if (strlen(temp_name) == 0) {
			cout << "Try again.\n";
			i--;
			continue;
		}
		players_list.push_back(new Player(temp_name));
		players_list.back()->setBalance(STARTING_BALANCE);
	}
}
bool gameEngine::turn(Player& p) throw (const char*) {
	//greeting message
	cout << "\n~~~~~~~~~~~~~~~~~~~~\n";
	//if the player is in jail, skip one turn
	if (p.jail) {
		cout << endl << p.getName() << " is in jail, turn skipped.\n";
		p.jail = false;
		return true;
	}
	cout << endl << p.getName() << ", it's your turn, you have " << p.getBalance() << " golden nuggets.\n";
	//ask the player about quitting the game
	cout << "Would you like to quit the game? 1 - Yes, 0 - No: ";
	if (yesNoChoice()) {
		cout << p.getName() << " has left the game.\n";
		return false;
	}
	int dice, value;
	Slot* p_slot;
	Instruction* p_inst;
	Asset* p_asset;
	Player* p_player = NULL;
	//start turn
	//print current position
	cout << p.getName() << "'s current position:\n";
	game_board.board_arr[p.position - 1]->printSlot(p.position);
	//starting turn - roll the dice
	dice = diceRoll();
	cout << p.getName() << " rolled the number " << dice << ".\n";
	//if the player has completed a lap, refund 350
	p.updatePosition(dice, game_board.getBoardSize());
	//print updated position
	cout << p.getName() << "'s new position:\n";
	game_board.board_arr[p.position - 1]->printSlot(p.position);
	
	//check the new position
	p_slot = game_board.board_arr[p.position - 1];

	if (p_inst = dynamic_cast<Instruction*>(p_slot)) {
		switch (p_inst->getType()) {
			//get ticket
			case 'T':
				cout << p.getName() << "'s current balance: " << p.getBalance() << ".\n";
				value = game_deck.getFirstCard();
				cout << "Drew a card with the value: " << value << ".\n";
				if (!(p.boolChargeRefund(value))) {
					LOST;
					return false;
				}
				cout << p.getName() << "'s new balance: " << p.getBalance() << ".\n";
				break;
			//jail
			case 'J':
				p.jail = true;
				break;
			//start game
			case 'S':
				p.boolChargeRefund(LAP_REFUND);
				break;
		}
		return true;
	}
	else if (p_asset = dynamic_cast<Asset*>(p_slot)) {
		p_player = p_asset->getOwner();
		//in case the asset is already owned
		if (p_player) {
			//if the player owns this asset, end the turn
			if (p_player == &p)
				return true;
			//if another player owns the asset, charge.
			//in case the player doesn't have enough funds to pay,
			//the function boolChargeRefund returns false
			//and this function returns false to the main game function
			//to remove the player from the game
			value = p_asset->getRent();
			if (!(p.boolChargeRefund((-1) * value))) {
				//pay the owner of p_asset the remainder of p_player's balance
				p_player->boolChargeRefund(p.getBalance());
				LOST;
				return false;
			}
			//if the asset is not pawned, refund its owner
			if (!(p_asset->getPawnYears()))
				p_player->boolChargeRefund(value);
		}
		//in case the asset isn't owned yet
		else {
			//if the player doesn't have enough money to
			//buy the asset, end the turn
			if (p.getBalance() < p_asset->getPrice())
				cout << p.getName() << " doesn't have enough golden nuggets to purchase this asset.\n";
			//if the player has enough money to
			//buy the asset, ask them
			else {
				cout << "The assets's price is: " << p_asset->getPrice() << " golden nuggets.\n";
				cout << "Would you like to purchase this asset? 1 - Yes, 0 - No: ";
				if (yesNoChoice())
					p.buyAsset(p_asset);
			}
		}
	}
	else
		throw BAD_TYPE;
	return true;
}
int gameEngine::yesNoChoice() const{
	int choice = -1;
	while (choice < 0 || 1 < choice) {
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> choice;
		if (choice < 0 || 1 < choice)
			cout << "Invalid value, try again: ";
	}
	return choice;
}
int gameEngine::diceRoll() const{
	srand(std::time(nullptr));
	return (rand() % 6) + 1;
}
void gameEngine::deletePlayerFromGame(Player& p){
	//in owned assets, set owner to NULL
	//and in pawned assets, set pawn years to zero
	for (size_t i = 0; i < p.assets_arr.size(); i++) {
		p.assets_arr[i]->setOwner(NULL);
		if (p.assets_arr[i]->getPawnYears())
			p.assets_arr[i]->zeroPawnYears();
	}
	//the turn belongs to the first player in the list
	//erase the first player
	players_list.pop_front();
	////find player in list
	//list<Player*>::iterator itr_idx = players_list.begin();
	//while (&p != itr_idx.operator*())
	//	itr_idx++;
	////remove player from list
	//players_list.erase(itr_idx);
}
void gameEngine::game(){
	//starting the game with at least 2 players
	Player* p_player;
	while (players_list.size() > 1) {
		//if turn function returns false, the player
		//has to be removed from the list
		p_player = players_list.front();
		if (!(turn(*p_player))) {
			deletePlayerFromGame(*p_player);
			continue;
		}
		//move the player to the end of the list after their turn
		players_list.pop_front();
		players_list.push_back(p_player);
	}
	if (players_list.size() == 1)
		cout << endl << players_list.front()->getName() << " IS THE WINNER!!!\n\n";
}