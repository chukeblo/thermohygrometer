#include "EventHandler.hpp"

#include <M5Stack.h>
#include "LogConstants.hpp"
#include "LogData.hpp"


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
  thermohygrometer_controller_ = new ThermohygrometerController();
  gui_manager_ = UIManagerBase::GetInstance(UIManagerType::kGuiManagerType);
  cui_manager_ = UIManagerBase::GetInstance(UIManagerType::kCuiManagerType);
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
			break;
		case EventType::kMiddleButtonPressed:
		case EventType::kRightButtonPressed:
			gui_manager_->HandleEvent(data);
			break;
		case EventType::kMeasurementRequested:
			thermohygrometer_controller_->MeasureThermohygroData();
			break;
		case EventType::kLogDataGenerated:
			cui_manager_->HandleEvent(data);
			break;
		default:
			LogData* log_data = new LogData(LogLevel::kError, kEventHandle, kEventHandle, "not supported event type");
			AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
			break;
		}
		if (data->context)
		{
			delete data->context;
			data->context = nullptr;
		}
		delete data;
		data = nullptr;
	}
}

void EventHandler::AddEvent(EventData* data)
{
	LogData* log_data = new LogData(LogLevel::kTrace, kEventHandler, kAddEvent,
		std::string("in: type=") + std::string(String((int)data->type).c_str())
	);
	event_queue_.push_back(new EventData(EventType::kLogDataGenerated, (void*)log_data));
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
