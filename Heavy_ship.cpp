#include "Heavy_ship.h"
#include <iostream>

using namespace std;

Heavy_ship::Heavy_ship()
{
	this->HP = 6;
	this->type = 2;
	this->movement = 1;
	this->damage = 4;
	this->attack_radius = 3;
	this->priority = 0;
	this->alive = true;
}

Heavy_ship::~Heavy_ship()
{
	cout << "Heavy ship on (" << x+1 << ", " << y+1 << ") was destroyed." << endl;
}
