#include "EnvironmentDataReader.hpp"

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
	if (thermohydrosensor_.get() != kReadSuccess)
	{
		return sThermohydroData{ false, 0.0, 0.0 };
	}
	float temperature = thermohydrosensor_.cTemp;
	float humidity = thermohydrosensor_.humidity;
	return sThermohydroData{ true, temperature, humidity };
}