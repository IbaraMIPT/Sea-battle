#include "Bot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*Bot::Bot()
{
	cout << "Bot created" << endl;
}*/

void Bot::set_all_priority()
{
	
}

void Bot::choose_max_priority()
{
	
}

Bot::get_max_priority(){return max_priority;}

void Bot::set_max_priority(int pr)
{
	max_priority = pr;
}

Bot::get_ship_coord_x(int num)
{
	return bot_ships[num]->get_coord_x();
}

Bot::get_ship_coord_y(int num)
{
	return bot_ships[num]->get_coord_y();
}

Bot::get_ship_HP(int num)
{
	return bot_ships[num]->get_HP();
}

void Bot::bot_init()
{
	for (int i = 0; i < 5; i++)
	{
		if (i < 3)
		{
			bot_ships[i] = new Light_ship;
		}
		else 
		{
			bot_ships[i] = new Heavy_ship;
		}
	}
}

void Bot::set_ships_coords()
{
	for (int i = 0; i < 5; i++)
	{
		srand(time(NULL));
		int _x, _y;
		_x = rand()%9;																				
		_y = rand()%2 + 7;
		for (int j = 0; j < i; j++)
		{
			while ( (bot_ships[j]->get_coord_x() == _x) && (bot_ships[j]->get_coord_y() == _y) )
			{
				_x = rand()%9;																				
				_y = rand()%2 + 7;
			}
		}
		bot_ships[i]->set_coords(_x, _y);
	}
}
