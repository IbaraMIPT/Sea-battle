#include "Player.h"
#include "Light_ship.h"
#include "Heavy_ship.h"
#include <iostream>

using namespace std;

Player::Player(){
	this->ship_num = 5;
	this->current_ship_num = -1;
	ships = new Ship*[5];
	for (int i = 0; i < 5; i++){
		if (i < 3){
			ships[i] = new Light_ship;
		}
		else {
			ships[i] = new Heavy_ship;
		}
	}
}

Player::get_ship_num(){return ship_num;}

Player::get_current_ship_num(){return current_ship_num;}

void Player::set_current_ship_num(int i){
	current_ship_num = i;
}              
	
