#pragma once

#include "GUIContext.hpp"

class GUIManager
{
public:
	GUIManager(GUIContext* context);
	~GUIManager();

public:
	void CheckIfButtonsPressed();
	void NotifyEnvDataMeasured();

private:
	GUIContext* gui_context_;
};
