#ifndef BOT_H
#define BOT_H

#include "Player.h"

class Bot : public Player {
	public:
		Bot();
		~Bot();
		void bot_init();
		void set_all_priority();
		void choose_max_priority();
		int get_max_priority();
		void set_max_priority(int pr);
	private:
		int max_priority;
		Ship** bot_ships;
};

#endif
