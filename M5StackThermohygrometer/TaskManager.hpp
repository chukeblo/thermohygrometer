#pragma once

#include <map>
#include <string>

class TaskManager
{
public:
    static TaskManager* GetInstance();

private:
    TaskManager();
    ~TaskManager();

public:
    bool CreateTask(std::string task_method, void* context = nullptr);
    bool DeleteTask(std::string task_method);

private:
    TaskHandle_t measure_task_handler_;
};