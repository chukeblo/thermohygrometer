#pragma once

#include <list>

#include "EventData.hpp"
#include "ThermohygrometerController.hpp"
#include "GUIManager.hpp"
#include "UIManagerBase.hpp"

class EventHandler
{
public:
	static EventHandler* GetInstance();

private:
	EventHandler();
	~EventHandler();

public:
	void Initialize();
	void SetGUIManager(GUIManager* gui_manager);
	void EventHandle();
	void AddEvent(EventData* data);

private:
	EventData* GetEvent();

private:
	std::list<EventData*> event_queue_;
	ThermohygrometerController* thermohygrometer_controller_;
	GUIManager* gui_manager_;
	UIManagerBase* cui_manager_;
};
