#include "EnvironmentDataCollector.hpp"

#include <M5Stack.h>

EnvironmentDataCollector::EnvironmentDataCollector()
{
    reader_ = new EnvironmentDataReader();
}

EnvironmentDataCollector::~EnvironmentDataCollector()
{
    delete reader_;
}

EnvironmentDataCollector *EnvironmentDataCollector::GetInstance()
{
    static EnvironmentDataCollector *instance = nullptr;
    if (!instance)
    {
        instance = new EnvironmentDataCollector();
    }
    return instance;
}

void EnvironmentDataCollector::CollectData()
{
    struct tm tm;
    while (true)
    {
        getLocalTime(&tm);
        if (hour_ != tm.tm_hour) {
            hour_ = tm.tm_hour;
            sThermohydroData data = reader_->ReadThermohydroData();
            M5.Lcd.setCursor(0, 140);
            M5.Lcd.printf("Temp: %2.1f 'C\nHumi: %2.0f\%\n", data.temperature, data.humidity);
        }
        M5.Lcd.setCursor(100, 100);
        M5.Lcd.printf("%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
        delay(1000);
    }
}

void StartDataCollectionTask(void *arg)
{
    EnvironmentDataCollector::GetInstance()->CollectData();
}