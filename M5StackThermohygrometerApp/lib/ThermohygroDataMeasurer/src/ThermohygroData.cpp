#include <ThermohygroData.hpp>

ThermohygroData::ThermohygroData(float temperature, float humidity)
{
	this->temperature = temperature;
	this->humidity = humidity;
}

ThermohygroData::~ThermohygroData()
{
}

ThermohygroData* ThermohygroData::CopyWith(ThermohygroData* base)
{
	if (!base)
	{
		return nullptr;
	}
	return new ThermohygroData(base->temperature, base->humidity);
}
