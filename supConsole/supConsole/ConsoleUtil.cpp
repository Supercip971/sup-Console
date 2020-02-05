#include "supConsole.hpp"

int MajorVersion = 0;
int minorVersion = 1;
int subVersion = 29; // for change id (+1 for every commit in github)
std::string changeLog = "version 0.1 still in beta"
		"commit 12 : add changelog and update how subVersion is calc"
		"commit 13 : add lib for lua support "
	"commit 14 : support for lua with lua {code} function"; // changelog not updated (used for major release
namespace SC {
	std::string fPath = "null";
	std::string sourcefPath = "null";
	std::string* args = new std::string[20]{ "null","null","null","null","null","null","null","null","null","null","null","null","null","null","null","null","null","null","null","null" }; // max 20 argument :(
	std::string comargs = "null";
	lua_State* L;

	bool beta = true;
	void ConsolePrint(std::string ttoPrint, ConsoleAttribute attribute) {
#ifdef SYS_WINDOWS 
		std::cout << attribute.AttribToString() << ttoPrint  ;
#endif // SYS_WINDOWS
#ifdef SYS_LINUX
		//snprintf((attribute.AttribToString() + ttoPrint),)
		printf("%s%s", attribute.AttribToString().c_str(), ttoPrint.c_str());
#endif // SYS_LINUX

	}

	

	void clog(std::string log, logType logtype)
	{

		switch (logtype)
		{
		case SC::LOG_NORMAL:
			ConsolePrint("", SC::ConsoleAttribute(ConsolePrintAttribute::RESET));
			ConsolePrint("[LOG] : ", SC::ConsoleAttribute(ConsoleCol::GREEN));
			ConsolePrint(log + "\n", SC::ConsoleAttribute(ConsoleCol::WHITE));
			break;
		
		case SC::LOG_WARNING:
			ConsolePrint("", SC::ConsoleAttribute(ConsolePrintAttribute::RESET));
			ConsolePrint("[WARNING] : ", SC::ConsoleAttribute(ConsoleCol::YELLOW));
			ConsolePrint(log + "\n", SC::ConsoleAttribute(ConsoleCol::WHITE));
			break;
		
		case SC::LOG_ERROR:
			ConsolePrint("", SC::ConsoleAttribute(ConsolePrintAttribute::RESET));
			ConsolePrint("[ERROR] : ", SC::ConsoleAttribute(ConsoleCol::RED));
			ConsolePrint(log + "\n", SC::ConsoleAttribute(ConsoleCol::WHITE));
			break;

		case SC::LOG_LUA_ERROR:
			ConsolePrint("", SC::ConsoleAttribute(ConsolePrintAttribute::RESET));
			ConsolePrint("[LUA ERROR] : ", SC::ConsoleAttribute(ConsoleCol::S_MAGENTA));
			ConsolePrint(log + "\n", SC::ConsoleAttribute(ConsoleCol::WHITE));
			break;
		default:
			break;
		}
	}

	void start() {
		ConsolePrint(fPath, SC::ConsoleAttribute(SC::ConsolePrintAttribute::BOLD, SC::S_CYAN, SC::BLACK));
		ConsolePrint(">", SC::ConsoleAttribute(SC::ConsolePrintAttribute::BOLD, SC::GREEN, SC::BLACK));
		ConsolePrint("", SC::ConsoleAttribute(SC::ConsolePrintAttribute::RESET, SC::WHITE, SC::BLACK));
	}

