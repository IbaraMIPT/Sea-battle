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
	
