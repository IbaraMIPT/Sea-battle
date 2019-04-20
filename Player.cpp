#include "Player.h"
#include <iostream>

using namespace std;

Player::Player()
{
	this->ship_num = 5;
	this->current_ship_num = -1;
}

Player::get_ship_num(){return ship_num;}

Player::get_current_ship_num(){return current_ship_num;}

void Player::set_current_ship_num(int i)
{
	current_ship_num = i;
}             
	
void Player::set_ship_num(int kill)
{
	ship_num = ship_num - kill;
}

void Player::input_new_coords()
{
	int a, b;
	cin >> a >> b;
	new_coord_x = a-1;
	new_coord_y = b-1;
}
