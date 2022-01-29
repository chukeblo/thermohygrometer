#include "Logger.hpp"

#include <M5Stack.h>

static const char* kInfoTag = "INFO";
static const char* kTraceTag = "TRACE";
static const char* kDebugTag = "DEBUG";
static const char* kErrorTag= "ERROR";

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Log(LogLevel level, std::string class_name, std::string method_name, std::string info)
{
	switch (level)
	{
	case LogLevel::kInfo:
		LogInfo(class_name, method_name, info);
		break;
	case LogLevel::kTrace:
		LogTrace(class_name, method_name, info);
		break;
	case LogLevel::kDebug:
		LogDebug(class_name, method_name, info);
		break;
	case LogLevel::kError:
		LogError(class_name, method_name, info);
		break;
	default:
		break;
	}
}

void Logger::LogInfo(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n", kInfoTag, class_name.c_str(), method_name.c_str(), info.c_str());
}

void Logger::LogTrace(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n", kTraceTag, class_name.c_str(), method_name.c_str(), info.c_str());
}

void Logger::LogError(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n",kDebugTag, class_name.c_str(), method_name.c_str(), info.c_str());
}

void Logger::LogDebug(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n", kErrorTag, class_name.c_str(), method_name.c_str(), info.c_str());
}
