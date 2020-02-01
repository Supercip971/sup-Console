#include "supConsole.hpp"
namespace SC {

	void ConsolePrint(std::string ttoPrint, ConsoleAttribute attribute) {
#ifdef SYS_WINDOWS or SYS_LINUX
		std::cout << attribute.AttribToString() << ttoPrint  ;
#endif // SYS_WINDOWS
	}

	void init(int width, int height) {

	}



	

	vec2 getConsoleSize()
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

}