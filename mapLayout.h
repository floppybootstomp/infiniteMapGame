#include <list>
#include <unordered_map>
#include "map.h"

/*
*
* MAP LAYOUT
* -----------------
* A MapLayout object is intended to store and manage all maps in the game
* 
* Functionalities include:
* - containing a record of all maps and their coordinates
* - facilitating moving between maps and adding new maps to the game
* - allowing for accessing information about both the current map the player is in and any other map in the game
* 
*/


class MapLayout{
	// coords object to store the x and y position of a map
	struct Coords{
		int x;
		int y;
		
		// constructor to make initialization of coords easy
		Coords(int theX = 0, int theY = 0){
			this->x = theX;
			this->y = theY;
		}
		// == overloaded to allow for comparison of Coords structs, so that unordered_map can retrieve Coords to Map mappings
		bool operator==(const Coords &cds) const{
			return (x == cds.x) && (y == cds.y);
		}
		
	} mapCoords; // mapCoords stores the current position of the player in the overall mapLayout
	// hash function to tell how Coords struct should be hashed
	struct HashFunction{
		std::size_t operator()(const Coords &cds) const{
			std::size_t i = std::hash<int>()(cds.x); // hash x
			std::size_t j = std::hash<int>()(cds.y); // hash y
			return i ^ j; // bitwise xor
		}
	};
	// unordered_map, which maps coords to maps
	std::unordered_map<Coords, Map*, HashFunction> theLayout;
public:
	// initialize mapCoords' x and y to 0 and create a new map at 0,0
	MapLayout(){
		theLayout[{0, 0}] = new Map();
		
		mapCoords.x = 0;
		mapCoords.y = 0;
	}
	// copy constructor
	MapLayout(const MapLayout &cpyMapLayout){
		mapCoords = cpyMapLayout.mapCoords;
		theLayout = cpyMapLayout.theLayout;
	}
	// delete all map pointers once MapLayout object is destroyed
	~MapLayout(){
		for(auto i : theLayout){
			delete i.second;
		}
	}
	
	// add a new map to the layout, given a direction and a position of an existing map
	void addMap(int currX, int currY, int dir){
		int newX = currX;
		int newY = currY;
		switch(dir){
			case 0: // left
				newX -= 1;
			break;
			case 1: // right
				newX += 1;
			break;
			case 2: // up
				newY -= 1;
			break;
			case 3: // down
				newY += 1;
			break;
		}
		theLayout[{newX, newY}] = new Map();
	}
	
	// change the value of mapCoords based on the direction of movement
	// add a new map to the layout, if it doesn't already exist
	void changeMap(int currX, int currY, int dir){
		switch(dir){
			case 0: // left
				if(theLayout.find({currX-1, currY}) == theLayout.end())
					addMap(currX, currY, dir);
				mapCoords.x -= 1;
			break;
			case 1: // right
				if(theLayout.find({currX+1, currY}) == theLayout.end())
					addMap(currX, currY, dir);
				mapCoords.x += 1;
			break;
			case 2: // up
				if(theLayout.find({currX, currY-1}) == theLayout.end())
					addMap(currX, currY, dir);
				mapCoords.y -= 1;
			break;
			case 3: // down
				if(theLayout.find({currX, currY+1}) == theLayout.end())
					addMap(currX, currY, dir);
				mapCoords.y += 1;
			break;
		}
	}
	
	// returns the map at coords x, y, if it exists, and returns -1 otherwise
	Map getMap(int x, int y){
		return (theLayout.find({x, y}) != theLayout.end())? *(theLayout[{x, y}]) : *(new Map());
	}
	// returns the map at mapCoords
	Map getCurrMap(){
		return *(theLayout[mapCoords]);
	}
	
	// get the x and y values of mapCoords
	int getXCoord(){return mapCoords.x;}
	int getYCoord(){return mapCoords.y;};
	
};