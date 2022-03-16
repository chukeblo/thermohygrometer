#include "EventHandler.hpp"

#include <M5Stack.h>
#include "ConsoleLogger.hpp"
#include "LogConstants.hpp"

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

void EventHandler::SetCommunicationClient(CommunicationClient* communication_client)
{
	communication_client_ = communication_client;
}

void EventHandler::SetGUIManager(GUIManager* gui_manager)
{
	gui_manager_ = gui_manager;
}

void EventHandler::EventHandle()
{
	while (true)
	{
		EventData* data = GetEvent();
		if (!data)
		{
			return;
		}
		switch (data->type)
		{
		case EventType::kReadEnvData:
			gui_manager_->NotifyEnvDataMeasured();
			break;
		case EventType::kSendEnvDataRequested:
			communication_client_->SendThermohygroData(MeasurementResultManager::GetInstance()->GetResults().front());
			break;
		default:
			ConsoleLogger::Log(new LogData(LogLevel::kError, kEventHandle, kEventHandle, "not supported event type"));
			break;
		}
		delete data;
		data = nullptr;
	}
}

void EventHandler::AddEvent(EventData* data)
{
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kEventHandler, kAddEvent,
		"in: type=" + std::string(String((int)data->type).c_str())
	));
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
