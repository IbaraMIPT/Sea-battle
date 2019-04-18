#ifndef PLAYER_H
#define PLAYER_H

#include "Light_ship.h"
#include "Heavy_ship.h"

class Player{
	private:
		int ship_num;
		int current_ship_num;
	public:
		int coord_x;
		int coord_y;
		int new_coord_x;
		int new_coord_y;
		
		Player();
		~Player();
		int get_ship_num();
		int get_current_ship_num();
		void set_current_ship_num(int i);
		void turn();
};

#endif
