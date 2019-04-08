#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
	public:
		Human();
		~Human();
		void choose_action();
		void choose_ship();
	private:
		char choosen_action[1];
};

#endif
