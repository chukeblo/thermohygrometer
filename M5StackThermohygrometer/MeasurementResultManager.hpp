#pragma once

#include <list>

#include "MeasurementResult.hpp"

class MeasurementResultManager
{
public:
    static MeasurementResultManager* GetInstance();

private:
    MeasurementResultManager();
    ~MeasurementResultManager();

public:
    void AddMeasurementResult(MeasurementResult* result);
    std::list<MeasurementResult*> GetResults();

private:
    std::list<MeasurementResult*> results_;
};