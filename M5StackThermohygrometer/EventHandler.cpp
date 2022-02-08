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
	EventData* data = GetEvent();
	if (!data)
	{
		return;
	}
	switch (data->type)
	{
	case EventType::kReadEnvData:
		break;
	case EventType::kMiddleButtonPressed:
		break;
	case EventType::kRightButtonPressed:
		break;
	default:
		Logger::Log(Logger::kErrorBit, kEventHandle, kEventHandle, "not supported event type");
		break;
	}
}

void EventHandler::AddEvent(EventData* data)
{
	Logger::Log(Logger::kTraceBit, kEventHandler, kAddEvent,
		std::string("in: type=") + std::string(String((int)data->type).c_str())
	);
	event_queue_.push_back(data);
}

EventData* EventHandler::GetEvent()
{
	if (event_queue_.empty())
	{
		return nullptr;
	}
	EventData* data = event_queue_.front();
	event_queue_.pop_front();
	return data;
}