#include "Game.h"
#include "Light_ship.h"
#include "Heavy_ship.h"
#include "Field.h"
#include "Bot.h"
#include "Human.h"

#include <iostream>

using namespace std;

Game::Game(){
	cout << 
		"SEA BATTLE" << endl <<
		"There are two types of ships: light (L) and heavy (H). Each player has 3 light and 2 heavy ships." << endl <<
		"Different types have different characteristic. " << endl << endl <<
		"Light ships: "<< endl <<
		"Heavy ships: "<< endl <<
		endl <<
		"On the field you can see HP of each your ship. " << endl <<
		"You can see only type of enemy ships. Type is marked by a uppercase letter. Damaged ships marked by a lowercase letter." << endl <<
		"Your goal is to destroy all enemy ships." << endl;
	system("pause");
}


