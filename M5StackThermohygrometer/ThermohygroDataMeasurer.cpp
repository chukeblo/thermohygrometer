#include "ThermohygroDataMeasurer.hpp"

#include "EventHandler.hpp"
#include "LogConstants.hpp"
#include "LogData.hpp"
#include "MeasurementResult.hpp"

ThermohygroDataMeasurer::ThermohygroDataMeasurer()
{
}

ThermohygroDataMeasurer::~ThermohygroDataMeasurer()
{
}

ThermohygroData* ThermohygroDataMeasurer::ReadThermohygroData()
{
	LogData* log_data = new LogData(LogLevel::kTrace, kThermohygroDataMeasurer, kReadThermohygroData, "in");
	EventHandler* event_handler =EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	ThermohygroData* data = thermohydrosensor_.ReadThermohygroData();
	if (!data)
	{
		log_data = new LogData(LogLevel::kError, kThermohygroDataMeasurer, kReadThermohygroData,
			"failed to read environment data"
		);
		event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
		return nullptr;
	}

	log_data = new LogData(LogLevel::kInfo, kThermohygroDataMeasurer, kReadThermohygroData,
		std::string("out: temp=") + std::string(String(data->temperature).c_str()) +
		std::string(",humi=") + std::string(String(data->humidity).c_str())
	);
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));

	return data;
}