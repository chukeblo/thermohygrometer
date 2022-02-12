#include "ThermohygrometerController.hpp"

#include <M5Stack.h>
#include "EventHandler.hpp"
#include "LogConstants.hpp"
#include "LogData.hpp"
#include "MeasurementResult.hpp"
#include "SettingsProvider.hpp"

ThermohygrometerController::ThermohygrometerController()
{
	settings_ = SettingsProvider::Of();
	measurer_ = new ThermohygroDataMeasurer();
}

ThermohygrometerController::~ThermohygrometerController()
{
	delete measurer_;
}

void ThermohygrometerController::MeasureThermohygroData()
{
	LogData* log_data = new LogData(LogLevel::kTrace, kThermohygrometerController, kReadThermohygroData, "in");
	EventHandler* event_handler = EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	struct tm tm;
	int hour = -1;
	while (true)
	{
		getLocalTime(&tm);
		if (hour != tm.tm_hour) {
			hour = tm.tm_hour;
			ThermohygroData* data = measurer_->ReadThermohygroData();
			if (data)
			{
				std::string time_string = std::string("time=") + std::string(String(tm.tm_hour).c_str()) + std::string(":") +
					std::string(String(tm.tm_min).c_str()) + std::string(":") + std::string(String(tm.tm_sec).c_str());
				log_data = new LogData(LogLevel::kInfo, kThermohygrometerController, kReadThermohygroData,
					time_string + std::string(",temp=") + std::string(String(data->temperature).c_str()) +
					std::string(",humi=") + std::string(String(data->humidity).c_str())
				);
				event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
				MeasurementResult* result = new MeasurementResult(time_string, data);
				event_handler->AddEvent(new EventData(EventType::kReadEnvData, result));
			}
		}
		M5.Lcd.setCursor(100, 100);
		M5.Lcd.printf("%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
		delay(1000);
	}
	log_data = new LogData(LogLevel::kError, kThermohygrometerController, kReadThermohygroData,
		"accidentally exit from the collection data task thread"
	);
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
}
