#pragma once

class ThermohygroData
{
public:
	ThermohygroData(float temperature, float humidity)
	{
		this->temperature = temperature;
		this->humidity = humidity;
	}

	float temperature;
	float humidity;
};