#include "Game.h"
#include "Light_ship.h"
#include "Heavy_ship.h"
#include "Field.h"
#include "Bot.h"
#include "Human.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <windows.h>

using namespace std;

Human* human;
Bot* bot;
Field* game_field;

Game::Game()
{
	game_field = new Field;
	human = new Human;
	human->human_init();
	bot = new Bot;
	bot->bot_init();
	human->set_ships_coords();
	bot->set_ships_coords();
}

float distance(int x, int y, int _x, int _y) 
{
	float dist = sqrt( pow( (_x - x),2 ) + pow( (_y - y),2 ) );
	return dist;
}

void Game::set_ships_on_field()
{
	for (int i = 0; i < 5; i++)
	{
		int _x, _y;
		_x = human->get_ship_coord_x(i);
		_y = human->get_ship_coord_y(i);
		if (i < 3) 
		{
			game_field->set_field(_x, _y, '3' );
		}
		else 
		{
			game_field->set_field(_x, _y, '6' );
		}
		_x = bot->get_ship_coord_x(i);
		_y = bot->get_ship_coord_y(i);
		if (i < 3) 
		{
			game_field->set_field(_x, _y, 'L' );
		}
		else 
		{
			game_field->set_field(_x, _y, 'H' );
		}
	}
}

void Game::draw_ship_on_field(int player, int num)
{
	if (player == 1)
	{
		if ( human->get_ship_HP( num ) == 3 )
		{
			game_field->set_field( human->get_ship_coord_x( num ), human->get_ship_coord_y( num ), '3' );
		}
		else if ( human->get_ship_HP( num ) == 1 )
		{
			game_field->set_field( human->get_ship_coord_x( num ), human->get_ship_coord_y( num ), '1' );
		}
		else if ( human->get_ship_HP( num ) == 6 )
		{
			game_field->set_field( human->get_ship_coord_x( num ), human->get_ship_coord_y( num ), '6' );
		}
		else if ( human->get_ship_HP( num ) == 4 )
		{
			game_field->set_field( human->get_ship_coord_x( num ), human->get_ship_coord_y( num ), '4' );
		}
		else if ( human->get_ship_HP( num ) == 2 )
		{
			game_field->set_field( human->get_ship_coord_x( num ), human->get_ship_coord_y( num ), '2' );
		}
		else if ( human->get_ship_HP( num ) <= 0 )
		{
			game_field->set_field( human->get_ship_coord_x( num ), human->get_ship_coord_y( num ), '0' );
		}
	}
	else
	{
		if ( bot->get_ship_HP( num ) == 3 )
		{
			game_field->set_field( bot->get_ship_coord_x( num ), bot->get_ship_coord_y( num ), 'L');
		}
		else if ( bot->get_ship_HP( num ) == 1 )
		{
			game_field->set_field( bot->get_ship_coord_x( num ), bot->get_ship_coord_y( num ), 'l' );
		}
		else if ( bot->get_ship_HP( num ) == 6 )
		{
			game_field->set_field( bot->get_ship_coord_x( num ), bot->get_ship_coord_y( num ), 'H' );
		}
		else if ( bot->get_ship_HP( num ) == 4 )
		{
			game_field->set_field( bot->get_ship_coord_x( num ), bot->get_ship_coord_y( num ), 'h' );
		}
		else if ( bot->get_ship_HP( num ) == 2 )
		{
			game_field->set_field( bot->get_ship_coord_x( num ), bot->get_ship_coord_y( num ), 'h' );
		}
		else if ( bot->get_ship_HP( num ) <= 0 )
		{
			game_field->set_field( bot->get_ship_coord_x( num ), bot->get_ship_coord_y( num ), '0' );
		}			
	}
}

void Game::show_turn()
{
	system("pause");
	system("cls");
	game_field->show_field();
}

