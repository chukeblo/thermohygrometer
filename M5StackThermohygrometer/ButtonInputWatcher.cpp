#include "ButtonInputWatcher.hpp"

#include <M5Stack.h>
#include "EventHandler.hpp"
#include "LogConstants.hpp"
#include "Logger.hpp"

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
	Logger::Log(Logger::kTraceBit, kButtonInputWatcher, kSetUpButtonInterruption, "in");
	pinMode(kMiddleButtonPin, INPUT);
	pinMode(kRightButtonPin, INPUT);

	attachInterrupt(kMiddleButtonPin, OnMiddleButtonPressed, FALLING);
	attachInterrupt(kRightButtonPin, OnRightButtonPressed, FALLING);
	Logger::Log(Logger::kTraceBit, kButtonInputWatcher, kSetUpButtonInterruption, "out");
}

void OnMiddleButtonPressed()
{
	EventHandler::GetInstance()->AddEvent(new EventData(EventType::kMiddleButtonPressed, nullptr));
}

void OnRightButtonPressed()
{
	EventHandler::GetInstance()->AddEvent(new EventData(EventType::kRightButtonPressed, nullptr));
}
