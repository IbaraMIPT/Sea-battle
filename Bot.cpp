#include "Bot.h"
#include <iostream>

using namespace std;

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
