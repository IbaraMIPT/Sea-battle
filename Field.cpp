#include "Field.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Field::Field()
{
	for (int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			sea[i][j] = '0';
		}
	}
}

void Field::light_ships_generation()
{
	srand(time(NULL));																				
	int _x, _y;																						
	for (int i = 0; i < 3; i++){																	
		_x = rand()%9;																				
		_y = rand()%2;																				
		while (get_field(_x, _y) != '0'){															
			_x = rand()%9;																			
			_y = rand()%2;																			
		}																							
		sea[_x][_y] = '3';																			
	}
}

void Field::heavy_ships_generation()
{
	srand(time(NULL));																				
	int _x, _y;																						
	for (int i = 0; i < 2; i++){																	
		_x = rand()%9;																				
		_y = rand()%2;																				
		while (get_field(_x, _y) != '0'){															
			_x = rand()%9;																			
			_y = rand()%2;																			
		}																							
		sea[_x][_y] = '6';																			
	}
}

void Field::comp_light_ships_generation()
{
	srand(time(NULL));																				
	int _x, _y;																						
	for (int i = 0; i < 3; i++){																	
		_x = rand()%9;																				
		_y = rand()%2 + 7;																			
		while ((get_field(_x, _y) != '0') || (get_field(_x, _y-7) != '0')){							
			_x = rand()%9;																			
			_y = rand()%2 + 7;																		
		}																							
		sea[_x][_y] = 'L';																			
	}
}

void Field::comp_heavy_ships_generation()
{
	srand(time(NULL));																				
	int _x, _y;																						
	for (int i = 0; i < 2; i++){																	
		_x = rand()%9;																				
		_y = rand()%2 + 7;																			
		while ((get_field(_x, _y) != '0') || (get_field(_x, _y-7) != '0')){							
			_x = rand()%9;																			
			_y = rand()%2 + 7;																		
		}																							
		sea[_x][_y] = 'H';																			
	}
}

void Field::all_ships_generation()
{
	light_ships_generation();																		
	heavy_ships_generation();																		
	comp_light_ships_generation();																	
	comp_heavy_ships_generation();	
}

char Field::get_field(int x, int y) {return sea[x][y];}

void Field::set_field(int _x, int _y, char c) {sea[_x][_y] = c;}

void Field::show_field()
{
	for(int t = 0; t < 10; t++){
		cout << t << "  ";
	}
	cout << endl;
	for(int q = 0; q < 14; q++){
		cout << " _";
	}	
	cout << endl;
	for(int i = 0; i < 9; i++){
		cout << i+1 << "| ";
		for (int j = 0; j < 9; j++){
			cout << sea[i][j] << "  ";					
		}
		cout << endl;
	}
	cout << endl;
}
