#include "Bot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <windows.h>

using namespace std;

Bot::~Bot()
{
	delete[] bot_ships;
}

int Bot::find_collided_ship_num(int _x, int _y)
{
	for (int i = 0; i < this->get_ship_num(); i++)
	{
		if ( (bot_ships[i]->get_coord_x() == _x) && (bot_ships[i]->get_coord_y() == _y) )
		{
			collided_ship_num = i;
		}
	}
}

void Bot::delete_ship(int num)
{
	Ship* temp;
	temp = bot_ships[this->get_ship_num()];
	bot_ships[this->get_ship_num()] = bot_ships[num];
	bot_ships[num] = temp;
	delete bot_ships[this->get_ship_num()];
}

void Bot::set_ship_HP(int num, int _dam)
{
	bot_ships[num]->set_HP(_dam);
}

void Bot::set_ship_coords(int num, int new_x, int new_y)
{
	bot_ships[num]->set_coords(new_x, new_y);
}

Bot::get_ship_priority(int num)
{
	return bot_ships[num]->get_priority();
}

void Bot::set_ship_priority(int num, int pr)
{
	bot_ships[num]->set_priority(pr);
}

Bot::get_ship_attack_radius(int num)
{
	return bot_ships[num]->get_attack_radius();
}

Bot::get_ship_movement(int num)
{
	return bot_ships[num]->get_movement();
}

Bot::get_ship_damage(int num)
{
	return bot_ships[num]->get_damage();
}

void Bot::choose_random_ship()
{
	int rnd;
	rnd = rand()%5+1;
	this->set_current_ship_num(this->get_ship_num() - rnd);
	while (this->get_current_ship_num() < 0)
	{
		int rnd = rand()%5+1;
		this->set_current_ship_num(this->get_ship_num() - rnd);
	}
}

void Bot::choose_max_priority()
{
	int max = this->get_max_priority();
	for (int i = 0; i < this->get_ship_num(); i++)
	{
		if (bot_ships[i]->get_priority() > max)
		{
			max = bot_ships[i]->get_priority();
			this->set_current_ship_num(i);	
		}
	}
	this->set_max_priority(max);
}

Bot::get_max_priority()
{
	return max_priority;
}

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
		int _x, _y, n;
		n = rand()%5+1;
		_x = rand()%9;																				
		_y = rand()%2 + 7;
		for (int k = 0; k < n; k++)
		{
			_x = _x + rand()%5-2;
			while ( (_x < 0) || (_x >= 9) )
			{
				_x = _x + rand()%5-2;	
			}
			for (int l = 0; l < i; l++)
			{
				for (int j = 0; j < i; j++)
				{
					while ( (bot_ships[j]->get_coord_x() == _x) && (bot_ships[j]->get_coord_y() == _y) )
					{
						_x = rand()%9;																				
						_y = rand()%2 + 7;
					}
				}	
			}
		}
		bot_ships[i]->set_coords(_x, _y);
	}
}
