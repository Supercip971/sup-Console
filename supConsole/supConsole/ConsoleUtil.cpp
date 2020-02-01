#include "supConsole.hpp"


namespace SC {

	void ConsolePrint(std::string ttoPrint, ConsoleAttribute attribute) {
#ifdef SYS_WINDOWS or SYS_LINUX
		std::cout << attribute.AttribToString() << ttoPrint  ;
#endif // SYS_WINDOWS
	}
	std::string filePath;
	void clog(std::string log, logType logtype)
	{

		switch (logtype)
		{
		case SC::LOG_NORMAL:
			ConsolePrint("", SC::ConsoleAttribute(ConsolePrintAttribute::RESET));
			ConsolePrint("[LOG] :", SC::ConsoleAttribute(ConsoleCol::GREEN));
			ConsolePrint(log + "\n", SC::ConsoleAttribute(ConsoleCol::WHITE));
		case SC::LOG_WARNING:
			ConsolePrint("", SC::ConsoleAttribute(ConsolePrintAttribute::RESET));
			ConsolePrint("[WARNING] :", SC::ConsoleAttribute(ConsoleCol::YELLOW));
			ConsolePrint(log + "\n", SC::ConsoleAttribute(ConsoleCol::WHITE));
			break;
		case SC::LOG_ERROR:
			ConsolePrint("", SC::ConsoleAttribute(ConsolePrintAttribute::RESET));
			ConsolePrint("[ERROR] :", SC::ConsoleAttribute(ConsoleCol::RED));
			ConsolePrint(log + "\n", SC::ConsoleAttribute(ConsoleCol::WHITE));
			break;
		default:
			break;
		}
	}
	void process(std::string input)
	{
		input.find('\n');
		clog(input + "is not a valid command, try help to get help", SC::LOG_ERROR);
	}

	void init(int width, int height) {
		ClearConsole();
		int MajorVersion = 0;
		int minorVersion =1 ;
		int subVersion = 2; // for change id (+1 for every push in github)
		bool beta = true;
		ConsolePrint("##########\n", ConsoleAttribute(GREEN));
		ConsolePrint("#        #\n", ConsoleAttribute(GREEN));
		ConsolePrint("#  ##### # ", ConsoleAttribute(GREEN));

		ConsolePrint("SupConsole \n", ConsoleAttribute(S_CYAN));

		ConsolePrint("# ##     # ", ConsoleAttribute(GREEN));
		if (beta)
		{
			ConsolePrint("version : [BETA] " + std::to_string(MajorVersion) + "." + std::to_string(minorVersion) + "." + std::to_string(subVersion) + "\n", ConsoleAttribute(S_CYAN));
		}
		else
		{
			ConsolePrint("version : " + std::to_string(MajorVersion) + "." + std::to_string(minorVersion) + "." + std::to_string(subVersion) + "\n", ConsoleAttribute(S_CYAN));
		}
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
	
			printf(std::string("\033["+std::to_string(int(p.x) + 1) + ";" + std::to_string(int(p.y) + 1) + "H").c_str());
			
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