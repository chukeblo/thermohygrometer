#pragma once

class ThermohygroData
{
public:
	ThermohygroData(float temperature, float humidity);
	~ThermohygroData();

public:
	static ThermohygroData* CopyWith(ThermohygroData* base);

public:
	float temperature;
	float humidity;
};