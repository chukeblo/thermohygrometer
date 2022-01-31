#pragma once

#include <string>
#include "LogLevel.hpp"

class Logger
{
private:
	static constexpr char* kInfoTag = "INFO";
	static constexpr char* kTraceTag = "TRACE";
	static constexpr char* kDebugTag = "DEBUG";
	static constexpr char* kErrorTag = "ERROR";

public:
	Logger();
	~Logger();

public:
	static void Log(LogLevel level, std::string class_name, std::string method_name, std::string info);
	static void Log(LogLevel level, std::string class_name, std::string method_name, char* info);
private:
	static void LogInfo(std::string class_name, std::string method_name, std::string info);
	static void LogTrace(std::string class_name, std::string method_name, std::string info);
	static void LogError(std::string class_name, std::string method_name, std::string info);
	static void LogDebug(std::string class_name, std::string method_name, std::string info);
};