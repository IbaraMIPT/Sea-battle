#ifndef BOT_H
#define BOT_H

#include "Player.h"

class Bot : public Player {
	public:
		Bot();
		virtual ~Bot();
		void bot_init();
		void choose_max_priority();
		int get_max_priority();
		int get_ship_coord_x(int num);
		int get_ship_coord_y(int num);
		int get_ship_HP(int num);
		int get_ship_priority(int num);
		int get_ship_attack_radius(int num);
		int get_ship_movement(int num);
		int get_ship_damage(int num);
		void set_ship_priority(int num, int pr);
		void set_max_priority(int pr);
		void set_ship_HP(int num, int _dam);
		void set_ship_coords(int num, int new_x, int new_y);
		void set_ships_coords();
		void choose_random_ship();
		int find_collided_ship_num(int _x, int _y);
		void delete_ship(int num);
		void set_bot_current_ship(int num);
		int get_bot_current_ship();
	private:
		int max_priority;
		int bot_current_ship;
		Ship* bot_ships[5];
};

#endif
