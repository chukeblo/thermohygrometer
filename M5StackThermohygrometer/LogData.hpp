#pragma once

#include <string>

#include "LogLevel.hpp"

class LogData
{
public:
    LogData(LogLevel level, std::string class_name, std::string method_name, std::string info)
    {
        this->level = level;
        this->class_name = class_name;
        this->method_name = method_name;
        this->info = info;
    }

    LogLevel level;
    std::string class_name;
    std::string method_name;
    std::string info;
};