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
	client_ = new CommunicationClient(settings_->aws_communication_settings);
	measurer_ = new ThermohygroDataMeasurer();
}

ThermohygrometerController::~ThermohygrometerController()
{
	delete settings_;
	delete client_;
	delete measurer_;
}

void ThermohygrometerController::MeasureThermohygroData()
{
	LogData* log_data = new LogData(LogLevel::kTrace, kThermohygrometerController, kReadThermohygroData, "in");
	EventHandler* event_handler = EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	struct tm tm;
	getLocalTime(&tm);
	ThermohygroData* data = measurer_->ReadThermohygroData();
	if (data)
	{
		std::string time_string = GetStringTimeFrom(&tm);
		log_data = new LogData(LogLevel::kInfo, kThermohygrometerController, kReadThermohygroData,
			time_string + std::string(",temp=") + std::string(String(data->temperature).c_str()) +
			std::string(",humi=") + std::string(String(data->humidity).c_str())
		);
		event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
		MeasurementResult* result = new MeasurementResult(time_string, data);
		event_handler->AddEvent(new EventData(EventType::kReadEnvData, result));
	}
}

std::string ThermohygrometerController::GetStringTimeFrom(struct tm* tm)
{
	return std::string("time=") + std::string(String(tm->tm_hour).c_str()) + std::string(":") +
			std::string(String(tm->tm_min).c_str()) + std::string(":") + std::string(String(tm->tm_sec).c_str());
}