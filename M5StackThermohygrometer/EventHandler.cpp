#include "EventHandler.hpp"

#include <M5Stack.h>
#include "ConsoleLogger.hpp"
#include "LogConstants.hpp"
#include "MeasurementResultManager.hpp"

EventHandler* EventHandler::GetInstance()
{
	static EventHandler* instance = nullptr;
	if (!instance)
	{
		instance = new EventHandler();
	}
	return instance;
}

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::Initialize()
{
  	cui_manager_ = UIManagerBase::GetInstance(UIManagerType::kCuiManagerType);
}

void EventHandler::EventHandle()
{
	while (true)
	{
		EventType type = GetEvent();
		switch (type)
		{
		case EventType::kNone:
			return;
		default:
			ConsoleLogger::Log(new LogData(LogLevel::kError, kEventHandle, kEventHandle, "not supported event type"));
			break;
		}
	}
}

void EventHandler::AddEvent(EventType type)
{
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kEventHandler, kAddEvent,
		"in: type=" + std::string(String((int)type).c_str())
	));
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
