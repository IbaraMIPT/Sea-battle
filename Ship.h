#ifndef SHIP_H
#define SHIP_H

class Ship{
	protected:
		int HP;
		int type;
		int movement;
		int damage;
		int attack_radius;
		int priority;
		int x, y;
		bool alive;
	public:
		Ship();
		virtual ~Ship();
		bool is_alive();
		int get_attack_radius();
		int get_coord_x();
		int get_coord_y();
		int get_damage();
		int get_HP();
		int get_movement();
		int get_priority();
		int get_type();
		void set_coords(int _x, int _y);
		void set_HP(int dam);
		void set_priority(int x);		
		void show_coords();
		void info();
};

#endif
