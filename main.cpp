#include <iostream>
#include "Game.h"
#include "Human.h"
#include "Bot.h"


using namespace std;

int main(){
	Game* battle;
	battle = new Game;
	battle->live();
}