	void process(std::string input)
	{

		input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
		std::string d;
		int argNum = 0;
		bool isCommarg = false;
		std::string commArg = "";
		int first = input.find('{');
		int last = input.find('}');

		std::string* strList = new std::string[30];
		int numArg = 0;
		if (first != -1)
		{
			if (last != -1)
			{
				if (first < last)
				{
					isCommarg = true;
				}
				else
				{
					clog( " '{' is used after '}' ", SC::LOG_ERROR);
				}
			}
		}
		if (isCommarg == true)
		{
			 commArg = input.substr(first, last - first);
			input.erase(first, (last ) - (first));

			commArg.erase(std::remove(commArg.begin(), commArg.end(), '}'), commArg.end());
			commArg.erase(std::remove(commArg.begin(), commArg.end(), '{'), commArg.end());
			input.erase(std::remove(input.begin(), input.end(), '}'), input.end());
			input.erase(std::remove(input.begin(), input.end(), '{'), input.end()); // used for commarg
			comargs = commArg;
		//	clog(commArg + " is  commArgument", SC::LOG_NORMAL);
		}


	

		std::istringstream iss(input);
		for (int i = 0; i < 30; i++)
		{
			strList[i] = "";
		}

		while (iss >> d) {
			strList[numArg] = d;
			++numArg;
			++argNum;

		}
			if (strList[0] == "lua" && isCommarg == true)
			{
				luaInterp(commArg);
			}
			else if (strList[0] == "update" && isCommarg == false)
			{
				clog("do you want to update app ? you have to install git on your computer. type 'y' to update app", logType::LOG_WARNING);
				std::string input;

				char* s = new char[1000];
				fgets(s, 1000, stdin);
				input = s;
				if (input[0] == 'y')
				{
					clog("starting update...", logType::LOG_NORMAL);

					clog("starting git...", logType::LOG_NORMAL);

					system("git clone https://github.com/Supercip971/Sup-Console-APP.git");
				}
				else
				{
					clog("cancelling update...", logType::LOG_NORMAL);
				}
			}
			else if (strList[0] == "install" && isCommarg == false)
			{

				clog("do you want to install app "+strList[1]+ "? you have to install git on your computer. type 'y' to install app", logType::LOG_WARNING);
				std::string input;

				char* s = new char[1000];
				fgets(s, 1000, stdin);
				input = s;
				if (input[0] == 'y')
				{
					clog("install is not supported for the moment sorry", logType::LOG_ERROR);
				}
				else
				{
					clog("cancelling install...", logType::LOG_NORMAL);
				}
			}
			else
			{
				std::string errorPrevious = "";
				if (luaL_dofile(L, ("Sup-Console-APP/" + strList[0] + ".lua").c_str())) {
					errorPrevious = lua_tostring(L, -1);
					if (luaL_dofile(L, ("Sup-Console-USER-APP/" + strList[0] + ".lua").c_str()))
					{

						clog(lua_tostring(L, -1), SC::LOG_LUA_ERROR);
						clog("and", SC::LOG_LUA_ERROR);
						clog(errorPrevious, SC::LOG_LUA_ERROR);
					}
				}
				else
				{
					lua_pcall(L, 0, 0, 0);

					if (numArg > 1)
					{
						 // we can not do switch on string :(
						if (strList[1] == "-help" )
						{
							lua_getglobal(L, "help");
							lua_pcall(L, 0, 0, 0);
						}
						else if (strList[1] == "-info" )
						{
							lua_getglobal(L, "info");
							lua_pcall(L, 0, 0, 0);
						}
						else if (strList[1] == "-version" )
						{
							lua_getglobal(L, "ver");
							lua_pcall(L, 0, 0, 0);
						}
						else
						{
							lua_getglobal(L, "run");
							for (int i = 1; i < numArg; i++)
							{
								args[i] = strList[i];
							}
							lua_pcall(L,0, 0, 0);

						}
					}
					else
					{

						lua_getglobal(L, "run");
						for (int i = 1; i < numArg; i++)
						{
							args[i] = "";

						}

						lua_pcall(L, 0, 0, 0);

					}
					for (int i = 1; i < numArg; i++)
					{
						strList[i] = "null";
						 // reset
					}

				}
			}
			delete[] strList; // delete
		
	}

