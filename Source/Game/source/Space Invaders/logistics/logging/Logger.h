#pragma once
#include <string>
#include <tge/math/color.h>
namespace si
{
	std::string FilterPath(const char* aFile, std::string someArgs);
	void Log(std::string aType,std::string aMessage, ...);
#define LOG(x) Log("[Log]",std::string("[") + FilterPath(__FILE__, "\\") + std::string(", Line ") + std::to_string(__LINE__) + std::string("]: ")+ std::string(x))
#define ERROR_LOG(x) Log("[Error]",std::string("[") + FilterPath(__FILE__, "\\") + std::string(", Line ") + std::to_string(__LINE__) + std::string("]: ")+ std::string(x))
}