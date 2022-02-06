#include "ThermohygroDataMeasurer.hpp"

#include "LogConstants.hpp"
#include "Logger.hpp"

EnvironmentDataMeasurer::EnvironmentDataReader()
{
	pressure_sensor_.init();
}

EnvironmentDataMeasurer::~EnvironmentDataReader()
{
}

sMeasurementResult EnvironmentDataMeasurer::ReadThermohydroData()
{
	Logger::Log(Logger::kTraceBit, kThermohygroDataMeasurer, kReadThermohydroData, "in");
	sThermohydroData data = thermohydrosensor_.ReadThermohygroData();
	if (data.temperature == -1.0f && data.humidity == -1.0f)
	{
		Logger::Log(Logger::kErrorBit, kThermohygroDataMeasurer, kReadThermohydroData,
			"failed to read environment data"
		);
		return sMeasurementResult{ false, data };
	}

	Logger::Log(Logger::kInfoBit, kThermohygroDataMeasurer, kReadThermohydroData,
		std::string("out: temp=") + std::string(String(data.temperature).c_str()) +
		std::string(",humi=") + std::string(String(data.humidity).c_str())
	);

	return sThermohydroData{ true, data };
}