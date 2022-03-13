#pragma once

class ThermohygroData
{
public:
	ThermohygroData(float temperature, float humidity);
	~ThermohygroData();

public:
	static ThermohygroData* CopyWith(ThermohygroData* base);

private:
	float temperature;
	float humidity;
};