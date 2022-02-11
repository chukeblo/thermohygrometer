#pragma once

#include <string>

#include "LogData.hpp"

class ConsoleLogger
{
private:
	static constexpr char* kInfoTag = "INFO";
	static constexpr char* kTraceTag = "TRACE";
	static constexpr char* kDebugTag = "DEBUG";
	static constexpr char* kErrorTag = "ERROR";

public:
	ConsoleLogger();
	~ConsoleLogger();

public:
	void Log(LogData* log_data);
private:
	void LogInfo(std::string class_name, std::string method_name, std::string info);
	void LogTrace(std::string class_name, std::string method_name, std::string info);
	void LogDebug(std::string class_name, std::string method_name, std::string info);
	void LogError(std::string class_name, std::string method_name, std::string info);
};