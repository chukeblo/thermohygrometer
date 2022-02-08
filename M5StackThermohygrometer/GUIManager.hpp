#pragma once

#include "UIManagerBase.hpp"

#include "ButtonInputWatcher.hpp"

class GUIManager : public UIManagerBase
{
public:
	GUIManager();
	~GUIManager() override;

public:
	void Initialize() override;
	void HandleEvent(EventData* event_data) override;

private:
	ButtonInputWatcher* button_input_watcher_;
};
