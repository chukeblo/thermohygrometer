#pragma once

#include <map>
#include <string>

#include <M5Stack.h>

class TaskManager
{
public:
    TaskManager();
    ~TaskManager();

public:
    bool CreateTask(std::string task_method, void* context);
    bool DeleteTask(std::string task_method);
    static std::string GetMeasureTaskToken();

private:
    TaskHandle_t measure_task_handler_;
};