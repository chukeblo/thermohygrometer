#include "ThermohygroDataMeasurer.hpp"

#include "LogConstants.hpp"
#include "Logger.hpp"
#include "MeasurementResult.hpp"

ThermohygroDataMeasurer::ThermohygroDataMeasurer()
{
}

ThermohygroDataMeasurer::~ThermohygroDataMeasurer()
{
}

MeasurementResult ThermohygroDataMeasurer::ReadThermohygroData()
{
	Logger::Log(Logger::kTraceBit, kThermohygroDataMeasurer, kReadThermohygroData, "in");
	ThermohygroData data = thermohydrosensor_.ReadThermohygroData();
	if (data.temperature == -1.0f && data.humidity == -1.0f)
	{
		Logger::Log(Logger::kErrorBit, kThermohygroDataMeasurer, kReadThermohygroData,
			"failed to read environment data"
		);
		return MeasurementResult{ false, data };
	}

	Logger::Log(Logger::kInfoBit, kThermohygroDataMeasurer, kReadThermohygroData,
		std::string("out: temp=") + std::string(String(data.temperature).c_str()) +
		std::string(",humi=") + std::string(String(data.humidity).c_str())
	);

	return MeasurementResult { true, data };
}