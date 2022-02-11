#include "ButtonInputWatcher.hpp"

#include <M5Stack.h>
#include "EventHandler.hpp"
#include "LogConstants.hpp"
#include "LogData.hpp"

ButtonInputWatcher::ButtonInputWatcher()
{
	middle_button_pressed_ = false;
	right_button_pressed_ = false;
}

ButtonInputWatcher::~ButtonInputWatcher()
{
}

void ButtonInputWatcher::SetUpButtonInterruption()
{
	LogData* log_data = new LogData(LogLevel::kTrace, kButtonInputWatcher, kSetUpButtonInterruption, "in");
	EventHandler* event_handler = EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	pinMode(kMiddleButtonPin, INPUT);
	pinMode(kRightButtonPin, INPUT);

	attachInterrupt(kMiddleButtonPin, OnMiddleButtonPressed, FALLING);
	attachInterrupt(kRightButtonPin, OnRightButtonPressed, FALLING);
	log_data = new LogData(LogLevel::kTrace, kButtonInputWatcher, kSetUpButtonInterruption, "out");
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
}

void OnMiddleButtonPressed()
{
	EventHandler::GetInstance()->AddEvent(new EventData(EventType::kMiddleButtonPressed, nullptr));
}

void OnRightButtonPressed()
{
	EventHandler::GetInstance()->AddEvent(new EventData(EventType::kRightButtonPressed, nullptr));
}
