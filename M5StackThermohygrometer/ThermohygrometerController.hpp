#pragma once

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
	ThermohygrometerSettings* settings_;
	ThermohygroDataMeasurer* measurer_;
};
