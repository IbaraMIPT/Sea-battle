#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
	public:		
		virtual ~Human();
		void human_init();
		void choose_action();
		char* get_choosen_action();
		void choose_ship();
		void set_ships_coords();
		void get_ship_info(int num);
		int get_ship_coord_x(int num);
		int get_ship_coord_y(int num);
		int get_ship_movement(int num);
		int get_ship_damage(int num);
		int get_ship_HP(int num);
		int get_ship_attack_radius(int num);
		void set_ship_coords(int num, int new_x, int new_y);
		void set_ship_HP(int num, int _dam);
		int find_collided_ship_num(int _x, int _y);
		void delete_ship(int num);
		void info();
	private:
		char choosen_action[1];
		Ship* human_ships[5];
};

#endif