void Game::live()
{
	int move_x, move_y;
	srand(time(NULL));
	this->set_ships_on_field();
	cout << 
		"SEA BATTLE" << endl <<
		"There are two types of ships: light (L) and heavy (H). Each player has 3 light and 2 heavy ships." << endl <<
		"Different types have different characteristics. " << endl << endl <<
		"Light ships: " << endl;
		human->get_ship_info(0);
		cout << endl <<
		"Heavy ships: "<< endl;
		human->get_ship_info(4);
		cout << endl <<
		"On the field you can see HP of each your ship. " << endl <<
		"You can see only type of enemy ships. Type is marked by a uppercase letter. Damaged ships marked by a lowercase letter." << endl <<
		"Your goal is to destroy all enemy ships." << endl;
	system("pause");
	system("cls");
	game_field->show_field();
	for (int i = 0; i < 5; i++){
		cout << i << ": " << human->get_ship_coord_x(i) << " " << human->get_ship_coord_y(i) << endl;
	}
	while ( (human->get_ship_num() > 0) && (bot->get_ship_num() > 0) )
	{
		
		//->	All game engine will be here
		
		human->choose_ship();
		TryAgain:
		human->choose_action();
		if ( strcmp(human->get_choosen_action(), "i") == 0 )
		{
			
		//->	Info
		
			cout << "Getting info..." << endl;
			human->info();
			cout << endl;
			goto TryAgain;
		}
		else if ( strcmp(human->get_choosen_action(), "m") == 0 )
		{
			
		//->	Movement
			
			cout << "Enter new coordinates: " << endl;
			MoveAgain:
			human->input_new_coords();
			
			//->	ERROR: out of bounds
			if ( (human->new_coord_x < 0) || (human->new_coord_x > 8) || (human->new_coord_y < 0) || (human->new_coord_y > 8) )
			{							
				cout << "Incorrect input!" << endl;
				goto MoveAgain; 
			}
			
			//->	ERROR: ship already in place
			if ( ( human->new_coord_x == human->get_ship_coord_x(human->get_current_ship_num() ) ) && ( human->new_coord_y == human->get_ship_coord_y(human->get_current_ship_num() ) ) )
			{
				cout << "Your ship is already at this field!" << endl;													
				goto MoveAgain;
			}
			
			//->	ERROR: Ship can't move fo far 
			if ( distance(  human->get_ship_coord_x( human->get_current_ship_num() ), human->get_ship_coord_y( human->get_current_ship_num() ), human->new_coord_x, human->new_coord_y ) > human->get_ship_movement( human->get_current_ship_num() ) )
			{
					cout << "Your ship can't move so far!" << endl;	
					goto MoveAgain;
			}
			
			if (game_field->get_field(human->new_coord_x, human->new_coord_y) == '0')
			{
				game_field->set_field( human->get_ship_coord_x( human->get_current_ship_num() ), human->get_ship_coord_y( human->get_current_ship_num() ), '0' );
				human->set_ship_coords( human->get_current_ship_num(), human->new_coord_x, human->new_coord_y );
				this->draw_ship_on_field(1, human->get_current_ship_num() );				
			}
			else if ( (game_field->get_field(human->new_coord_x, human->new_coord_y) == '3') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == '1') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == '6') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == '4') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == '2') )
			{
				human->find_collided_ship_num(human->new_coord_x, human->new_coord_y);
				/*
				move_x = rand()%5 - 2;
				move_y = rand()%5 - 2;
				
				cout << move_x << " " << move_y << endl;
				
				//	ERROR!!!!!
				while ( (game_field->get_field( human->get_ship_coord_x(human->collided_ship_num)+move_x, human->get_ship_coord_y(human->collided_ship_num)+move_y ) != '0') || ( (move_x == 0) && (move_y == 0) ) || ( human->get_ship_coord_x(human->collided_ship_num)+move_x < 0 ) || ( human->get_ship_coord_x(human->collided_ship_num)+move_x > 8 ) || ( human->get_ship_coord_y(human->collided_ship_num)+move_y < 0 ) || ( human->get_ship_coord_y(human->collided_ship_num)+move_y > 8 ) || distance( human->get_ship_coord_x(human->collided_ship_num)+move_x, human->get_ship_coord_y(human->collided_ship_num)+move_y, human->get_ship_coord_x(human->collided_ship_num), human->get_ship_coord_y(human->collided_ship_num) ) > human->get_ship_movement(human->collided_ship_num) )
				{
					move_x = rand()%5 - 2;
					move_y = rand()%5 - 2;
				}
				
				cout << move_x << " " << move_y << endl;
				
				human->set_ship_coords(human->collided_ship_num, human->new_coord_x+move_x, human->new_coord_y+move_y);
				this->draw_ship_on_field(1, human->collided_ship_num );
				
				cout << human->get_ship_coord_x(human->collided_ship_num)+1 << " " << human->get_ship_coord_y(human->collided_ship_num)+1 << endl;
				
				game_field->set_field(human->get_ship_coord_x( human->get_current_ship_num() ), human->get_ship_coord_y( human->get_current_ship_num() ), '0');
				human->set_ship_coords( human->get_current_ship_num(), human->new_coord_x, human->new_coord_y);
				this->draw_ship_on_field(1, human->get_current_ship_num() );
				
				cout << human->get_ship_coord_x(human->get_current_ship_num())+1 << " " << human->get_ship_coord_y(human->get_current_ship_num())+1 << endl;
				*/			
				game_field->set_field(human->get_ship_coord_x( human->get_current_ship_num() ), human->get_ship_coord_y( human->get_current_ship_num() ), '0');
				game_field->set_field(human->get_ship_coord_x( human->collided_ship_num ), human->get_ship_coord_y( human->collided_ship_num ), '0');
				human->delete_ship(human->get_current_ship_num());
				human->delete_ship(human->collided_ship_num);
			}
			else if( (game_field->get_field(human->new_coord_x, human->new_coord_y) == 'L') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == 'l') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == 'H') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == 'h') )
			{	
				bot->find_collided_ship_num(human->new_coord_x, human->new_coord_y);
				game_field->set_field(human->get_ship_coord_x( human->get_current_ship_num() ), human->get_ship_coord_y( human->get_current_ship_num() ), '0');
				game_field->set_field(bot->get_ship_coord_x( bot->collided_ship_num ), bot->get_ship_coord_y( bot->collided_ship_num ), '0');
				human->delete_ship(human->get_current_ship_num());
				bot->delete_ship(bot->collided_ship_num);
			
			}
			this->show_turn();
		}
		else
		{
			
		//->	Attack
			
			cout << "Enter coordinates to attack: ";
			AttackAgain:
			human->input_new_coords();
			
			//->	ERROR: out of bounds
			if ( (human->new_coord_x < 0) || (human->new_coord_x > 8) || (human->new_coord_y < 0) || (human->new_coord_y > 8) )
			{							
				cout << "Incorrect input!" << endl;
				goto AttackAgain; 
			}
			
			//-> 	ERROR: shooting on empty field
			if (game_field->get_field(human->new_coord_x, human->new_coord_y) == '0')
			{
				cout << "Do you really want to kill water???" << endl;
				goto AttackAgain;
			}
			
			//->	ERROR: out of shooting range
			if ( distance( human->get_ship_coord_x( human->get_current_ship_num() ), human->get_ship_coord_y( human->get_current_ship_num() ), human->new_coord_x, human->new_coord_y ) > ( human->get_ship_attack_radius( human->get_current_ship_num() ) ) )
			{
				cout << "Out of shooting range!" << endl;
				goto AttackAgain;
			}
			
			//->	ERROR: Attack yourself
			if ( ( human->get_ship_coord_x( human->get_current_ship_num() ) == human->new_coord_x ) && ( human->get_ship_coord_y( human->get_current_ship_num() ) == human->new_coord_y ) )
			{
				cout << "Ship can't attack itself!" << endl;
				goto AttackAgain;	
			}
			else if ( (game_field->get_field(human->new_coord_x, human->new_coord_y) == '3') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == '1') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == '6') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == '4') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == '2') )
			{
				human->find_collided_ship_num(human->new_coord_x, human->new_coord_y);
				human->set_ship_HP( human->collided_ship_num, human->get_ship_damage( human->get_current_ship_num() ) );
				this->draw_ship_on_field(1, human->collided_ship_num);
				if (human->get_ship_HP(human->collided_ship_num) <= 0)
				{
					human->delete_ship(human->collided_ship_num);
				}
			}
			
			if ( (game_field->get_field(human->new_coord_x, human->new_coord_y) == 'L') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == 'l') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == 'H') || (game_field->get_field(human->new_coord_x, human->new_coord_y) == 'h') )
			{
				bot->find_collided_ship_num(human->new_coord_x, human->new_coord_y);
				bot->set_ship_HP(bot->collided_ship_num, human->get_ship_damage( human->get_current_ship_num() ) );
				this->draw_ship_on_field(2, bot->collided_ship_num);
				if (bot->get_ship_HP(bot->collided_ship_num) <= 0)
				{
					bot->delete_ship(bot->collided_ship_num);
				}
			}
			
			this->show_turn();
		}
	}
}
	


