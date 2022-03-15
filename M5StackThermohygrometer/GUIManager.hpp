#pragma once

#include "ViewController.hpp"

class GUIManager
{
public:
	GUIManager();
	~GUIManager();

public:
	void CheckIfButtonsPressed();
	void NotifyEnvDataMeasured();

private:
	ViewController* view_controller_;
};
