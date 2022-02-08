#pragma once

#include <list>

#include "EventData.hpp"

class EventHandler
{
public:
	static EventHandler* GetInstance();

private:
	EventHandler();
	~EventHandler();

public:
	void EventHandle();
	void AddEvent(EventData* data);

private:
	EventData* GetEvent();

private:
	std::list<EventData*> event_queue_;
};
