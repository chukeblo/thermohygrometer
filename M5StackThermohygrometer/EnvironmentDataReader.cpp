#include "EnvironmentDataReader.hpp"

#include "LogConstants.hpp"
#include "Logger.hpp"

static const int kReadSuccess = 0;

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
	if (thermohydrosensor_.get() != kReadSuccess)
	{
		Logger::Log(LogLevel::kError, kEnvironmentDataReader, kReadThermohydroData,
			"failed to read environment data"
		);
		return sThermohydroData{ false, 0.0, 0.0 };
	}
	float temperature = thermohydrosensor_.cTemp;
	float humidity = thermohydrosensor_.humidity;

	Logger::Log(LogLevel::kInfo, kEnvironmentDataReader, kReadThermohydroData,
		std::string("out: temp=") + std::string(String(temperature).c_str()) +
		std::string(",humi=") + std::string(String(humidity).c_str())
	);

	return sThermohydroData{ true, temperature, humidity };
}