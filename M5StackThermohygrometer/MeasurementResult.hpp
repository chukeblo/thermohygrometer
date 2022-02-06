#pragma once

#include "ThermohydroData.hpp"

typedef struct MeasurementResult
{
    bool is_succeeded;
    sThermohydroData thermohygro_data;
} sMeasurementResult;