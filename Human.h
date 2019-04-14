#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
	public:
		Human();
		~Human();
		void human_init();
		void choose_action();
		void choose_ship();
		void move();
		void attack();
	private:
		char choosen_action[1];
		Ship** human_ships;
};

#endif
