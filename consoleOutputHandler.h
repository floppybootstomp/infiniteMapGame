#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>

#define SIZE_X 16
#define SIZE_Y 15

class ConsoleOutputHandler{
	static const HANDLE hOut;
	
public:
	ConsoleOutputHandler(){
	}
	
	// change only a single character in the console, so that it runs faster
	void replaceConsoleChar(int x, int y, std::string c, int color = 0){
		std::cout.flush();
		COORD coord = { (SHORT)(x*2), (SHORT)(y) };
		SetConsoleCursorPosition(hOut, coord);
		std::cout << c;
	}
	// print a command under the map
	void printCommand(std::string c){
		std::cout.flush();
		COORD coord = { (SHORT)(0), (SHORT)(SIZE_Y+1) };
		SetConsoleCursorPosition(hOut, coord);
		for(int i = 0; i < 100; i ++)
			std::cout << " ";
		std::cout.flush();
		
		SetConsoleCursorPosition(hOut, coord);
		std::cout << c;
	}
	// 
	void sendPointerToBottom(){
		std::cout.flush();
		COORD coord = { (SHORT)(0), (SHORT)(SIZE_Y+5) };
		SetConsoleCursorPosition(hOut, coord);
	}
};
const HANDLE ConsoleOutputHandler::hOut = GetStdHandle(STD_OUTPUT_HANDLE); 