#pragma once

#include "EnvironmentDataReader.hpp"

class EnvironmentDataCollector
{
public:
    static EnvironmentDataCollector *GetInstance();
    void CollectData();

private:
    EnvironmentDataCollector();
    ~EnvironmentDataCollector();

    EnvironmentDataReader *reader_;
    int8_t hour_;
};

void StartDataCollectionTask(void *arg);