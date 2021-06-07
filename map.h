#include <iostream>
#include <conio.h>
#include <Windows.h>

#define SIZE_X 16
#define SIZE_Y 15

class Map{
	int theMap[SIZE_Y][SIZE_X];
	
	void mapgen(){
		for(int i = 0; i < SIZE_Y; i ++){
			for(int j = 0; j < SIZE_X; j ++){
				switch(rand()%5){
					case 0:
						theMap[i][j] = 0;
					break;
					case 1:
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
						theMap[i][j] = 1;
					break;
				}
			}
		}
	}
	
public:
	Map(){
		mapgen();
	}
	Map(const Map &cpyMap){
		//std::cout << "cpy\n";
		for(int i = 0; i < SIZE_Y; i ++){
			for(int j = 0; j < SIZE_X; j ++){
				theMap[i][j] = cpyMap.theMap[i][j];
			}
		}
	}
	
	void drawMap(){
		system("cls");
		for(int i = 0; i < SIZE_Y; i ++){
			for(int j = 0; j < SIZE_X; j ++){
				if(theMap[i][j] == 1){
					std::cout << "  ";
				}
				else{
					std::cout << "\x1B[32mT\033[0m ";
				}
			}
			std::cout << std::endl;
		}
	}
	
	int getMapVal(int x, int y){
		return theMap[y][x];
	}
	void newMap(){
		mapgen();
	}
	
};
