#pragma once

#include <MeasurementResult.hpp>

class CommunicationClient
{
public:
    virtual ~CommunicationClient() {}

public:
    virtual void Prepare() = 0;
    virtual void SendThermohygroData(MeasurementResult* result) = 0;
};