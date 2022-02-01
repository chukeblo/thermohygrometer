#include "Logger.hpp"

#include <M5Stack.h>

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Log(uint8_t level, std::string class_name, std::string method_name, std::string info)
{
	if (level & kInfoBit > 0)
	{
		LogInfo(class_name, method_name, info);
	}
	else if (level & kTraceBit > 0)
	{
		LogTrace(class_name, method_name, info);
	}
	else if (level & kDebugBit > 0)
	{
		LogDebug(class_name, method_name, info);
	}
	else if (level & kErrorBit > 0)
	{
		LogError(class_name, method_name, info);
	}
}

void Logger::Log(uint8_t level, std::string class_name, std::string method_name, char* info)
{
	Log(level, class_name, method_name, std::string(info));
}

void Logger::LogInfo(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n", kInfoTag, class_name.c_str(), method_name.c_str(), info.c_str());
}

void Logger::LogTrace(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n", kTraceTag, class_name.c_str(), method_name.c_str(), info.c_str());
}

void Logger::LogDebug(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n",kDebugTag, class_name.c_str(), method_name.c_str(), info.c_str());
}

void Logger::LogError(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n", kErrorTag, class_name.c_str(), method_name.c_str(), info.c_str());
}
