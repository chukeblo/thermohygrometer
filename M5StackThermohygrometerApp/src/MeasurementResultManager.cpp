#include "MeasurementResultManager.hpp"

#include <M5Stack.h>
#include "ConsoleLogger.hpp"
#include "LogConstants.hpp"

static const int kMaxResultCounts = 20;

MeasurementResultManager* MeasurementResultManager::GetInstance()
{
    static MeasurementResultManager* instance = nullptr;
    if (!instance)
    {
        instance = new MeasurementResultManager();
    }
    return instance;
}

MeasurementResultManager::MeasurementResultManager()
{
}

MeasurementResultManager::~MeasurementResultManager()
{
}

void MeasurementResultManager::AddMeasurementResult(MeasurementResult* result)
{
    ConsoleLogger::Log(new LogData(LogLevel::kDebug, kMeasurementResultManager, kAddMeasurementResult,
        "count=" + std::string(String(results_.size() + 1).c_str()) +
        ", time=" + result->time + ", temperature=" + std::string(String(result->thermohygro_data->temperature).c_str()) +
        ", humidity=" + std::string(String(result->thermohygro_data->humidity).c_str())
    ));
    if (IsFull())
    {
        results_.pop_front();
    }
    results_.push_back(MeasurementResult::CopyWith(result));
}

std::list<MeasurementResult*> MeasurementResultManager::GetResults()
{
    return results_;
}

bool MeasurementResultManager::IsFull()
{
    return (results_.size() >= kMaxResultCounts);
}