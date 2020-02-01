// supConsole.cpp : définit le point d'entrée de l'application.
//

#include "supConsole.hpp"

using namespace std;
class Console
{
public:

	std::string cons;

	

private:

};


int main()
{
	SC::ConsolePrint("hello world", SC::ConsoleAttribute(SC::RED,SC::BLUE));
	SC::ConsolePrint("hello world", SC::ConsoleAttribute(SC::RED));
	SC::ConsolePrint("hello world", SC::ConsoleAttribute(SC::UNDERLINE,SC::RED, SC::BLUE)); // esc char
	SC::ConsolePrint("hello world", SC::ConsoleAttribute(SC::UNDERLINE, SC::RED, SC::BLUE)); // esc char
	std::string s = "j";
	while (true)
	{
		



	}
	return 0;
}
