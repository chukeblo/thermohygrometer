#pragma once

#include "ThermohygroData.hpp"

struct MeasurementResult
{
    bool is_succeeded;
    ThermohygroData thermohygro_data;
};