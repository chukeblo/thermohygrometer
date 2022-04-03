#pragma once

#include <string>

#include <ThermohygroData.hpp>

class MeasurementResult
{
public:
    MeasurementResult(std::string time, ThermohygroData* thermohygro_data);
    ~MeasurementResult();

public:
    static MeasurementResult* CopyWith(MeasurementResult* base);
    std::string ToString();

public:
    std::string time;
    ThermohygroData* thermohygro_data;
};