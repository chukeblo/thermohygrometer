#pragma once

#include <string>

#include "LogData.hpp"

class ConsoleLogger
{
public:
	ConsoleLogger();
	~ConsoleLogger();

public:
	static void Log(LogData* log_data);
private:
	static void LogInfo(std::string class_name, std::string method_name, std::string info);
	static void LogTrace(std::string class_name, std::string method_name, std::string info);
	static void LogDebug(std::string class_name, std::string method_name, std::string info);
	static void LogError(std::string class_name, std::string method_name, std::string info);
};