	void Close() {
		clog("closing lua", LOG_NORMAL);
		lua_close(L);
	}

#pragma region luaFunc
	// all important lua function
	static int  LuaLog(lua_State* Li)
	{
		int n = lua_gettop(Li);

		
		std::string str = lua_tostring(Li, 1);
		std::string type= lua_tostring(Li, 2); 
		if (type == "error")
		{
			clog(str, LOG_ERROR);
		}else if (type == "normal")
		{
			clog(str, LOG_NORMAL);
		}
		else if (type == "warning")
		{
			clog(str, LOG_WARNING);
		}
		else
		{
			ConsolePrint(str, SC::ConsoleAttribute(ConsolePrintAttribute::RESET));
		}
		return 0;
	}
	static int  setStyle(lua_State* Li)
	{
		int n = lua_gettop(Li);


		std::string fcolor = lua_tostring(Li, 1);
		std::string bcolor = lua_tostring(Li, 2);
		std::string type = lua_tostring(Li, 3);
		SC::ConsoleCol fcolorA = SC::ConsoleCol::WHITE;
		SC::ConsoleCol bcolorA = SC::ConsoleCol::BLACK;
		SC::ConsolePrintAttribute attribA = SC::ConsolePrintAttribute::NULLT;
					// can't do switch on string >:(
#pragma region ForGroundColor
		if (fcolor == "white")
			fcolorA = SC::ConsoleCol::WHITE;
		else if (fcolor == "black")
			fcolorA = SC::ConsoleCol::BLACK;
		else if (fcolor == "blue")
			fcolorA = SC::ConsoleCol::BLUE;
		else if (fcolor == "sblue")
			fcolorA = SC::ConsoleCol::S_BLUE;
		else if (fcolor == "cyan")
			fcolorA = SC::ConsoleCol::CYAN;
		else if (fcolor == "scyan")
			fcolorA = SC::ConsoleCol::S_CYAN;
		else if (fcolor == "green")
			fcolorA = SC::ConsoleCol::GREEN;
		else if (fcolor == "sgreen")
			fcolorA = SC::ConsoleCol::S_GREEN;
		else if (fcolor == "magenta")
			fcolorA = SC::ConsoleCol::MAGENTA;
		else if (fcolor == "smagenta")
			fcolorA = SC::ConsoleCol::S_MAGENTA;
		else if (fcolor == "red")
			fcolorA = SC::ConsoleCol::RED;
		else if (fcolor == "sred")
			fcolorA = SC::ConsoleCol::S_RED;
		else if (fcolor == "yellow")
			fcolorA = SC::ConsoleCol::YELLOW;
		else if (fcolor == "syellow")
			fcolorA = SC::ConsoleCol::S_YELLOW;
#pragma endregion
#pragma region Background


		if (bcolor == "white")
			bcolorA = SC::ConsoleCol::WHITE;
		else if (bcolor == "black")
			bcolorA = SC::ConsoleCol::BLACK;
		else if (bcolor == "blue")
			bcolorA = SC::ConsoleCol::BLUE;
		else if (bcolor == "sblue")
			bcolorA = SC::ConsoleCol::S_BLUE;
		else if (bcolor == "cyan")
			bcolorA = SC::ConsoleCol::CYAN;
		else if (bcolor == "scyan")
			bcolorA = SC::ConsoleCol::S_CYAN;
		else if (bcolor == "green")
			bcolorA = SC::ConsoleCol::GREEN;
		else if (bcolor == "sgreen")
			bcolorA = SC::ConsoleCol::S_GREEN;
		else if (bcolor == "magenta")
			bcolorA = SC::ConsoleCol::MAGENTA;
		else if (bcolor == "smagenta")
			bcolorA = SC::ConsoleCol::S_MAGENTA;
		else if (bcolor == "red")
			bcolorA = SC::ConsoleCol::RED;
		else if (bcolor == "sred")
			bcolorA = SC::ConsoleCol::S_RED;
		else if (bcolor == "yellow")
			bcolorA = SC::ConsoleCol::YELLOW;
		else if (bcolor == "syellow")
			bcolorA = SC::ConsoleCol::S_YELLOW;
	

#pragma endregion
#pragma region Type
		if (type == "underline")
			attribA = SC::ConsolePrintAttribute::UNDERLINE;
		else if (type == "bold")
			attribA = SC::ConsolePrintAttribute::BOLD;
		else if (type == "inverse")
			attribA = SC::ConsolePrintAttribute::INVERSE;
		else if (type == "reset")
			attribA = SC::ConsolePrintAttribute::RESET;
#pragma endregion

		SC::ConsoleAttribute CA(attribA, fcolorA, bcolorA);
		SC::ConsolePrint("", CA);
		return 0;
	}
	static int getFPath(lua_State* Li) { // get path
		int n = lua_gettop(Li);
		lua_pushfstring(Li, (fPath).c_str());
		return 1;
	}
	
	static int getFPathIS(lua_State* Li) { // inverted slash
		int n = lua_gettop(Li);
		std::string fpToret = fPath;
		std::replace(fpToret.begin(), fpToret.end(), '/', '\\'); // replace all 'x' to 'y'
		lua_pushfstring(Li, (fpToret).c_str());
		return 1;
	}
	
	static int getFPathNS(lua_State* Li) { // normal slash
		int n = lua_gettop(Li);
		std::string fpToret = fPath;
		std::replace(fpToret.begin(), fpToret.end(), '\\', '/'); // replace all 'x' to 'y'
		lua_pushfstring(Li, (fpToret).c_str());
		return 1;
	}
	
	static int setFPath(lua_State* Li) {

		int n = lua_gettop(Li);
		std::string np = lua_tostring(Li, 1);
		fPath = np;
		return 0;
	}
	
	static int  LuagetVer(lua_State* Li)
	{
		int n = lua_gettop(Li);
		lua_pushnumber(Li, MajorVersion);
		lua_pushnumber(Li, minorVersion);
		lua_pushnumber(Li, subVersion);
		return 3;
	}
	
