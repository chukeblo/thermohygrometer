#pragma once

#include <list>

#include "EventType.hpp"
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
	void EventHandle();
	void AddEvent(EventType type);

private:
	EventType GetEvent();

private:
	std::list<EventType> event_queue_;
	UIManagerBase* cui_manager_;
};
