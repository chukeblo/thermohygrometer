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

MeasurementResult* ThermohygroDataMeasurer::ReadThermohygroData()
{
	Logger::Log(Logger::kTraceBit, kThermohygroDataMeasurer, kReadThermohygroData, "in");
	ThermohygroData* data = thermohydrosensor_.ReadThermohygroData();
	if (!data)
	{
		Logger::Log(Logger::kErrorBit, kThermohygroDataMeasurer, kReadThermohygroData,
			"failed to read environment data"
		);
		return new MeasurementResult(false, nullptr);
	}

	Logger::Log(Logger::kInfoBit, kThermohygroDataMeasurer, kReadThermohygroData,
		std::string("out: temp=") + std::string(String(data->temperature).c_str()) +
		std::string(",humi=") + std::string(String(data->humidity).c_str())
	);

	return new MeasurementResult(true, data);
}