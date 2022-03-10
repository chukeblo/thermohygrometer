#include "ConsoleLogger.hpp"

#include <M5Stack.h>

const char* kInfoTag = "INFO";
const char* kTraceTag = "TRACE";
const char* kDebugTag = "DEBUG";
const char* kErrorTag = "ERROR";

ConsoleLogger::ConsoleLogger()
{
}

ConsoleLogger::~ConsoleLogger()
{
}

void ConsoleLogger::Log(LogData* log_data)
{
    switch (log_data->level)
    {
    case LogLevel::kInfo:
        LogInfo(log_data->class_name, log_data->method_name, log_data->info);
        break;
    case LogLevel::kTrace:
        LogTrace(log_data->class_name, log_data->method_name, log_data->info);
        break;
    case LogLevel::kDebug:
        LogDebug(log_data->class_name, log_data->method_name, log_data->info);
        break;
    case LogLevel::kError:
        LogError(log_data->class_name, log_data->method_name, log_data->info);
        break;
    }
    delete log_data;
}

void ConsoleLogger::LogInfo(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n", kInfoTag, class_name.c_str(), method_name.c_str(), info.c_str());
}

void ConsoleLogger::LogTrace(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n", kTraceTag, class_name.c_str(), method_name.c_str(), info.c_str());
}

void ConsoleLogger::LogDebug(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n",kDebugTag, class_name.c_str(), method_name.c_str(), info.c_str());
}

void ConsoleLogger::LogError(std::string class_name, std::string method_name, std::string info)
{
	Serial.printf("[%s] %s::%s() %s\n", kErrorTag, class_name.c_str(), method_name.c_str(), info.c_str());
}
