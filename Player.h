#ifndef PLAYER_H
#define PLAYER_H

#include "Ship.h"

class Player{
	private:
		int ship_num;
		int current_ship_num;
		Ship** ships;
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
		virtual void turn();
		virtual void move();
		virtual void attack();
};

#endif
