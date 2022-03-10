#pragma once

#include "UIManagerBase.hpp"

#include "GUIDrawer.hpp"

class GUIManager : public UIManagerBase
{
public:
	GUIManager();
	~GUIManager() override;

public:
	void Initialize() override;
	void HandleEvent(EventData* event_data) override;
	void CheckIfButtonsPressed();
private:
	void NotifyMeasurementRequest();

private:
	GUIDrawer* gui_drawer_;
};
