#pragma once

#include "MeasurementResult.hpp"
#include "ViewController.hpp"

class GUIManager
{
public:
	GUIManager();
	~GUIManager();

public:
	void CheckIfButtonsPressed();
	void NotifyMeasurementResult(MeasurementResult* result);

private:
	ViewController* view_controller_;
};
