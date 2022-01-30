#pragma once

#include <list>
#include "EventData.hpp"

class EventHandler
{
public:
	static EventHandler* GetInstance();
	void EventHandle();
	void AddEvent(sEventData data);

private:
	EventHandler();
	~EventHandler();
	sEventData GetEvent();

	std::list<sEventData> event_queue_;
};
