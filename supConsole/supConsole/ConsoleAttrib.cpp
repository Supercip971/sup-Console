#include "ConsoleUtil.hpp"
namespace SC {


	ConsoleAttribute::ConsoleAttribute(ConsolePrintAttribute cpa, ConsoleCol fcol, ConsoleCol bcol)
	{
		CAcpa = cpa;
		CAccf = fcol;
		CAccb = bcol;
	}

	ConsoleAttribute::ConsoleAttribute(ConsoleCol fcol)
	{
		CAcpa = ConsolePrintAttribute::RESET;
		CAccf = fcol;
		CAccb = ConsoleCol::BLACK;
	}

	ConsoleAttribute::ConsoleAttribute(ConsoleCol fcol, ConsoleCol bcol)
	{
		CAcpa = ConsolePrintAttribute::RESET;
		CAccf = fcol;
		CAccb = bcol;
	}

	ConsoleAttribute::ConsoleAttribute(ConsolePrintAttribute cpa)
	{
		CAcpa = cpa;
		CAccf = ConsoleCol::WHITE;
		CAccb = ConsoleCol::BLACK;
	}

	std::string ConsoleAttribute::AttribToString()
	{

		std::string str;
		str = "\x1B[" + std::to_string(CAcpa) + ";" + std::to_string(CAccf) + ";" + std::to_string(CAccb + 10) + "m";
		return str;
	}
}