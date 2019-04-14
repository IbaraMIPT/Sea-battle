#include "Player.h"
#include <iostream>

using namespace std;

void Player::player_init()
{
	this->ship_num = 5;
	this->current_ship_num = -1;
}

Player::Player()
{
	cout << "Player constructor" << endl;
}

Player::get_ship_num(){return ship_num;}

Player::get_current_ship_num(){return current_ship_num;}

void Player::set_current_ship_num(int i)
{
	current_ship_num = i;
}             
	
