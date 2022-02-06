#pragma once

#include "ThermohygroDataMeasurer.hpp"

class ThermohygrometerController
{
public:
	ThermohygrometerController();
	~ThermohygrometerController();

public:
	void MeasureThermohygroData();

private:
	ThermohygroDataMeasurer* measurer_;
};
