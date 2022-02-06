#pragma once

#include "ThermohydroData.hpp"

typedef struct MeasurementResult
{
    bool is_succeeded;
    ThermohydroData thermohygro_data;
};