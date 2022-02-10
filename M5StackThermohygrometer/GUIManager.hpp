#pragma once

#include "UIManagerBase.hpp"

#include "ButtonInputWatcher.hpp"
#include "GUIDrawer.hpp"

class GUIManager : public UIManagerBase
{
public:
	GUIManager();
	~GUIManager() override;

public:
	void Initialize() override;
	void HandleEvent(EventData* event_data) override;
private:
	void NotifyMeasurementRequest();

private:
	ButtonInputWatcher* button_input_watcher_;
	GUIDrawer* gui_drawer_;
};
