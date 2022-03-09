#include "ButtonInputWatcher.hpp"

#include <M5Stack.h>
#include "ConsoleLogger.hpp"
#include "EventHandler.hpp"
#include "LogConstants.hpp"

const uint8_t kMiddleButtonPin = 38;
const uint8_t kRightButtonPin = 37;

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
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kButtonInputWatcher, kSetUpButtonInterruption, "in"));
	pinMode(kMiddleButtonPin, INPUT);
	pinMode(kRightButtonPin, INPUT);

	attachInterrupt(kMiddleButtonPin, OnMiddleButtonPressed, FALLING);
	attachInterrupt(kRightButtonPin, OnRightButtonPressed, FALLING);
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kButtonInputWatcher, kSetUpButtonInterruption, "out"));
}

void OnMiddleButtonPressed()
{
	EventHandler::GetInstance()->AddEvent(new EventData(EventType::kMiddleButtonPressed, nullptr));
}

void OnRightButtonPressed()
{
	EventHandler::GetInstance()->AddEvent(new EventData(EventType::kRightButtonPressed, nullptr));
}
