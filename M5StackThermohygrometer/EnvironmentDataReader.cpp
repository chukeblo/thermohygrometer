#include "EnvironmentDataReader.hpp"

#include "LogConstants.hpp"
#include "Logger.hpp"

EnvironmentDataReader::EnvironmentDataReader()
{
	pressure_sensor_.init();
}

EnvironmentDataReader::~EnvironmentDataReader()
{
}

sThermohydroData EnvironmentDataReader::ReadThermohydroData()
{
	Logger::Log(LogLevel::kTrace, kEnvironmentDataReader, kReadThermohydroData, "in");
	if (thermohydrosensor_.TryReadEnvData() != kReadSuccess)
	{
		Logger::Log(LogLevel::kError, kEnvironmentDataReader, kReadThermohydroData,
			"failed to read environment data"
		);
		return sThermohydroData{ false, 0.0, 0.0 };
	}
	float temperature = thermohydrosensor_.GetCTemp();
	float humidity = thermohydrosensor_.GetHumidity();

	Logger::Log(LogLevel::kInfo, kEnvironmentDataReader, kReadThermohydroData,
		std::string("out: temp=") + std::string(String(temperature).c_str()) +
		std::string(",humi=") + std::string(String(humidity).c_str())
	);

	return sThermohydroData{ true, temperature, humidity };
}