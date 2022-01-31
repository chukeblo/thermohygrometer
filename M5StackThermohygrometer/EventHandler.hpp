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
	void AddEvent(sEventData data);

private:
	sEventData GetEvent();

private:
	std::list<sEventData> event_queue_;
};
