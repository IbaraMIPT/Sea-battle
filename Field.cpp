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

char Field::get_field(int x, int y) {return sea[x][y];}

void Field::set_field(int _x, int _y, char c) {sea[_x][_y] = c;}

void Field::show_field()
{
	for(int t = 0; t < 10; t++)
	{
		cout << t << "  ";
	}
	cout << endl;
	for(int q = 0; q < 14; q++)
	{
		cout << " _";
	}	
	cout << endl;
	for(int i = 0; i < 9; i++)
	{
		cout << i+1 << "| ";
		for (int j = 0; j < 9; j++)
		{
			cout << sea[i][j] << "  ";					
		}
		cout << endl;
	}
	cout << endl;
}
