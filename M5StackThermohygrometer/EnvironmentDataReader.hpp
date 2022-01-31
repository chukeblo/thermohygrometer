#pragma once

#include "src/UNIT_ENV/UNIT_ENV.hpp"
#include "ThermohydroData.hpp"

class EnvironmentDataReader
{
private:
	const int kReadSuccess = 0;

public:
	EnvironmentDataReader();
	~EnvironmentDataReader();

public:
	sThermohydroData ReadThermohydroData();

private:
	SHT3X thermohydrosensor_;
	QMP6988 pressure_sensor_;
};