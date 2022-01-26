#include "EventHandler.hpp"

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

EventHandler* EventHandler::GetInstance()
{
	static EventHandler* instance = nullptr;
	if (!instance)
	{
		instance = new EventHandler();
	}
	return instance;
}

void EventHandler::EventHandle()
{
	EventType type = GetEvent();
	if (type == EventType::kNone)
	{
		return;
	}
	switch (type)
	{
	case EventType::kReadEnvData:
		break;
	case EventType::kMiddleButtonPressed:
		break;
	case EventType::kRightButtonPressed:
		break;
	default:
		break;
	}
}

void EventHandler::AddEvent(EventType type)
{
	event_queue_.push_back(type);
}

EventType EventHandler::GetEvent()
{
	if (event_queue_.empty())
	{
		return EventType::kNone;
	}
	EventType type = event_queue_.front();
	event_queue_.pop_front();
	return type;
}