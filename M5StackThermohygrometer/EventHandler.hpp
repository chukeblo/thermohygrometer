#pragma once

#include <list>
#include "EventType.hpp"

class EventHandler
{
public:
	static EventHandler* GetInstance();
	void EventHandle();
	void AddEvent(EventType type);

private:
	EventHandler();
	~EventHandler();
	EventType GetEvent();

	std::list<EventType> event_queue_;
};
