#include "Logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <iostream>

#pragma warning (disable : 4840) //variadic function warning

std::string si::FilterPath(const char* aFile, std::string someArgs)
{
	std::string file = std::string(aFile);
	size_t found = file.find_last_of(someArgs);
	return file.substr(found + 1);
}

void si::Log(std::string aType, std::string aMessage, ...)
{
#ifndef _RETAIL

	std::cout << aType << aMessage << std::endl;



#endif
}
