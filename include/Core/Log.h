#pragma once

#include <string>

class Log
{
public:
	static void Info(const std::string& msg);
	static void Warning(const std::string& msg);
	static void Error(const std::string& msg);

private:
	enum class LogLevel
	{
		INFO,
		WARNING,
		ERROR
	};
	static void Print(LogLevel level, const std::string& msg);
};

#ifdef NDEBUG
	#define LOG_INFO(msg)
	#define LOG_WARN(msg)
	#define LOG_ERROR(msg) Log::Error(msg)
#else
	#define LOG_INFO(msg) Log::Info(msg)
	#define LOG_WARN(msg) Log::Warning(msg)
	#define LOG_ERROR(msg) Log::Error(msg)
#endif