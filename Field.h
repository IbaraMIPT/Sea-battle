#ifndef FIELD_H
#define FIELD_H

class Ship;

class Field{
	protected:
		char sea[9][9];
	public:						
		char get_field(int x, int y);
		void set_field(int _x, int _y, char c);
		void show_field();
		Field();
};

#endif
