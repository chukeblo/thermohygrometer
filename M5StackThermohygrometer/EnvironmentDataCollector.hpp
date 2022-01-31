#pragma once

#include "EnvironmentDataReader.hpp"

class EnvironmentDataCollector
{
public:
	static EnvironmentDataCollector* GetInstance();

private:
	EnvironmentDataCollector();
	~EnvironmentDataCollector();

public:
	void CollectData();

private:
	EnvironmentDataReader* reader_;
	int8_t hour_;
};

void StartDataCollectionTask(void* arg);