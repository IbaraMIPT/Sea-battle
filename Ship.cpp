#include "Ship.h"
#include <iostream>

using namespace std;

Ship::Ship()
{
	//cout << "Ship constructor" << endl;
}

Ship::~Ship()
{
	//cout << "Ship deleted" << endl;
}

bool Ship::is_alive() {return alive;}

Ship::get_attack_radius() {return attack_radius;}

Ship::get_coord_x() {return x;}

Ship::get_coord_y() {return y;}

Ship::get_damage() {return damage;}

Ship::get_HP() {return HP;}

Ship::get_movement() {return movement;}

Ship::get_priority() {return priority;}

Ship::get_type() {return type;}

void Ship::set_coords(int _x, int _y)
{
	x = _x;
	y = _y;
}

void Ship::set_HP(int dam)
{
	HP = HP - dam;
}

void Ship::set_priority(int x)
{
	priority = x;
}

void Ship::show_coords()
{
	cout << "(" << this->get_coord_x()+1 << ", " << this->get_coord_y()+1 << ")" << endl;
}

void Ship::info()
{
	cout << endl << 
	"Coordinates: (" << x+1 << ", " << y+1 << ")" << endl <<
	"HP: " << HP << endl << 
	"Movement: " << movement << endl << 
	"Damage: " << damage << endl << 
	"Attack radius: " << attack_radius << endl;
}
