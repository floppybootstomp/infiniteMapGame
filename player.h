#include <iostream>
#include <string>

#define SIZE_X 16
#define SIZE_Y 15

/*
*
* PLAYER
* -----------------
* A Player object is intended to create and manage the position of an object that moves through the procedurally generated map world
* 
* Functionalities include:
* - store and update x and y position, both through a function that moves the player by a distance and through a function that moves the player to a position
* - prevent the player from moving through walls and moving out of the map
* - provide an interface to access the player's x and y position
* - redraw the player by replacing characters in the console after the map has been drawn
* 
*/

class Player{
	
	int playerX;
	int playerY;
public:
	// initialize a player by setting x and y positions
	Player(int x, int y){
		playerX = x;
		playerY = y;
	}
	
	// change the character position on the map
	void moveCharacter(int distX, int distY, Map mapChecker){
		ConsoleOutputHandler csh;
		// if there is not a wall or the player is not at the edge of the map, redraw the player and move them
		if(((playerX+distX) >= 0 && (playerX+distX) < SIZE_X && (playerY+distY) >= 0 && (playerY+distY) < SIZE_Y) && (mapChecker.getMapVal(playerX+distX, playerY+distY) != 0)){
			csh.replaceConsoleChar(playerX, playerY, " "); // replace player character with space character
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
			csh.replaceConsoleChar(playerX+distX, playerY+distY, "\x1B[33m@\033[0m"); // redraw player in the console
			// move the player by x and y distances
			playerX += distX;
			playerY += distY;
		}
		// if the player reaches the edge of the map, just move them
		else if((playerX+distX) < 0 || (playerX+distX) >= SIZE_X || (playerY+distY) < 0 || (playerY+distY) >= SIZE_Y){
			// move the player by x and y distances
			playerX += distX;
			playerY += distY;
		}
	}
	
	// get player x and y positions
	int getPlayerX(){return playerX;}
	int getPlayerY(){return playerY;}
	
	// set player x and y positions and redraw them
	void setPlayerX(int val){
		ConsoleOutputHandler csh;
		csh.replaceConsoleChar(playerX, playerY, " "); // replace player character with space character
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		csh.replaceConsoleChar(val, playerY, "\x1B[33m@\033[0m"); // redraw player in console
		// update player x value to val
		playerX = val;
	}
	void setPlayerY(int val){
		ConsoleOutputHandler csh;
		csh.replaceConsoleChar(playerX, playerY, " "); // replace player character with space character
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		csh.replaceConsoleChar(playerX, val, "\x1B[33m@\033[0m"); // redraw player in console
		// update player y value to val
		playerY = val;
	}
	
};