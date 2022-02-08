#include "ThermohygrometerController.hpp"

#include <M5Stack.h>
#include "LogConstants.hpp"
#include "Logger.hpp"
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
	Logger::Log(Logger::kTraceBit, kThermohygrometerController, kReadThermohygroData, "in");
	struct tm tm;
	int hour = -1;
	while (true)
	{
		getLocalTime(&tm);
		if (hour != tm.tm_hour) {
			hour = tm.tm_hour;
			MeasurementResult result = measurer_->ReadThermohygroData();
			M5.Lcd.setCursor(0, 140);
			M5.Lcd.printf("Temp: %2.1f 'C\nHumi: %2.0f\%\n", result.thermohygro_data.temperature, result.thermohygro_data.humidity);

			Logger::Log(Logger::kInfoBit, kThermohygrometerController, kReadThermohygroData,
				std::string("time=") + std::string(String(tm.tm_hour).c_str()) + std::string(":") +
				std::string(String(tm.tm_min).c_str()) + std::string(":") + std::string(String(tm.tm_sec).c_str()) +
				std::string(",temp=") + std::string(String(result.thermohygro_data.temperature).c_str()) +
				std::string(",humi=") + std::string(String(result.thermohygro_data.humidity).c_str())
			);
		}
		M5.Lcd.setCursor(100, 100);
		M5.Lcd.printf("%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
		delay(1000);
	}
	Logger::Log(Logger::kErrorBit, kThermohygrometerController, kReadThermohygroData,
		"accidentally exit from the collection data task thread"
	);
}