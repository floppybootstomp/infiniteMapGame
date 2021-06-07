#include <iostream>
#include <string>
#include <ctime>
#include "consoleOutputHandler.h"
//#include "map.h"
#include "mapLayout.h"
#include "player.h"

using namespace std;

#define SIZE_X 16
#define SIZE_Y 15


int main(){
	srand(time(0));
	
	ConsoleOutputHandler csh;
	MapLayout gameMap;
	gameMap.addMap(0, 0, -1);
	gameMap.getCurrMap().drawMap();
	Player player(0, 0);
	for(int i = 0; i < SIZE_X; i ++){
		if(gameMap.getCurrMap().getMapVal(i, 0) == 1){
			player.moveCharacter(i, 0, gameMap.getCurrMap());
			if(rand()%5 == 0)
				break;
		}
	}
	player.moveCharacter(0, 0, gameMap.getCurrMap());
	
	char input;
	while(input != 'q'){
		input = getch();
		string output = string(1, input) + "\nMap Coords: (" + to_string(gameMap.getXCoord()) + ", " + to_string(gameMap.getYCoord()) + ")";
		csh.printCommand(output);
		switch(input){
			case 'w':
				player.moveCharacter(0, -1, gameMap.getCurrMap());
				if(player.getPlayerY() < 0){
					gameMap.changeMap(gameMap.getXCoord(), gameMap.getYCoord(), 2);
					gameMap.getCurrMap().drawMap();
					player.setPlayerY(SIZE_Y-1);
				}
			break;
			case 'a':
				player.moveCharacter(-1, 0, gameMap.getCurrMap());
				if(player.getPlayerX() < 0){
					gameMap.changeMap(gameMap.getXCoord(), gameMap.getYCoord(), 0);
					gameMap.getCurrMap().drawMap();
					player.setPlayerX(SIZE_X-1);
				}
			break;
			case 's':
				player.moveCharacter(0, 1, gameMap.getCurrMap());
				if(player.getPlayerY() > SIZE_Y-1){
					gameMap.changeMap(gameMap.getXCoord(), gameMap.getYCoord(), 3);
					gameMap.getCurrMap().drawMap();
					player.setPlayerY(0);
				}
			break;
			case 'd':
				player.moveCharacter(1, 0, gameMap.getCurrMap());
				if(player.getPlayerX() > SIZE_X-1){
					gameMap.changeMap(gameMap.getXCoord(), gameMap.getYCoord(), 1);
					gameMap.getCurrMap().drawMap();
					player.setPlayerX(0);
				}
			break;
			case 'm':
				gameMap.getCurrMap().newMap();
				gameMap.getCurrMap().drawMap();
			break;
			case 'q':
				csh.printCommand("quit\n");
			break;
			default:
				csh.printCommand("umm sorry not a command\n");
			break;
		}
		csh.sendPointerToBottom();
	}
	
	// clear the console once the game is done, to prevent spaghetti
	system("cls");
	
	return 0;
}































