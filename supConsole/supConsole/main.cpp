// supConsole.cpp : définit le point d'entrée de l'application.
//

#include "supConsole.hpp"


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
	for (int i = 0; i < 512; i++)
	{
		if (argv[0][i] == '\\' )
		{
			argv[0][i] = '/';
		}
	} // change the address 
	std::string fpath = GetPrevDirectoryPath(argv[0]); // argv[0] is the executable path so we want to get the folder path no the executable 
	SC::init(0, 0, &fpath, argv); // init the console
	ConsolePrint("", SC::ConsoleAttribute(SC::ConsolePrintAttribute::RESET, SC::WHITE, SC::BLACK)); // reset


	while (true) // main loop, to do create a exit function
	{
		SC::start();

		std::string input;

		char* s = new char[1000];
		fgets(s, 1000, stdin);
		input = s;
		
		SC::process(input);

		delete[] s;

	}


	SC::Close(); 
	return 0;
}
