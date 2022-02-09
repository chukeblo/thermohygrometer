#pragma once

#include "SHT3X.h"
#include "ThermohygroData.hpp"

class ThermohygroDataMeasurer
{
private:
	const int kReadSuccess = 0;

public:
	ThermohygroDataMeasurer();
	~ThermohygroDataMeasurer();

public:
	ThermohygroData* ReadThermohygroData();

private:
	SHT3X thermohydrosensor_;
};