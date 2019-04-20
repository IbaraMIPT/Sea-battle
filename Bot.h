#ifndef BOT_H
#define BOT_H

#include "Player.h"

class Bot : public Player {
	public:
		//Bot();
		~Bot();
		void bot_init();
		void set_all_priority();
		void choose_max_priority();
		int get_max_priority();
		int get_ship_coord_x(int num);
		int get_ship_coord_y(int num);
		int get_ship_HP(int num);
		void set_max_priority(int pr);
		void set_ship_HP(int num, int _dam);
		void set_ships_coords();
		int find_collided_ship_num(int _x, int _y);
		void delete_ship(int num);
	private:
		int max_priority;
		Ship* bot_ships[5];
};

#endif
