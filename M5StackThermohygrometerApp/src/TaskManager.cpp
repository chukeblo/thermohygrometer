#include "TaskManager.hpp"

#include "ConsoleLogger.hpp"
#include "LogConstants.hpp"
#include "ThermohygroDataMeasurer.hpp"

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
}

TaskManager::~TaskManager()
{
}

bool TaskManager::CreateTask(std::string task_method, void* context)
{
    ConsoleLogger::Log(new LogData(LogLevel::kDebug, kTaskManager, kCreateTask,
        "task method = \"" + task_method + "\""
    ));
    if (task_method.empty())
    {
        ConsoleLogger::Log(new LogData(LogLevel::kError, kTaskManager, kCreateTask, "task method name must be specified."));
        return false;
    }

    if (task_method == kMeasureTask)
    {
        xTaskCreatePinnedToCore(StartMeasureTask, kMeasureTask.c_str(), 8192, context, kMeasureTaskPriority, &measure_task_handler_, kMeasureTaskCore);
        return true;
    }
    ConsoleLogger::Log(new LogData(LogLevel::kError, kCreateTask, kCreateTask,
        "no matched task was found with given task method name: \"" + task_method + "\""
    ));
    return false;
}

bool TaskManager::DeleteTask(std::string task_method)
{
    ConsoleLogger::Log(new LogData(LogLevel::kDebug, kTaskManager, kDeleteTask,
        "task method = \"" + task_method + "\""
    ));
    if (task_method.empty())
    {
        ConsoleLogger::Log(new LogData(LogLevel::kError, kTaskManager, kDeleteTask, "task method name must be specified."));
        return false;
    }

    if (task_method == kMeasureTask)
    {
        vTaskDelete(measure_task_handler_);
        return true;
    }
    ConsoleLogger::Log(new LogData(LogLevel::kError, kCreateTask, kDeleteTask,
        "no matched task was found with given task method name: \"" + task_method + "\""
    ));
    return false;
}
