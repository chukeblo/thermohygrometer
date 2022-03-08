#pragma once

#include <string>

#include "SHT3X.h"

class ThermohygroDataMeasurer
{
private:
	const int kReadSuccess = 0;

public:
	ThermohygroDataMeasurer();
	~ThermohygroDataMeasurer();

public:
	void ReadThermohygroData();

private:
	std::string GetStringTimeFrom(struct tm* tm);

private:
	SHT3X thermohydrosensor_;
};

void StartMeasureTask(void* context);