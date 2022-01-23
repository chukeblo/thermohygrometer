#pragma once

#include "src/UNIT_ENV/UNIT_ENV.h"
#include "ThermohydroData.hpp"

class EnvironmentDataReader
{
public:
    EnvironmentDataReader();
    ~EnvironmentDataReader();
    sThermohydroData ReadThermohydroData();

private:
    SHT3X thermohydrosensor_;
    QMP6988 pressure_sensor_;
};