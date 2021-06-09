#include <iostream>
#include <conio.h>
#include <Windows.h>

#define SIZE_X 16
#define SIZE_Y 15

/*
*
* MAP
* -----------------
* A Map object is intended to create, store and manage maps of size SIZE_X x SIZE_Y
* 
* Functionalities include:
* - generate and regenerate a map containing pathways (where a player object can move) and walls (where a player object can't move)
* - provide an interface to draw that map to the console as needed
* - provide an interface to determine if a particular x or y position is a pathway or a wall
* 
*/


class Map{
	// an array storing the information for each x and y coordinate of the map
	int theMap[SIZE_Y][SIZE_X];
	
	// generates a new map 
	// NEEDS IMPROVEMENT
	void mapgen(){
		// determines how many walls are in the map. Higher values = fewer walls
		int mapDensity = 5;
		// for every position in theMap array, set it to either 0 (wall) or 1 (pathway)
		for(int i = 0; i < SIZE_Y; i ++){
			for(int j = 0; j < SIZE_X; j ++){
				switch(rand()%mapDensity){ // randomly select a value between 0 and mapDensity to decide whether to place a wall or not
					case 0: 
						theMap[i][j] = 0; // place a wall
					break;
					case 1: // place a pathway if an adjacent x or y value contains a pathway
						if(i > 0 && i < SIZE_Y-1){
							if(theMap[i+(rand()%2-1)][j] == 1){
								theMap[i][j] = 1;
								break;
							}
						}
						if(j > 0 && j < SIZE_X-1){
							if(theMap[i][j+(rand()%2-1)] == 1){
								theMap[i][j] = 1;
								break;
							}
						}
					default:
						theMap[i][j] = 1; // place a pathway
					break;
				}
			}
		}
	}
	
public:
	Map(){
		// generate a new map automatically
		mapgen();
	}
	// copy constructor to copy all previous map values into a new map
	Map(const Map &cpyMap){
		for(int i = 0; i < SIZE_Y; i ++){
			for(int j = 0; j < SIZE_X; j ++){
				theMap[i][j] = cpyMap.theMap[i][j];
			}
		}
	}
	
	// redraws the map in the console
	void drawMap(){
		system("cls"); // clear console
		for(int i = 0; i < SIZE_Y; i ++){
			for(int j = 0; j < SIZE_X; j ++){
				if(theMap[i][j] == 1){
					std::cout << "  "; // draw space if pathway
				}
				else{
					std::cout << "\x1B[32mT\033[0m "; // draw green T character if wall
				}
			}
			std::cout << std::endl;
		}
	}
	
	// get the value (wall or pathway) at the position (x, y)
	int getMapVal(int x, int y){
		return theMap[y][x];
	}
	
	// overwrite this map and generate a new one
	void newMap(){
		mapgen();
	}
	
};
