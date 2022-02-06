#pragma once

#include "SHT3X.h"
#include "MeasurementResult.hpp"

class EnvironmentDataMeasurer
{
private:
	const int kReadSuccess = 0;

public:
	EnvironmentDataMeasurer();
	~EnvironmentDataMeasurer();

public:
	sMeasurementResult ReadThermohydroData();

private:
	SHT3X thermohydrosensor_;
};