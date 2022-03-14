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
	bool IsTimeForMeasurement(int current_mins);
	bool IsTimeForSendingEnvData(int current_hours);
	std::string GetStringTimeFrom(struct tm* tm);

private:
	SHT3X thermohydrosensor_;
	int next_measure_mins_;
	int next_sending_hours_;
};

void StartMeasureTask(void* context);