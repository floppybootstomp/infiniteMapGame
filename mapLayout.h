#include <list>
#include <unordered_map>
#include "map.h"

class MapLayout{
	//std::list<std::list<Map*>*> theLayout;
	struct Coords{
		int x;
		int y;
		
		Coords(int theX = 0, int theY = 0){
			this->x = theX;
			this->y = theY;
		}
		bool operator==(const Coords &cds) const{
			return (x == cds.x) && (y == cds.y);
		}
		
	} mapCoords;
	struct HashFunction{
		std::size_t operator()(const Coords &cds) const{
			std::size_t i = std::hash<int>()(cds.x);
			std::size_t j = std::hash<int>()(cds.y);
			return i ^ j;
		}
	};
	
	std::unordered_map<Coords, Map*, HashFunction> theLayout;
public:
	MapLayout(){
		//theLayout.push_back(new std::list<Map*>);
		theLayout[{0, 0}] = new Map();
		
		mapCoords.x = 0;
		mapCoords.y = 0;
	}
	~MapLayout(){
		//Coords lCoords;
		for(auto i : theLayout){
			delete i.second;
		}
		
		
		/*for(int i = 0; i < theLayout.size(); i ++){
			for(int j = 0; j < theLayout.size(); j ++){
				delete theLayout[i];
			}
		}*/
	}
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
			default:
				
			break;
		}
	}
	
	Map getMap(int x, int y){
		return *(theLayout[{x, y}]);
		
		//return *(theLayout[y]->at(x));
	}
	Map getCurrMap(){
		return *(theLayout[mapCoords]);
		//return *(theLayout[mapCoords.y]->at(mapCoords.x));
	}
	
	int getXCoord(){return mapCoords.x;}
	int getYCoord(){return mapCoords.y;};
	
};