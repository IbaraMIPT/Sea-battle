#include "Human.h"
#include <iostream>

using namespace std;

void Human::choose_action(){
	cout << "Do you want to move or attack?" << endl <<													
	"Enter 'm' to move or 'a' to attack or 'i' to get info about your ships: ";
	cin >> choosen_action;
}

void Human::choose_ship(){
	cout << "Choose ship: enter ship coordinates: ";													
	cin >> coord_x >> coord_y;
	for (int i = 0; i <= this->get_ship_num(); i++){																			
		if ((ships[i]->get_coord_x() == coord_x - 1) && (ships[i]->get_coord_y() == coord_y - 1)){
			this->set_current_ship_num(i);
		}
	}
	while (current_ship_num == -1){
		cout << "No ship on this field" << endl << 
		"Choose ship: enter ship coordinates: ";
		cin >> coord_x >> coord_y;
		for (int i = 0; i <= this->get_ship_num(); i++){																			
			if ((ships[i]->get_coord_x() == coord_x - 1) && (ships[i]->get_coord_y() == coord_y - 1)){
				this->set_current_ship_num(i);
			}
		}
	}
}

void Human::move(){
	
}

void Human::attack(){
	
}
