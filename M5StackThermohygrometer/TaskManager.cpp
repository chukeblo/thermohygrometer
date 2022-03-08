#include "TaskManager.hpp"

static const int kMeasureTaskCore = 0;
static const int kMeasureTaskPriority = 0;
static const std::string kMeasureTask = "MeasureTask";

TaskManager* TaskManager::GetInstance()
{
    static TaskManager* instance = nullptr;
    if (!instance)
    {
        instance = new TaskManager();
    }
    return instance;
}

TaskManager::TaskManager()
{
    measure_task_handler_ = TaskHandle_t
}

TaskManager::~TaskManager()
{
}

bool TaskManager::CreateTask(std::string task_method, void* context = nullptr)
{
    if (task_method.empty())
    {
        return false;
    }

    if (task_method == kMeasureTask)
    {
        xTaskCreatePinnedToCore(StartMeasureTask, kMeasureTask.c_str(), 4096, context, kMeasureTaskPriority, &measure_task_handler_, kMeasureTaskCore);
        return true;
    }
    return false;
}

bool TaskManager::DeleteTask(std::string task_method)
{
    if (task_method.empty())
    {
        return false;
    }

    if (task_method == kMeasureTask)
    {
        vTaskDelete(measure_task_handler_);
        return true;
    }
    return false;
}