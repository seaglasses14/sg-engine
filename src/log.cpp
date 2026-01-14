#include "log.h"
#include <iostream>

void Log::Info(const std::string& msg)
{
	Print(LogLevel::INFO, msg);
}
void Log::Warning(const std::string& msg)
{
	Print(LogLevel::WARNING, msg);
}
void Log::Error(const std::string& msg)
{
	Print(LogLevel::ERROR, msg);
}
void Log::Print(LogLevel level, const std::string& msg)
{
	switch (level)
	{
		case LogLevel::INFO:
			std::cout << "[INFO] ";
			break;
		case LogLevel::WARNING:
			std::cout << "[WARNING] ";
			break;
		case LogLevel::ERROR:
			std::cout << "[ERROR] ";
			break;
	}
	std::cout << msg << std::endl;
}