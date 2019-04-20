#ifndef GAME_H
#define GAME_H

class Player;
class Ship;
class Field;
class Game{
	private:
		int turn;
	public:
		Game();
		~Game();
		void set_ships_on_field();
		void cout_coords();
		void move_ship_on_field(int num);
		void live();
};

#endif
