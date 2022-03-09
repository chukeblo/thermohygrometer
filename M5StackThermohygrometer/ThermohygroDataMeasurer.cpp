#include "ThermohygroDataMeasurer.hpp"

#include "EventHandler.hpp"
#include "MeasurementResult.hpp"

ThermohygroDataMeasurer::ThermohygroDataMeasurer()
{
}

ThermohygroDataMeasurer::~ThermohygroDataMeasurer()
{
}

void ThermohygroDataMeasurer::ReadThermohygroData()
{
	struct tm tm;
	getLocalTime(&tm);
	int prev_measure_minutes = -1;

	while (true)
	{
		getLocalTime(&tm);
		if (tm.tm_min != prev_measure_minutes)
		{
			prev_measure_minutes = tm.tm_min;
			ThermohygroData* data = thermohydrosensor_.ReadThermohygroData();
			if (data)
			{
				MeasurementResult* result = new MeasurementResult(GetStringTimeFrom(&tm), data);
				EventHandler::GetInstance()->AddEvent(new EventData(EventType::kReadEnvData, (void*)result));
			}
		}
		delay(1000);
	}
}

std::string ThermohygroDataMeasurer::GetStringTimeFrom(struct tm* tm)
{
	return std::string("time=") + std::string(String(tm->tm_hour).c_str()) + std::string(":") +
			std::string(String(tm->tm_min).c_str()) + std::string(":") + std::string(String(tm->tm_sec).c_str());
}

void StartMeasureTask(void* context)
{
	ThermohygroDataMeasurer* measurer = static_cast<ThermohygroDataMeasurer*>(context);
	measurer->ReadThermohygroData();
}