#include "EnvironmentDataCollector.hpp"

#include <M5Stack.h>
#include "LogConstants.hpp"
#include "Logger.hpp"

EnvironmentDataCollector* EnvironmentDataCollector::GetInstance()
{
	static EnvironmentDataCollector* instance = nullptr;
	if (!instance)
	{
		instance = new EnvironmentDataCollector();
	}
	return instance;
}

EnvironmentDataCollector::EnvironmentDataCollector()
{
	reader_ = new EnvironmentDataReader();
}

EnvironmentDataCollector::~EnvironmentDataCollector()
{
	delete reader_;
}

void EnvironmentDataCollector::CollectData()
{
	Logger::Log(LogLevel::kTrace, kEnvironmentDataCollector, kCollectData, "in");
	struct tm tm;
	while (true)
	{
		getLocalTime(&tm);
		if (hour_ != tm.tm_hour) {
			hour_ = tm.tm_hour;
			sThermohydroData data = reader_->ReadThermohydroData();
			M5.Lcd.setCursor(0, 140);
			M5.Lcd.printf("Temp: %2.1f 'C\nHumi: %2.0f\%\n", data.temperature, data.humidity);

			Logger::Log(LogLevel::kInfo, kEnvironmentDataCollector, kCollectData,
				std::string("time=") + std::string(String(tm.tm_hour).c_str()) + std::string(":") +
				std::string(String(tm.tm_min).c_str()) + std::string(":") + std::string(String(tm.tm_sec).c_str()) +
				std::string(",temp=") + std::string(String(data.temperature).c_str()) +
				std::string(",humi=") + std::string(String(data.humidity).c_str())
			);
		}
		M5.Lcd.setCursor(100, 100);
		M5.Lcd.printf("%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
		delay(1000);
	}
	Logger::Log(LogLevel::kError, kEnvironmentDataCollector, kCollectData,
		"accidentally exit from the collection data task thread"
	);
}

void StartDataCollectionTask(void* arg)
{
	EnvironmentDataCollector::GetInstance()->CollectData();
}