	static int  isarg(lua_State* Li)
	{
		int n = lua_gettop(Li);
		bool findit = false;
		std::string argtofind =lua_tostring(Li, 1);;
		for (int i = 0; i < 20; i++)
		{
			if (args[i] == argtofind)
			{
				findit = true;
			}
		}
		lua_pushboolean(Li, findit);

		return 1;
	}
	
	static int  getcommarg(lua_State* Li)
	{
		int n = lua_gettop(Li);
		lua_pushfstring(Li, comargs.c_str() );

		return 1;
	}
#pragma endregion


	void init(int width, int height, std::string* path, char** argv) {
		fPath = *path;
		sourcefPath = fPath;
#ifdef SYS_LINUX
	
#endif // SYS_LINUX
		clog("loading lua", LOG_NORMAL);
		L = luaL_newstate();

		clog("loading lua lib", LOG_NORMAL);
		luaL_openlibs(L);

		clog("loading lua function", LOG_NORMAL);
		lua_register(L, "log", LuaLog); //  log(logstring, logtype (normal | warning | error or null)) return : nothing | log
		lua_register(L, "getVer", LuagetVer); //  getVer() return : majorVersion, minorVersion, subVersion | get versions
		lua_register(L, "getFilePath", getFPath); //  getFilePath() return : current file path | get the current file path
		lua_register(L, "getFilePathIS", getFPathIS); //  getFilePathI() return : current file path | get the current file path but / are \ 
		lua_register(L, "getFilePathNS", getFPathNS); //  getFilePathI() return : current file path | get the current file path but \ are /
		lua_register(L, "setFilePath", setFPath); //  setFilePath(string path) return : nothing | set current file path
		lua_register(L, "getCommarg", getcommarg); //  getCommarg() return : string  | get the comm argument
		lua_register(L, "isArg", isarg); //  isarg(string arg) return : bool  | get if the 'arg' is in the argument list
		lua_register(L, "setStyle", setStyle); //  setStyle(foregroundCol, backgroundColor, type) return : bool  | get if the 'arg' is in the argument list
		SC::LU::LoadLUCommand(L);
		

		
		clog("loading finish", LOG_NORMAL);

	
		ClearConsole();
			
		
		
		ConsolePrint("##########\n", ConsoleAttribute(GREEN));
		ConsolePrint("#        #\n", ConsoleAttribute(GREEN));
		ConsolePrint("#  ##### # ", ConsoleAttribute(GREEN));

		ConsolePrint("SupConsole \n", ConsoleAttribute(S_CYAN));

		ConsolePrint("# ##     # ", ConsoleAttribute(GREEN));
		if (beta)
			ConsolePrint("version : [BETA] " + std::to_string(MajorVersion) + "." + std::to_string(minorVersion) + "       edition : " + std::to_string(subVersion) + "\n", ConsoleAttribute(S_CYAN));
		else
			ConsolePrint("version : " + std::to_string(MajorVersion) + "." + std::to_string(minorVersion) + "       edition : " + std::to_string(subVersion) + "\n", ConsoleAttribute(S_CYAN));
		
		ConsolePrint("#  ####  #\n", ConsoleAttribute(GREEN));
		ConsolePrint("#     ## #\n", ConsoleAttribute(GREEN));
		ConsolePrint("# #####  #\n", ConsoleAttribute(GREEN));
		ConsolePrint("#        #\n", ConsoleAttribute(GREEN));
		ConsolePrint("########## \n", ConsoleAttribute(GREEN));
	}



	

	vec2 getConsSize()
	{
		vec2 size = { 0,0 };
#ifdef SYS_LINUX
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		size.y = (float) w.ws_row;
		size.x = (float) w.ws_col;
#endif // SYS_LINUX
		
#ifdef SYS_WINDOWS
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		size.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		size.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#endif // SYS_WINDOWS
		return size;
	}

	void setConsCurPos(vec2 p)
	{
		if (p.x == -1)
		{
			printf(std::string("\033[;" + std::to_string(int(p.y) + 1) + "H").c_str());
		}else if (p.y == -1)
		{
			printf(std::string("\033[" + std::to_string(int(p.x) + 1) + "G").c_str());
		}else
		{
			printf(std::string("\033[" + std::to_string(int(p.x) + 1) + ";" + std::to_string(int(p.y) + 1) + "H").c_str());
		}
			
	}

	void ClearConsole()
	{
#ifdef SYS_LINUX
		system("clear");
#endif // SYS_LINUX
#ifdef SYS_WINDOWS
		system("cls");
#endif // SYS_WINDOWS
	}

}