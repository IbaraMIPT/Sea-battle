#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
	public:
		//Human();
		~Human();
		void human_init();
		void choose_action();
		char get_choosen_action();
		void choose_ship();
		void set_ships_coords();
		void get_ship_info(int num);
		int get_ship_coord_x(int num);
		int get_ship_coord_y(int num);
		int get_ship_HP(int num);
		void move();
		void attack();
		void info();
		void turn();
	private:
		char choosen_action[1];
		Ship* human_ships[5];
};

#endif
