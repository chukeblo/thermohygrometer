#pragma once

#include "SHT3X.h"
#include "MeasurementResult.hpp"

class ThermohygroDataMeasurer
{
private:
	const int kReadSuccess = 0;

public:
	ThermohygroDataMeasurer();
	~ThermohygroDataMeasurer();

public:
	MeasurementResult ReadThermohygroData();

private:
	SHT3X thermohydrosensor_;
};