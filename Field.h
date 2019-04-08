#ifndef FIELD_H
#define FIELD_H

class Ship;

class Field{
	protected:
		char sea[9][9];
	public:
		Field();						//in old version: field_generation
		void light_ships_generation();
		void heavy_ships_generation();
		void comp_light_ships_generation();
		void comp_heavy_ships_generation();
		void all_ships_generation();
		char get_field(int x, int y);
		void set_field(int _x, int _y, char c);
		void show_field();
};

#endif
