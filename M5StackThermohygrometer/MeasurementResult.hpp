#pragma once

#include <string>

#include "ThermohygroData.hpp"

class MeasurementResult
{
public:
    MeasurementResult(std::string time, ThermohygroData* thermohygro_data)
    {
        this->time = time;
        this->thermohygro_data = thermohygro_data;
    }
    ~MeasurementResult()
    {
        delete this->thermohygro_data;
    }

    std::string time;
    ThermohygroData* thermohygro_data;
};