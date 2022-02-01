#pragma once

#include <string>

class Logger
{
public:
	static const uint8_t kInfoBit = 1;
	static const uint8_t kTraceBit = 2;
	static const uint8_t kDebugBit = 4;
	static const uint8_t kErrorBit = 8;
private:
	static constexpr char* kInfoTag = "INFO";
	static constexpr char* kTraceTag = "TRACE";
	static constexpr char* kDebugTag = "DEBUG";
	static constexpr char* kErrorTag = "ERROR";

public:
	Logger();
	~Logger();

public:
	static void Log(uint8_t level, std::string class_name, std::string method_name, std::string info);
	static void Log(uint8_t level, std::string class_name, std::string method_name, char* info);
private:
	static void LogInfo(std::string class_name, std::string method_name, std::string info);
	static void LogTrace(std::string class_name, std::string method_name, std::string info);
	static void LogError(std::string class_name, std::string method_name, std::string info);
	static void LogDebug(std::string class_name, std::string method_name, std::string info);
};