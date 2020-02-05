#pragma once
#include "supConsole.hpp"
#include <string> 

#include "luaUtil.hpp"
namespace SC {
	struct vec2 // just a vector2
	{
		float x;
		float y;
	};
	enum ConsolePrintAttribute 
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
	enum logType {
		 LOG_NORMAL = 0,
		 LOG_WARNING,
		 LOG_ERROR,
		 LOG_LUA_ERROR
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
	}; // console attribute


	 
	void ConsolePrint(std::string ttoPrint, ConsoleAttribute attribute); // print a thing in the console

	vec2 getConsSize(); // get the console size 
	void setConsCurPos(vec2 p); // set the cursor pos

	void ClearConsole(); // clear the console
	
	void clog(std::string log, logType logtype); // log

	void process(std::string input); // process the input
	void Close();
	void init(int width, int height, std::string* path, char** argv); // init the console


	void start();
	
	
	
	
	// lua Implementation
	void print_errorLUA(lua_State* state); // error callback for lua

	void executeLUA(std::string data); // execute lua code

	void luaInterp(std::string cmd); // interpret lua

}