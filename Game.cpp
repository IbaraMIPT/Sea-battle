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

Game::Game()
{
	//cout << "Game constructor" << endl;
	game_field = new Field;
	human = new Human;
	human->human_init();
	//cout << "-----------------------" << endl;
	bot = new Bot;
	bot->bot_init();
	//cout << "-----------------------" << endl << endl;
	human->set_ships_coords();
	bot->set_ships_coords();
}

void Game::set_ships_on_field()
{
	for (int i = 0; i < 5; i++)
	{
		int _x, _y;
		_x = human->get_ship_coord_x(i);
		_y = human->get_ship_coord_y(i);
		if (i < 3) 
		{
			game_field->set_field(_x, _y, '3' );
		}
		else 
		{
			game_field->set_field(_x, _y, '6' );
		}
		_x = bot->get_ship_coord_x(i);
		_y = bot->get_ship_coord_y(i);
		if (i < 3) 
		{
			game_field->set_field(_x, _y, 'L' );
		}
		else 
		{
			game_field->set_field(_x, _y, 'H' );
		}
	}
}

void Game::live()
{
	this->set_ships_on_field();
	cout << 
		"SEA BATTLE" << endl <<
		"There are two types of ships: light (L) and heavy (H). Each player has 3 light and 2 heavy ships." << endl <<
		"Different types have different characteristics. " << endl << endl <<
		"Light ships: " << endl;
		human->get_ship_info(0);
		cout << endl <<
		"Heavy ships: "<< endl;
		human->get_ship_info(4);
		cout << endl <<
		"On the field you can see HP of each your ship. " << endl <<
		"You can see only type of enemy ships. Type is marked by a uppercase letter. Damaged ships marked by a lowercase letter." << endl <<
		"Your goal is to destroy all enemy ships." << endl;
	system("pause");
	system("cls");
	game_field->show_field();
}
	


