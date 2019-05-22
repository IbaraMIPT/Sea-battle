#include "Light_ship.h"
#include <iostream>

using namespace std;

Light_ship::Light_ship()
{
	//cout << "Light ship created" << endl;
	this->HP = 3;
	this->type = 1;
	this->movement = 2;
	this->damage = 2;
	this->attack_radius = 2;
	this->priority = 0;
	this->alive = true;
}

Light_ship::~Light_ship()
{
	//cout << "Light ship on (" << x+1 << ", " << y+1 << ") was destroyed." << endl;
}

