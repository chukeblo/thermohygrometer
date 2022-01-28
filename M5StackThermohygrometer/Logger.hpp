#pragma once

#include <string>
#include "LogLevel.hpp"

class Logger
{
public:
	Logger();
	~Logger();
	static void Log(LogLevel level, std::string class_name, std::string method_name, std::string info);
private:
	static void LogInfo(std::string class_name, std::string method_name, std::string info);
	static void LogError(std::string class_name, std::string method_name, std::string info);
	static void LogDebug(std::string class_name, std::string method_name, std::string info);
};