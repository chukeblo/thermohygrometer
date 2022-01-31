#include "EventHandler.hpp"

#include <M5Stack.h>
#include "LogConstants.hpp"
#include "Logger.hpp"

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

void EventHandler::EventHandle()
{
	sEventData data = GetEvent();
	if (data.type == EventType::kNone)
	{
		return;
	}
	switch (data.type)
	{
	case EventType::kReadEnvData:
		break;
	case EventType::kMiddleButtonPressed:
		break;
	case EventType::kRightButtonPressed:
		break;
	default:
		Logger::Log(LogLevel::kError, kEventHandle, kEventHandle, "not supported event type");
		break;
	}
}

void EventHandler::AddEvent(sEventData data)
{
	Logger::Log(LogLevel::kTrace, kEventHandler, kAddEvent,
		std::string("in: type=") + std::string(String((int)data.type).c_str())
	);
	event_queue_.push_back(data);
}

sEventData EventHandler::GetEvent()
{
	if (event_queue_.empty())
	{
		return sEventData{ EventType::kNone, nullptr };
	}
	sEventData data = event_queue_.front();
	event_queue_.pop_front();
	return data;
}