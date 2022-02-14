#pragma once

#include <string>

#include "CommunicationClient.hpp"
#include "ThermohygroDataMeasurer.hpp"
#include "ThermohygrometerSettings.hpp"

class ThermohygrometerController
{
public:
	ThermohygrometerController();
	~ThermohygrometerController();

public:
	void MeasureThermohygroData();
private:
	std::string GetStringTimeFrom(struct tm* tm);

private:
	ThermohygrometerSettings* settings_;
	ThermohygroDataMeasurer* measurer_;
	CommunicationClient* client_;
};
