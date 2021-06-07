#include <iostream>
#include <string>

#define SIZE_X 16
#define SIZE_Y 15

class Player{
	
	int playerX;
	int playerY;
public:
	Player(int x, int y){
		playerX = x;
		playerY = y;
	}
	
	// change the character position on the map
	void moveCharacter(int distX, int distY, Map mapChecker){
		ConsoleOutputHandler csh;
		if(((playerX+distX) >= 0 && (playerX+distX) < SIZE_X && (playerY+distY) >= 0 && (playerY+distY) < SIZE_Y) && (mapChecker.getMapVal(playerX+distX, playerY+distY) != 0)){
			csh.replaceConsoleChar(playerX, playerY, " ");
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			csh.replaceConsoleChar(playerX+distX, playerY+distY, "\x1B[33m@\033[0m");
			playerX += distX;
			playerY += distY;
		}
		else if((playerX+distX) < 0 || (playerX+distX) >= SIZE_X || (playerY+distY) < 0 || (playerY+distY) >= SIZE_Y){
			playerX += distX;
			playerY += distY;
		}
	}
	int getPlayerX(){return playerX;}
	int getPlayerY(){return playerY;}
	void setPlayerX(int val){
		ConsoleOutputHandler csh;
		csh.replaceConsoleChar(playerX, playerY, " ");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		csh.replaceConsoleChar(val, playerY, "\x1B[33m@\033[0m");
		playerX = val;
	}
	void setPlayerY(int val){
		ConsoleOutputHandler csh;
		csh.replaceConsoleChar(playerX, playerY, " ");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		csh.replaceConsoleChar(playerX, val, "\x1B[33m@\033[0m");
		playerY = val;
	}
	
};