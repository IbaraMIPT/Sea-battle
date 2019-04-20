#include "Human.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <windows.h>

using namespace std;

/*Human::Human()
{
	cout << "Human created" << endl;
}*/

void Human::choose_action()
{
	char step[1];
	cout << "Do you want to move or attack?" << endl <<													
	"Enter 'm' to move or 'a' to attack or 'i' to get info about your ships: ";
	cin >> step;
	while(true){
		if ((strcmp(step, "a") == 0) || (strcmp(step, "m") == 0) || (strcmp(step, "i") == 0) ){
			break;
		}
		else{
			cout << "Incorrect input! Try again: ";
			cin >> step;
		}
	}
	choosen_action[0] = step[0];
}

char* Human::get_choosen_action(){return choosen_action;}

void Human::human_init()
{
	for (int i = 0; i < 5; i++)
	{
		if (i < 3)
		{
			human_ships[i] = new Light_ship;
		}
		else 
		{
			human_ships[i] = new Heavy_ship;
		}
	}
}

void Human::get_ship_info(int num)
{
	human_ships[num]->info();
}

void Human::choose_ship()
{
	cout << "Choose ship: enter ship coordinates: ";													
	cin >> this->coord_x >> this->coord_y;
	this->set_current_ship_num(-1);
	for (int i = 0; i < this->get_ship_num(); i++)
	{																			
		if ((human_ships[i]->get_coord_x() == coord_x - 1) && (human_ships[i]->get_coord_y() == coord_y - 1))
		{
			this->set_current_ship_num(i);
		}
	}
	while (this->get_current_ship_num() == -1)
	{
		cout << "No ship on this field" << endl << 
		"Choose ship: enter ship coordinates: ";
		cin >> this->coord_x >> this->coord_y;
		for (int i = 0; i < this->get_ship_num(); i++)
		{																			
			if ((human_ships[i]->get_coord_x() == coord_x - 1) && (human_ships[i]->get_coord_y() == coord_y - 1))
			{
				this->set_current_ship_num(i);
			}
		}
	}
}

void Human::set_ships_coords()
{
	for (int i = 0; i < 5; i++)
	{
		srand(time(NULL));
		int _x, _y;
		int mas_x[5];
		int mas_y[5];
		_x = rand()%9;																				
		_y = rand()%2;
		for (int j = 0; j < i; j++)
		{
			for (int k = 0; k < i; k++)
			{
				while ( (human_ships[k]->get_coord_x() == _x) && (human_ships[k]->get_coord_y() == _y) )
				{
					_x = rand()%9;																				
					_y = rand()%2;
				}
			}	
		}
		human_ships[i]->set_coords(_x, _y);
	}
}

Human::get_ship_coord_x(int num)
{
	return human_ships[num]->get_coord_x();
}

Human::get_ship_coord_y(int num)
{
	return human_ships[num]->get_coord_y();
}

Human::get_ship_movement(int num)
{
	return human_ships[num]->get_movement();
}

Human::get_ship_HP(int num)
{
	return human_ships[num]->get_HP();
}

void Human::set_ship_coords(int num, int new_x, int new_y)
{
	human_ships[num]->set_coords(new_x, new_y);
}

int Human::find_collided_ship_num(int _x, int _y)
{
	for (int i = 0; i < this->get_ship_num(); i++)
	{
		if ( (human_ships[i]->get_coord_x() == _x) && (human_ships[i]->get_coord_y() == _y) )
		{
			collided_ship_num = i;
		}
	}
}

void Human::delete_ship(int num)
{
	Ship* temp;
	temp = human_ships[this->get_ship_num()];
	human_ships[this->get_ship_num()] = human_ships[num];
	human_ships[num] = temp;
	delete human_ships[this->get_ship_num()];
}

void Human::info(){
	for (int i = 0; i < this->get_ship_num(); i++ )
	{
		//Sleep(1500);
		human_ships[i]->info();
	}
}
