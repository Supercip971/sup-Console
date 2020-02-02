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



int main(int argc, char* argv[]) {
	cout << "the address is: " << argv[0] << endl;
	std::string fpath = argv[0];
	SC::init(0, 0);
	ConsolePrint("", SC::ConsoleAttribute(SC::ConsolePrintAttribute::RESET, SC::WHITE, SC::BLACK));
	while (true)
	{
		std::string input ;
		ConsolePrint(fpath, SC::ConsoleAttribute(SC::ConsolePrintAttribute::BOLD, SC::S_CYAN, SC::BLACK));
		ConsolePrint(">", SC::ConsoleAttribute(SC::ConsolePrintAttribute::BOLD, SC::GREEN, SC::BLACK));
		ConsolePrint("", SC::ConsoleAttribute(SC::ConsolePrintAttribute::RESET, SC::WHITE, SC::BLACK));
		char s[1000];
		fgets(s, 1000, stdin);
		input = s;

		SC::process(input);

	}
	return 0;
}
