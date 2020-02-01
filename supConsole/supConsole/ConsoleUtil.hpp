#pragma once
#include "supConsole.hpp"
#include <string> 

namespace SC {

	 enum  ConsolePrintAttribute 
	{
		RESET = 0,
		BOLD = 1, 
		UNDERLINE = 4,
		INVERSE = 7,

		

	};
	 enum ConsoleCol {

		 BLACK = 30,
		 RED = 31,
		 GREEN = 32,
		 YELLOW = 33,
		 BLUE = 34,
		MAGENTA = 35,
		 CYAN = 36,
		 WHITE = 37,
		 S_BLACK = 90,
		 S_RED = 91,
		 S_GREEN = 92,
		 S_YELLOW = 93,
		 S_BLUE = 94,
		 S_MAGENTA = 95,
		 S_CYAN = 96,
		 S_WHITE = 97
	 };
	 enum ColType
	 {
		 FOREGROUND = 0,
		 BACKGROUND = 10
	 };

	 class ConsoleAttribute
	 {
	 public:
		 ConsoleAttribute(ConsolePrintAttribute cpa, ConsoleCol fcol, ConsoleCol bcol );
		 ConsoleAttribute(ConsoleCol fcol);
		 ConsoleAttribute(ConsoleCol fcol, ConsoleCol bcol);
		 ConsoleAttribute(ConsolePrintAttribute cpa);

		 std::string AttribToString();// return a string attribute (for use in console)

	 private:
		 ConsolePrintAttribute CAcpa; // console print attribute
		 ConsoleCol CAccf; // console foreground color
		 ConsoleCol CAccb; // console background color
	 };


	 
	 std::string getConsoleAttribute(ConsolePrintAttribute att);
	void ConsolePrint(std::string ttoPrint, ConsoleAttribute attribute)
		; // print a thing in the console
	
	void init(int width, int height); // init the console
}