#pragma once

#include "MeasurementResult.hpp"

class GUIDrawer
{
public:
	GUIDrawer();
	~GUIDrawer();

public:
	void DisplayMeasurementResult(MeasurementResult* result);
};