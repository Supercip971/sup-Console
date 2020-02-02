﻿// supConsole.cpp : définit le point d'entrée de l'application.
//

#include "supConsole.hpp"

using namespace std;
class Console
{
public:

	std::string cons;

	

private:

};

const char* GetPrevDirectoryPath(const char* dirPath)
{
	static char prevDirPath[2048];
	memset(prevDirPath, 0, 2048);
	int pathLen = strlen(dirPath);

	if (pathLen <= 3) strcpy(prevDirPath, dirPath);

	for (int i = (pathLen - 1); (i > 0) && (pathLen > 3); i--)
	{
		if ((dirPath[i] == '\\') || (dirPath[i] == '/'))
		{
			if (i == 2) i++;    // Check for root: "C:\"
			strncpy(prevDirPath, dirPath, i);
			break;
		}
	}

	return prevDirPath;
}

int main(int argc, char* argv[]) {
	cout << "the address is: " << argv[0] << endl;

	std::string fpath = GetPrevDirectoryPath(argv[0]);
	SC::init(0, 0, &fpath);
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


	SC::Close();
	return 0;
}
