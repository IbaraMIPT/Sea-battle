#include "Game.h"
#include "Light_ship.h"
#include "Heavy_ship.h"
#include "Field.h"
#include "Bot.h"
#include "Human.h"

#include <iostream>

using namespace std;

Human* human;
Bot* bot;
Field* game_field;

Game::intro()
{
	cout << "Game constructor" << endl;
	human->human_init();
	bot->bot_init();
	cout << 
		"SEA BATTLE" << endl <<
		"There are two types of ships: light (L) and heavy (H). Each player has 3 light and 2 heavy ships." << endl <<
		"Different types have different characteristics. " << endl << endl <<
		"Light ships: ~Some characteristics"<< endl <<
		"Heavy ships: ~Some characteristics"<< endl <<
		endl <<
		"On the field you can see HP of each your ship. " << endl <<
		"You can see only type of enemy ships. Type is marked by a uppercase letter. Damaged ships marked by a lowercase letter." << endl <<
		"Your goal is to destroy all enemy ships." << endl;
	system("pause");
}
	


