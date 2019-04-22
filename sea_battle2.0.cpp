#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <windows.h>

/*
	Ship не должен наследоваться от field
	Сделать класс, содержащий в виде переменных массив кораблей и поле
	Убрать игровую логику из main в класс игрока и класс бота (возможно с наследованием)
	Функции вне main переместить в field
	Заставить ботов сражаться друг с другом
	Сделать разные уровни сложности
	Разбить на файлы
	Покрасить корабли разных игроков в разные цвета для наглядности
*/

using namespace std;

class ship;
ship* player_ships[5];
ship* computer_ships[5];
ship* temp;

class field{																								//Описание класса игровое поле
	protected:
		char sea[9][9];
	public:
		void field_generation(){
			for (int i = 0; i < 9; i++){
				for(int j = 0; j < 9; j++){
					sea[i][j] = '0';
				}
			}
		}
		void light_ships_generation(){																		//Рассстановка кораблей
			srand(time(NULL));																				//.
			int _x, _y;																						//.
			for (int i = 0; i < 3; i++){																	//.
				_x = rand()%9;																				//.
				_y = rand()%2;																				//.
				while (get_field(_x, _y) != '0'){															//.
					_x = rand()%9;																			//.
					_y = rand()%2;																			//.
				}																							//.
				sea[_x][_y] = '3';																			//.
			}																								//.
		}																									//.
		void heavy_ships_generation(){																		//.
			srand(time(NULL));																				//.
			int _x, _y;																						//.
			for (int i = 0; i < 2; i++){																	//.
				_x = rand()%9;																				//.
				_y = rand()%2;																				//.
				while (get_field(_x, _y) != '0'){															//.
					_x = rand()%9;																			//.
					_y = rand()%2;																			//.
				}																							//.
				sea[_x][_y] = '6';																			//.
			}																								//.
		}																									//.
		void comp_light_ships_generation(){																	//.
			srand(time(NULL));																				//.
			int _x, _y;																						//.
			for (int i = 0; i < 3; i++){																	//.
				_x = rand()%9;																				//.
				_y = rand()%2 + 7;																			//.
				while ((get_field(_x, _y) != '0') || (get_field(_x, _y-7) != '0')){							//.
					_x = rand()%9;																			//.
					_y = rand()%2 + 7;																		//.
				}																							//.
				sea[_x][_y] = 'L';																			//.
			}																								//.
		}																									//.
		void comp_heavy_ships_generation(){																	//.
			srand(time(NULL));																				//.
			int _x, _y;																						//.
			for (int i = 0; i < 2; i++){																	//.
				_x = rand()%9;																				//.
				_y = rand()%2 + 7;																			//.
				while ((get_field(_x, _y) != '0') || (get_field(_x, _y-7) != '0')){							//.
					_x = rand()%9;																			//.
					_y = rand()%2 + 7;																		//.
				}																							//.
				sea[_x][_y] = 'H';																			//.
			}																								//.
		}																									//.
		void all_ships_generation(){																		//.
			light_ships_generation();																		//.
			heavy_ships_generation();																		//.
			comp_light_ships_generation();																	//.
			comp_heavy_ships_generation();																	//.
		}																									//Конец расстановки
		char get_field(int x, int y){
			return sea[x][y];
		}
		void set_field(int _x, int _y, char c){
			sea[_x][_y] = c;
		}
		void show_field(){																					//Показ поля
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
};

class ship: public field{																					//Описание класса корабль
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
		ship(){}
		virtual ~ship(){
			priority = -1000;
		}
		bool is_alive(){
			return alive;
		}
		void show_info(){
			cout << HP << endl << movement << endl << damage << endl;
		}
		int get_HP(){
			return HP;
		}
		void set_HP(int dam){
			HP = HP - dam;
		}
		int get_damage(){
			return damage;
		}
		int get_attack_radius(){
			return attack_radius;
		}
		int get_movement(){
			return movement;
		}
		void set_coords(int _x, int _y){
			x = _x;
			y = _y;
		}
		int get_coord_x(){
			return x;
		}
		int get_coord_y(){
			return y;
		}
		void show_coords(){
			cout << "(" << this->get_coord_x()+1 << ", " << this->get_coord_y()+1 << ")" << endl;
		}
		int get_type(){
			return type;
		}
		void set_priority(int x){
			priority = x;
		}		
		int get_priority(){
			return priority;
		}
		void info(){
			cout << "Type: " << type << endl <<
			"HP: " << HP << endl <<
			"Movement: " << movement << endl <<
			"Damage: " << damage << endl <<
			"Attack radius: " << attack_radius << endl;
		} 
};

class light_ship : public ship{																				//Легкий корабль	
	public:
		light_ship(){
			this->HP = 3;
			this->type = 1;
			this->movement = 2;
			this->damage = 2;
			this->attack_radius = 2;
			this->priority = 0;
			this->alive = true;
		}
		~light_ship(){
			cout << "Light ship on (" << x+1 << ", " << y+1 << ") was destroyed." << endl;
		}
};
class heavy_ship : public ship{																				//Тяжелый корабль
	public:
		heavy_ship(){
			this->HP = 6;
			this->type = 2;
			this->movement = 1;
			this->damage = 4;
			this->attack_radius = 3;
			this->priority = 0;
			this->alive = true;
		}
		~heavy_ship(){
			cout << "Heavy ship on (" << x+1 << ", " << y+1 << ") was destroyed." << endl;
		}
};

float distance(int x, int y, int _x, int _y){																//Расстояние между точками
	float dist = sqrt( pow( (_x - x),2 ) + pow( (_y - y),2 ) );
	return dist;
}

bool safe(int x, int y){
	bool safe_field = true;
	for (int i = 0; i < 5; i++){
		if ( distance(player_ships[i]->get_coord_x(), player_ships[i]->get_coord_y(), x, y ) <= player_ships[i]->get_attack_radius() ){
			safe_field = false;
		}	
	}
	return safe_field;
}

field game_field;

int main(){
	int turn = 0;
	int l1, h1, l2, h2;
	int player_num = 4;
	int computer_num = 4;
	int ship_num = -1;
	int computer_ship_num;
	int collided_num;
	int max_priority = 0;
	int min_distance = 10;
	int min_friend_distance = 100;
	int coord_x, coord_y;
	int move_x, move_y;
	int reply;
	bool is_safe = false;
	bool is_breaked = false;
	bool is_destroyed = false;
	char step[1];
	l1 = 0;
	h1 = 3;
	l2 = 0;
	h2 = 3;
	game_field.field_generation();																			//Создание поля
	game_field.all_ships_generation();																		//Расстановка кораблей на поле
	for (int i = 0; i < 5; i++){																			//Создание кораблей
		if (i < 3){
			player_ships[i] = new light_ship;
			computer_ships[i] = new light_ship; 			
		}
		else{
			player_ships[i] = new heavy_ship;
			computer_ships[i] = new heavy_ship; 
		}
	}
	for (int i = 0; i < 9; i++){																			//Привязка кораблей к полю
				for(int j = 0; j < 9; j++){
					if (game_field.get_field(i, j) == '3'){
						player_ships[l1]->set_coords(i, j);
						l1++;
					}
					else if(game_field.get_field(i, j) == '6'){
						player_ships[h1]->set_coords(i, j);
						h1++;
					}
					else if(game_field.get_field(i, j) == 'L'){
						computer_ships[l2]->set_coords(i, j);
						l2++;
					}
					else if(game_field.get_field(i, j) == 'H'){
						computer_ships[h2]->set_coords(i, j);
						h2++;
					}
				}
			}
	cout << 
		"SEA BATTLE" << endl <<
		"There are two types of ships: light (L) and heavy (H). Each player has 3 light and 2 heavy ships." << endl <<
		"Different types have different characteristic. " << endl << endl <<
		"Light ships: "<< endl;
		player_ships[0]->info();
	cout << endl <<
		"Heavy ships: "<< endl;
		player_ships[4]->info();
	cout << endl <<
		"On the field you can see HP of each your ship. " << endl <<
		"You can see only type of enemy ships. Type is marked by a uppercase letter. Damaged ships marked by a lowercase letter." << endl <<
		"Your goal is to destroy all enemy ships." << endl;
	system("pause");
	system("cls");
	while ((player_num >= 0) && (computer_num >= 0)){														//Описание хода
		turn++;
		cout << "Turn: " << turn << endl;
		game_field.show_field();
		
		//----------ХОД ИГРОКА----------
		
		cout << "Choose ship: enter ship coordinates: ";													//Выбор корабля
		cin >> coord_x >> coord_y;
		for (int i = 0; i <= player_num; i++){																			
			if ((player_ships[i]->get_coord_x() == coord_x - 1) && (player_ships[i]->get_coord_y() == coord_y - 1)){
				ship_num = i;
			}
		}
		while (ship_num == -1){
			cout << "No ship on this field" << endl << 
			"Choose ship: enter ship coordinates: ";
			cin >> coord_x >> coord_y;
			for (int i = 0; i <= player_num; i++){																			
				if ((player_ships[i]->get_coord_x() == coord_x - 1) && (player_ships[i]->get_coord_y() == coord_y - 1)){
					ship_num = i;
				}
			}
		}
		TryAgain:
		cout << "Do you want to move or attack?" << endl <<													//Выбор действия
		"Enter 'm' to move or 'a' to attack or 'i' to get info about your ships: ";
		cin >> step;
		while(true){
			if ((strcmp(step, "a") == 0) || (strcmp(step, "m") == 0) || (strcmp(step, "i") == 0) ){
				break;
			}
			else{
				cout << "Incorrect input! Try again: ";
				cin >> step;
			}
		}
		if (strcmp(step, "i") == 0){
			for (int i = 0; i <= player_num; i++){
				cout << "Getting info..." << endl;
				Sleep(1500);
				cout << "Ship number " << i+1 << ":" << endl;
				player_ships[i]->info();
				cout << endl;
			}
			goto TryAgain;
		}
		if (strcmp(step, "a") == 0){																		//Атака	
			cout << "Enter coordinates to attack: ";
			cin >> coord_x >> coord_y;	
			while ( (coord_x < 1) || (coord_x > 9) || (coord_y < 1) || (coord_y > 9) ){							//Ошибка: выход за рамки
				cout << "Incorrect input! Try again!";
				goto TryAgain;
			}
			while ( (game_field.get_field(coord_x-1, coord_y-1) == '0') ){										//Ошибка: стрельба по воде
				cout << "This field is empty. Do you really want to kill water???" << endl;
				goto TryAgain;
			}
			while ( (game_field.get_field(coord_x-1, coord_y-1) == '3') || (game_field.get_field(coord_x-1, coord_y-1) == '1') || (game_field.get_field(coord_x-1, coord_y-1) == '6') || (game_field.get_field(coord_x-1, coord_y-1) == '4') || (game_field.get_field(coord_x-1, coord_y-1) == '2') ){										
				cout << "You want to attack friendly ship!!!" << endl;											//Ошибка: стрельба по своим
				goto TryAgain;
			}
			while (distance( player_ships[ship_num]->get_coord_x()+1, player_ships[ship_num]->get_coord_y()+1, coord_x, coord_y) > player_ships[ship_num]->get_attack_radius() ){
				cout << "Exceeded shooting range! Try again!";													//Ошибка: ограничение дальности стрельбы
				goto TryAgain; 
			}
			if ( (game_field.get_field(coord_x-1, coord_y-1) == 'L') || (game_field.get_field(coord_x-1, coord_y-1) == 'l') || (game_field.get_field(coord_x-1, coord_y-1) == 'H') || (game_field.get_field(coord_x-1, coord_y-1) == 'h') ){
				for (int i = 0; i <= computer_num; i++){														//Попадание																	
					if ( (computer_ships[i]->get_coord_x() == coord_x - 1) && (computer_ships[i]->get_coord_y() == coord_y - 1) ){
						computer_ship_num = i;
					}
				}
				computer_ships[computer_ship_num]->set_HP( player_ships[ship_num]->get_damage() );
				cout << "Commander: " << "Ship " << ship_num+1 << ", attack enemy on (" << coord_x << ", " << coord_y << "). Over." << endl;
				Sleep(3000); 
				cout << "Ship " << ship_num+1 << ": Roger that, Commander. Putting the gun on the target..." << endl;
				Sleep(3000);
				cout << "Ship " << ship_num+1 << ": Enemy ship on (" << coord_x << ", " << coord_y << ") took " << player_ships[ship_num]->get_damage() << " damage." << endl;
				if ( (game_field.get_field(coord_x-1, coord_y-1) == 'L') ){
					game_field.set_field(coord_x-1, coord_y-1, 'l');
				}
				if ( (game_field.get_field(coord_x-1, coord_y-1) == 'H') ){
					game_field.set_field(coord_x-1, coord_y-1, 'h');
				}
				if (computer_ships[computer_ship_num]->get_HP() <= 0){
					game_field.set_field(coord_x-1, coord_y-1, '0');
					temp = computer_ships[computer_num];
					computer_ships[computer_num] = computer_ships[computer_ship_num];
					computer_ships[computer_ship_num] = temp; 
					Sleep(3000); 
					cout << "Ship " << ship_num+1 << ": ";
					delete computer_ships[computer_num];
					computer_num--;
				}
			}
			
		}
		else if (strcmp(step, "m") == 0){																	//Движение		
			cout << "Enter new coordinates: ";
			cin >> coord_x >> coord_y; 
			while ( (coord_x < 1) || (coord_x > 9) || (coord_y < 1) || (coord_y > 9) ){							//Ошибка: выход за рамки
				cout << "Incorrect input! Try again: ";
				cin >> coord_x >> coord_y; 
			}
			while ( ( coord_x-1 == player_ships[ship_num]->get_coord_x() ) && ( coord_y-1 == player_ships[ship_num]->get_coord_y() ) ){
				cout << "Your ship is already at this field! Try again: ";										//Ошибка: корабль уже на месте
				cin >> coord_x >> coord_y;
			}
			while (distance( player_ships[ship_num]->get_coord_x()+1, player_ships[ship_num]->get_coord_y()+1, coord_x, coord_y) > player_ships[ship_num]->get_movement()){
					cout << "Your ship can't move so far! Enter new coordinates: ";								//Ошибка: ограничение передвижения
					cin >> coord_x >> coord_y; 
			}
			if (game_field.get_field(coord_x-1, coord_y-1) == '0'){												//Корадль переместился
				cout << "Commander: " << "Ship " << ship_num+1 << ", move to (" << coord_x << ", " << coord_y << "). Over." << endl;
				Sleep(3000); 
				cout << "Ship " << ship_num+1 << ": Roger that, Commander. I am on the way..." << endl;
				game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '0' );
				player_ships[ship_num]->set_coords(coord_x-1, coord_y-1);
				if(player_ships[ship_num]->get_HP() == 3){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '3' );
				}
				if(player_ships[ship_num]->get_HP() == 1){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '1' );
				}
				if(player_ships[ship_num]->get_HP() == 6){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '6' );
				}
				if(player_ships[ship_num]->get_HP() == 4){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '4' );
				}
				if(player_ships[ship_num]->get_HP() == 2){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '2' );
				}
			}
			else if( (game_field.get_field(coord_x-1, coord_y-1) == '3') || (game_field.get_field(coord_x-1, coord_y-1) == '1') || (game_field.get_field(coord_x-1, coord_y-1) == '6') || (game_field.get_field(coord_x-1, coord_y-1) == '4') || (game_field.get_field(coord_x-1, coord_y-1) == '2') ){
				for (int i = 0; i <= player_num; i++){															//Столкновение со своим кораблем
					if ((player_ships[i]->get_coord_x() == coord_x - 1) && (player_ships[i]->get_coord_y() == coord_y - 1)){
						collided_num = i;
					}
				}
				cout << "Commander: " << "Ship " << ship_num+1 << ", move to (" << coord_x << ", " << coord_y << "). Over." << endl;
				Sleep(3000);
				cout << "Ship " << ship_num+1 << ": Roger that, Commander. I am on the way..." << endl;
				Sleep(3000);
				cout << "Ship " << ship_num+1 << ": Allied ship in front!" << endl;
				Sleep(4000);
				cout << "Ship " << collided_num+1 << ": Ship " << ship_num+1 << ", You are moving right towards us! Change course immediately!" << endl;
				Sleep(4000);
				cout << "Ship " << ship_num+1 << ": Ship " << collided_num+1 << ", Can't change my course! Get out of the way!" << endl;	
				Sleep(3000);											
				move_x = rand()%5 - 2;
				move_y = rand()%5 - 2;
				while ( ( game_field.get_field(player_ships[collided_num]->get_coord_x()+move_x, player_ships[collided_num]->get_coord_y()+move_y) != '0' ) || ( (move_x == 0) && (move_y == 0) ) || ( player_ships[collided_num]->get_coord_x()+move_x < 0 ) || ( player_ships[collided_num]->get_coord_x()+move_x >=9 ) || ( player_ships[collided_num]->get_coord_y()+move_y < 0 ) || ( player_ships[collided_num]->get_coord_y()+move_y >= 9 ) || ( distance( player_ships[collided_num]->get_coord_x()+move_x, player_ships[collided_num]->get_coord_y()+move_y, player_ships[collided_num]->get_coord_x(), player_ships[collided_num]->get_coord_y() ) > player_ships[collided_num]->get_movement() ) ){
					move_x = rand()%5 - 2;
					move_y = rand()%5 - 2;
				}
				player_ships[collided_num]->set_coords(player_ships[collided_num]->get_coord_x()+move_x, player_ships[collided_num]->get_coord_y()+move_y);
				cout << "Ship " << collided_num+1 << ": Moving to (" << player_ships[collided_num]->get_coord_x()+1 << ", " << player_ships[collided_num]->get_coord_y()+1 << ")..." << endl;
				if(player_ships[collided_num]->get_HP() == 3){
					game_field.set_field( player_ships[collided_num]->get_coord_x(), player_ships[collided_num]->get_coord_y(), '3' );
				}
				if(player_ships[collided_num]->get_HP() == 1){
					game_field.set_field( player_ships[collided_num]->get_coord_x(), player_ships[collided_num]->get_coord_y(), '1' );
				}
				if(player_ships[collided_num]->get_HP() == 6){
					game_field.set_field( player_ships[collided_num]->get_coord_x(), player_ships[collided_num]->get_coord_y(), '6' );
				}
				if(player_ships[collided_num]->get_HP() == 4){
					game_field.set_field( player_ships[collided_num]->get_coord_x(), player_ships[collided_num]->get_coord_y(), '4' );
				}
				if(player_ships[collided_num]->get_HP() == 2){
					game_field.set_field( player_ships[collided_num]->get_coord_x(), player_ships[collided_num]->get_coord_y(), '2' );
				}
				
				game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '0' );
				player_ships[ship_num]->set_coords(coord_x-1, coord_y-1);
				if(player_ships[ship_num]->get_HP() == 3){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '3' );
				}
				if(player_ships[ship_num]->get_HP() == 1){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '1' );
				}
				if(player_ships[ship_num]->get_HP() == 6){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '6' );
				}
				if(player_ships[ship_num]->get_HP() == 4){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '4' );
				}
				if(player_ships[ship_num]->get_HP() == 2){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '2' );
				}
			}
			else if( (game_field.get_field(coord_x-1, coord_y-1) == 'L') || (game_field.get_field(coord_x-1, coord_y-1) == 'l') || (game_field.get_field(coord_x-1, coord_y-1) == 'H') || (game_field.get_field(coord_x-1, coord_y-1) == 'h') ){
				cout << "Commander: " << "Ship " << ship_num+1 << ", move to (" << coord_x << ", " << coord_y << "). Over." << endl;
				Sleep(3000);																					//Таран вражеского корабля
				cout << "Ship " << ship_num+1 << ": Enemy ship in front! Ram it!" << endl;
				Sleep(3000);
				cout << "Ship " << ship_num+1 << ": We rammed an enemy ship! We are sinking!" << endl;	
				for (int i = 0; i <= computer_num; i++){																			
					if ((computer_ships[i]->get_coord_x() == coord_x - 1) && (computer_ships[i]->get_coord_y() == coord_y - 1)){
						collided_num = i;
					}
				}
				game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '0' );
				game_field.set_field( computer_ships[collided_num]->get_coord_x(), computer_ships[collided_num]->get_coord_y(), '0' );
				temp = player_ships[player_num];
				player_ships[player_num] = player_ships[ship_num];
				player_ships[ship_num] = temp;
				Sleep(3000); 
				cout << "Assistant: ";
				delete player_ships[player_num];
				player_num--;
				temp = computer_ships[computer_num];
				computer_ships[computer_num] = computer_ships[collided_num];
				computer_ships[collided_num] = temp; 
				cout << "Assistant: ";
				delete computer_ships[computer_num];
				computer_num--;
			}
		}
		system("pause");
		system ("cls");
		cout << "Turn: " << turn << endl;
		game_field.show_field();
		
		
		//----------ХОД КОМПЬЮТЕРА----------
		
		if ( (computer_num < 0) || (player_num < 0) ){
			break;
		}
		cout << "Computer turn... " << endl;
		Sleep(3000);
		for (int i = 0; i <= computer_num; i++){																		//Установка приоритета
			if (computer_ships[i]->is_alive() == true) {
				if ( (computer_ships[i]->get_HP() <= 2) && (computer_ships[i]->get_HP() > 0) ){
					computer_ships[i]->set_priority(200);
				}
				for (int t = 0; t <= computer_num; t++){
					if ( distance( computer_ships[i]->get_coord_x(), computer_ships[i]->get_coord_y(), computer_ships[t]->get_coord_x(), computer_ships[t]->get_coord_y() ) < min_friend_distance){
						min_friend_distance = distance( computer_ships[i]->get_coord_x(), computer_ships[i]->get_coord_y(), computer_ships[t]->get_coord_x(), computer_ships[t]->get_coord_y() );
					}
				}
				if ( min_friend_distance < 2*computer_ships[i]->get_movement() ){
					computer_ships[i]->set_priority(300);												//Далеко от своих
				}
				else{
					computer_ships[i]->set_priority(500);
				}
				
				for (int j = 0; j <= player_num; j ++){
					
					//Раненый под обстрелом
					
					if ( (computer_ships[i]->get_HP() <= 2) && ( distance( computer_ships[i]->get_coord_x(), computer_ships[i]->get_coord_y(), player_ships[j]->get_coord_x(), player_ships[j]->get_coord_y() ) <= player_ships[j]->get_attack_radius() ) ){
							computer_ships[i]->set_priority(700);												
					}
					
					//Если под обстрелом
					
					if ( distance( computer_ships[i]->get_coord_x(), computer_ships[i]->get_coord_y(), player_ships[j]->get_coord_x(), player_ships[j]->get_coord_y() ) <= player_ships[j]->get_attack_radius() ){
						computer_ships[i]->set_priority(800);
					}
					
					//Может атаковать
					
					if ( distance( computer_ships[i]->get_coord_x(), computer_ships[i]->get_coord_y(), player_ships[j]->get_coord_x(), player_ships[j]->get_coord_y() ) <= computer_ships[i]->get_attack_radius() ){
						if ( (player_ships[j]->get_HP() - computer_ships[i]->get_damage()) > 0 ){
							computer_ships[i]->set_priority(850);																								
						}
					}
					
					//Раненый может протаранить
					
					if ( (computer_ships[i]->get_HP() <= 2)){
						if ( (distance( computer_ships[i]->get_coord_x(), computer_ships[i]->get_coord_y(), player_ships[j]->get_coord_x(), player_ships[j]->get_coord_y() ) <= computer_ships[i]->get_movement() ) && (computer_ships[i]->get_HP() > 0) ){
							computer_ships[i]->set_priority(900);												
						}	
					}
					
					//Может потопить	
					
					if ( distance( computer_ships[i]->get_coord_x(), computer_ships[i]->get_coord_y(), player_ships[j]->get_coord_x(), player_ships[j]->get_coord_y() ) <= computer_ships[i]->get_attack_radius() ){
						if ( (player_ships[j]->get_HP() - computer_ships[i]->get_damage()) <= 0 ){
							computer_ships[i]->set_priority(1000);	
							break;																							
						}
					}
				}
			}	
		}
		computer_ship_num = rand()%5;																		//Выбор корабля
		max_priority = computer_ships[computer_ship_num]->get_priority();
		for (int i = 0; i <= computer_num; i++){
			if ( computer_ships[i]->is_alive() == true){
				if ( computer_ships[i]->get_priority() == -1000 ){
					continue;
				}
				if (computer_ships[i]->get_priority() > max_priority){
					max_priority = computer_ships[i]->get_priority();
					computer_ship_num = i;
				}	
			}
			else{
				continue;
			}
		}			
		if (max_priority == 1000){		//Работает															//Ходы
			for (int j = 0; j <= player_num; j++){
				if ( distance( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), player_ships[j]->get_coord_x(), player_ships[j]->get_coord_y() ) <= computer_ships[computer_ship_num]->get_attack_radius() ){
					if ( (player_ships[j]->get_HP() - computer_ships[computer_ship_num]->get_damage()) <= 0 ){
						ship_num = j;
						break;
					}
				}
			}
			player_ships[ship_num]->set_HP( computer_ships[computer_ship_num]->get_damage() );
			cout << "Ship " << ship_num+1 << ": We are under attack!" << endl;
			Sleep(3000);
			cout << "Commander: Ship " << ship_num+1 << ", report about damage. Over." << endl;
			Sleep(5000);
			cout << "Commander: Ship " << ship_num+1 << ", do you copy?" << endl;
			Sleep(3000);
			if (player_num > 0){
				reply = rand()%5;
					while ( (reply == ship_num) ){
						reply = rand()%5;
					}
				cout << "Ship " << reply+1 << ": Ship " << ship_num+1 << " took " << computer_ships[computer_ship_num]->get_damage() << " damege. They are sinking!" << endl;
			}
			else{
				cout << "Assistant: Ship " << ship_num+1 << " took " << computer_ships[computer_ship_num]->get_damage() << " damege. They are sinking!" << endl;
			}
			game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '0' );
			temp = player_ships[player_num];
			player_ships[player_num] = player_ships[ship_num];
			player_ships[ship_num] = temp;
			Sleep(3000); 
			if (player_num > 0){
				cout << "Ship " << reply+1 << ": ";
			}
			else{
				cout << "Assistant: ";
			}
			delete player_ships[player_num];
			player_num--;
			system("pause");
		}
		else if (max_priority == 900){	//Работает
			for (int j = player_num; j >= 0; j--){   	 
				if ( distance( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), player_ships[j]->get_coord_x(), player_ships[j]->get_coord_y() ) <= computer_ships[computer_ship_num]->get_movement() ){
					cout << "Ship " << ship_num+1 << ": The enemy ship is heading straight for us!!!" << endl;
					Sleep(3000);
					cout << "Commander: Ship " << ship_num+1 << ", report on your status. Over." << endl;
					Sleep(5000);
					cout << "Commander: Ship " << ship_num+1 << ", do you copy?" << endl;
					Sleep(3000);
					cout << "Ship " << ship_num+1 << ": .................." << endl;
					Sleep(3000);
					if (player_num > 0){
						reply = rand()%5;
							while ( (reply == ship_num) ){
								reply = rand()%5;
							}
						cout << "Ship " << reply+1 << ": The enemy rammed ship " << ship_num+1 << "!" << endl;
					}
					else{
						cout << "Assistant: The enemy rammed ship " << ship_num+1 << " " << endl;
					}
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					game_field.set_field( player_ships[j]->get_coord_x(), player_ships[j]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_priority(-1000);
					temp = computer_ships[computer_num];
					computer_ships[computer_num] = computer_ships[computer_ship_num];
					computer_ships[computer_ship_num] = temp;
					Sleep(3000); 
					if (player_num > 0){
						cout << "Ship " << reply+1 << ": ";
					}
					else{
						cout << "Assistant: ";
					}
					delete computer_ships[computer_num];
					computer_num--;
					temp = player_ships[player_num];
					player_ships[player_num] = player_ships[j];
					player_ships[j] = temp;
					if (player_num > 0){
						cout << "Ship " << reply+1 << ": ";
					}
					else{
						cout << "Assistant: ";
					}
					delete player_ships[player_num];
					player_num--;
					system("pause");
					break;
				}
			}
		}
		else if (max_priority == 850){	//Работает
			for (int j = 0; j <= player_num; j++){
				if ( distance( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), player_ships[j]->get_coord_x(), player_ships[j]->get_coord_y() ) <= computer_ships[computer_ship_num]->get_attack_radius() ){
					ship_num = j;
				}
			}
			player_ships[ship_num]->set_HP( computer_ships[computer_ship_num]->get_damage() );
			cout << "Ship " << ship_num+1 << ": We are under attack!" << endl;
			Sleep(3000);
			cout << "Commander: Ship " << ship_num+1 << ", report about damage. Over." << endl;
			Sleep(3000);
			cout << "Ship " << ship_num+1 << ": We took " << computer_ships[computer_ship_num]->get_damage() << " damege, but we can continue the fight." << endl;
			system("pause");
			if ( computer_ships[computer_ship_num]->get_damage() == 2 ){
				if ( game_field.get_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y() ) == '3' ){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '1' );
				}
				if ( game_field.get_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y() ) == '4' ){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '2' );
				}	
				if ( game_field.get_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y() ) == '6' ){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '4' );
				}
			}
			else if( computer_ships[computer_ship_num]->get_damage() == 4 ){
				if ( game_field.get_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y() ) == '6' ){
					game_field.set_field( player_ships[ship_num]->get_coord_x(), player_ships[ship_num]->get_coord_y(), '2' );
				}
			}
		}
		else if (max_priority == 800){	//Работает, но это не точно
			for (int dx = 2; dx > -3; dx--){
				for(int dy = 2; dy > -3; dy--){
					if ( (computer_ships[computer_ship_num]->get_coord_x()+dx >= 0) && (computer_ships[computer_ship_num]->get_coord_x()+dx < 9) && (computer_ships[computer_ship_num]->get_coord_y()+dy >= 0) && (computer_ships[computer_ship_num]->get_coord_y()+dy < 9) && (safe(computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy) == true) && (game_field.get_field(computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy) == '0') && ( distance( computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy, computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) <= computer_ships[computer_ship_num]->get_movement() ) ){
						move_x = dx;
						move_y = dy;
						is_safe = true;
						is_breaked = true;
						break;
					}	
				}
				if (is_breaked == true){
					break;
				}
			}
			if (is_safe == true){
				if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'L' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'L' );
				}
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'l' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'l' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'H' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'H' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'h' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'h' );
				}
			}
			else{
				move_x = rand()%5 - 2;
				move_y = rand()%5 - 2;
				while ( ( game_field.get_field(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y) != '0' ) || ( (move_x == 0) && (move_y == 0) ) || ( computer_ships[computer_ship_num]->get_coord_x()+move_x < 0 ) || ( computer_ships[computer_ship_num]->get_coord_x()+move_x >=9 ) || ( computer_ships[computer_ship_num]->get_coord_y()+move_y < 0 ) || ( computer_ships[computer_ship_num]->get_coord_y()+move_y >= 9 ) || ( distance( computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y, computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) > computer_ships[computer_ship_num]->get_movement() ) ){
					move_x = rand()%5 - 2;
					move_y = rand()%5 - 2;
				}
				if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'L' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'L' );
				}
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'l' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'l' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'H' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'H' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'h' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'h' );
				}
			}
		}
		else if (max_priority == 700){	//Наверное работает
			for (int dx = 2; dx > -3; dx--){
				for(int dy = 2; dy > -3; dy--){
					if ( (computer_ships[computer_ship_num]->get_coord_x()+dx >= 0) && (computer_ships[computer_ship_num]->get_coord_x()+dx < 9) && (computer_ships[computer_ship_num]->get_coord_y()+dy >= 0) && (computer_ships[computer_ship_num]->get_coord_y()+dy < 9) && (safe(computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy) == true) && (game_field.get_field(computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy) == '0') && ( distance( computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy, computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) <= computer_ships[computer_ship_num]->get_movement() ) ){
						move_x = dx;
						move_y = dy;
						is_safe = true;
						is_breaked = true;
						break;
					}	
				}
				if (is_breaked == true){
					break;
				}
			}
			if (is_safe == true){
				if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'L' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'L' );
				}
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'l' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'l' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'H' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'H' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'h' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'h' );
				}
			}
			else{
				move_x = rand()%5 - 2;
				move_y = rand()%5 - 2;
				while ( ( game_field.get_field(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y) != '0' ) || (move_x == 0) || (move_y == 0) || ( computer_ships[computer_ship_num]->get_coord_x()+move_x < 0 ) || ( computer_ships[computer_ship_num]->get_coord_x()+move_x >=9 ) || ( computer_ships[computer_ship_num]->get_coord_y()+move_y < 0 ) || ( computer_ships[computer_ship_num]->get_coord_y()+move_y >= 9 ) || ( distance( computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y, computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) > computer_ships[computer_ship_num]->get_movement() ) ){
					move_x = rand()%5 - 2;
					move_y = rand()%5 - 2;
				}
				if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'L' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'L' );
				}
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'l' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'l' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'H' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'H' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'h' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'h' );
				}
			}
		}
		else if (max_priority == 500){	//Хз работает ли
			for (int t = computer_num+1; t > 0; t--){
				if ( distance( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), computer_ships[t]->get_coord_x(), computer_ships[t]->get_coord_y() ) > 2*computer_ships[computer_ship_num]->get_movement() ){
					for (int dx = -2; dx < 3; dx++ ){
						for (int dy = -2; dy < 3; dy ++){
							if ( ( distance( computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy, computer_ships[t]->get_coord_x(), computer_ships[t]->get_coord_y() ) < min_distance ) && (game_field.get_field(computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy) == '0') && ( distance( computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy, computer_ships[t]->get_coord_x(), computer_ships[t]->get_coord_y() ) < computer_ships[computer_ship_num]->get_movement() ) ){
								min_distance = distance( computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy, computer_ships[t]->get_coord_x(), computer_ships[t]->get_coord_y() );
								coord_x = computer_ships[computer_ship_num]->get_coord_x()+dx;
								coord_y = computer_ships[computer_ship_num]->get_coord_y()+dy;
								
							}
						}						
					}
					if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'L' ){
						game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
						computer_ships[computer_ship_num]->set_coords(coord_x, coord_y);
						game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'L' );
					}
					else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'l' ){
						game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
						computer_ships[computer_ship_num]->set_coords(coord_x, coord_y);
						game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'l' );
					}
					else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'H' ){
						game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
						computer_ships[computer_ship_num]->set_coords(coord_x, coord_y);
						game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'H' );
					}
					else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'h' ){
						game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
						computer_ships[computer_ship_num]->set_coords(coord_x, coord_y);
						game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'h' );
					}
					break;
				}
			}
		}
		else if (max_priority == 300){
			for (int dy = -2; dy < 3; dy++){
				for(int dx = -2; dx < 3; dx++){
					if ( ( computer_ships[computer_ship_num]->get_coord_x()+dx < 0 ) || ( computer_ships[computer_ship_num]->get_coord_x()+dx >=9 ) || ( computer_ships[computer_ship_num]->get_coord_y()+dy < 0 ) || ( computer_ships[computer_ship_num]->get_coord_y()+dy >= 9 ) ){
						continue;
					}
					else if ( (computer_ships[computer_ship_num]->get_coord_x()+dx >= 0) && (computer_ships[computer_ship_num]->get_coord_x()+dx < 9) && (computer_ships[computer_ship_num]->get_coord_y()+dy >= 0) && (computer_ships[computer_ship_num]->get_coord_y()+dy < 9) && (safe(computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy) == true) && (game_field.get_field(computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy) == '0') && ( distance( computer_ships[computer_ship_num]->get_coord_x()+dx, computer_ships[computer_ship_num]->get_coord_y()+dy, computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) <= computer_ships[computer_ship_num]->get_movement() ) ){
						move_x = dx;
						move_y = dy;
						is_safe = true;
						is_breaked = true;
						break;
					}	
				}
				if (is_breaked == true){
					break;
				}
			}
			//Самое примитивное хождение
			/*is_safe = true;
			if ( game_field.get_field(computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y()-computer_ships[computer_ship_num]->get_movement() ) == '0' ){
				move_x = 0;
				move_y = -computer_ships[computer_ship_num]->get_movement();
			}
			else if( game_field.get_field(computer_ships[computer_ship_num]->get_coord_x()-computer_ships[computer_ship_num]->get_movement(), computer_ships[computer_ship_num]->get_coord_y() ) == '0' ){
				move_x = -computer_ships[computer_ship_num]->get_movement();
				move_y = 0;
			}
			else if( game_field.get_field(computer_ships[computer_ship_num]->get_coord_x()+computer_ships[computer_ship_num]->get_movement(), computer_ships[computer_ship_num]->get_coord_y() ) == '0' ){
				move_x = +computer_ships[computer_ship_num]->get_movement();
				move_y = 0;
			}
			else{
				move_x = 0;
				move_y = 0;
			}*/
			if (is_safe == true){
				//cout << "New coords: " << computer_ships[computer_ship_num]->get_coord_x()+move_x+1 << " " << computer_ships[computer_ship_num]->get_coord_y()+move_y+1 <<endl;
				if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'L' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'L' );
				}
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'l' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'l' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'H' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'H' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'h' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'h' );
				}
			}
			else{
				move_x = rand()%5 - 2;
				move_y = rand()%5 - 2;
				while ( ( game_field.get_field(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y) != '0' ) || ( (move_x == 0) && (move_y == 0) ) || ( computer_ships[computer_ship_num]->get_coord_x()+move_x < 0 ) || ( computer_ships[computer_ship_num]->get_coord_x()+move_x >=9 ) || ( computer_ships[computer_ship_num]->get_coord_y()+move_y < 0 ) || ( computer_ships[computer_ship_num]->get_coord_y()+move_y >= 9 ) || ( distance( computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y, computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) > computer_ships[computer_ship_num]->get_movement() ) ){
					move_x = rand()%5 - 2;
					move_y = rand()%5 - 2;
				}
				//cout << "New coords: " << computer_ships[computer_ship_num]->get_coord_x()+move_x+1 << " " << computer_ships[computer_ship_num]->get_coord_y()+move_y+1 <<endl;
				if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'L' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'L' );
				}
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'l' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'l' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'H' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'H' );
				} 
				else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'h' ){
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
					computer_ships[computer_ship_num]->set_coords(computer_ships[computer_ship_num]->get_coord_x()+move_x, computer_ships[computer_ship_num]->get_coord_y()+move_y);
					game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'h' );
				}
			}
		}
		else if (max_priority == 200){	//Хз работает ли
			for (int _x = 0; _x < 9; _x++){
				for (int _y = 0; _y < 9; _y++){
					for (int t = 0; t <= player_num; t++){
						if( (distance( _x, _y, player_ships[t]->get_coord_x(), player_ships[t]->get_coord_y() ) <= player_ships[t]->get_attack_radius() ) && ( game_field.get_field(_x, _y) != '0' ) ){
							is_safe = false;
						}
					}
					if ( (safe(_x, _y) == true) && (distance( _x, _y, computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) <= computer_ships[computer_ship_num]->get_movement() ) && ( game_field.get_field(_x, _y) == '0' ) ){
						if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'L' ){
							game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
							computer_ships[computer_ship_num]->set_coords(_x, _y);
							game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'L' );
						} 	
						else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'l' ){
							game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
							computer_ships[computer_ship_num]->set_coords(_x, _y);
							game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'l' );
						} 
						else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'H' ){
							game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
							computer_ships[computer_ship_num]->set_coords(_x, _y);
							game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'H' );
						} 
						else if ( game_field.get_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y() ) == 'h' ){
							game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), '0' );
							computer_ships[computer_ship_num]->set_coords(_x, _y);
							game_field.set_field( computer_ships[computer_ship_num]->get_coord_x(), computer_ships[computer_ship_num]->get_coord_y(), 'h' );
						}
						is_breaked = true;
						break;
					}
				}
				if (is_breaked == true){
					break;
				}
			}
		}
		system ("cls");
		max_priority = 0;
		ship_num = -1;
		is_breaked = false;
		is_safe = false;
		for(int i = 0; i <= computer_num; i++){
			computer_ships[i]->set_priority(0);
		}
	}
	if (player_num >=0){
		cout << "You win! And tou still have " << player_num+1 << " ships." << endl;
	}
	else{
		cout << "Your fleet was destroyed! You lose!" << endl <<
		"Computer still have " << computer_num+1 << " ships.";
	}
}


