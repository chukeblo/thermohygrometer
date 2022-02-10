#include "ThermohygrometerController.hpp"

#include <M5Stack.h>
#include "EventData.hpp"
#include "EventHandler.hpp"
#include "EventType.hpp"
#include "LogConstants.hpp"
#include "Logger.hpp"
#include "MeasurementResult.hpp"
#include "SettingsProvider.hpp"
#include "ThermohygroData.hpp"

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
	Logger::Log(Logger::kTraceBit, kThermohygrometerController, kReadThermohygroData, "in");
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
				Logger::Log(Logger::kInfoBit, kThermohygrometerController, kReadThermohygroData,
					time_string + std::string(",temp=") + std::string(String(data->temperature).c_str()) +
					std::string(",humi=") + std::string(String(data->humidity).c_str())
				);
				MeasurementResult* result = new MeasurementResult(time_string, data);
				EventHandler::GetInstance()->AddEvent(new EventData(EventType::kReadEnvData, result));
			}
		}
		M5.Lcd.setCursor(100, 100);
		M5.Lcd.printf("%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
		delay(1000);
	}
	Logger::Log(Logger::kErrorBit, kThermohygrometerController, kReadThermohygroData,
		"accidentally exit from the collection data task thread"
	);
}
