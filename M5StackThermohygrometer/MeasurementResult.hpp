#pragma once

#include "ThermohygroData.hpp"

class MeasurementResult
{
public:
    MeasurementResult(bool is_succeeded, ThermohygroData* thermohygro_data)
    {
        this->is_succeeded = is_succeeded;
        this->thermohygro_data = thermohygro_data;
    }

    bool is_succeeded;
    ThermohygroData* thermohygro_data;
};