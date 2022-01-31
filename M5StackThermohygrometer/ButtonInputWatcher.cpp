#include "ButtonInputWatcher.hpp"

#include <M5Stack.h>
#include "EventHandler.hpp"
#include "LogConstants.hpp"
#include "Logger.hpp"

ButtonInputWatcher* ButtonInputWatcher::GetInstance()
{
	static ButtonInputWatcher* instance = nullptr;
	if (!instance)
	{
		instance = new ButtonInputWatcher();
	}
	return instance;
}

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
	Logger::Log(LogLevel::kTrace, kButtonInputWatcher, kSetUpButtonInterruption, "in");
	pinMode(kMiddleButtonPin, INPUT);
	pinMode(kRightButtonPin, INPUT);

	attachInterrupt(kMiddleButtonPin, OnMiddleButtonPressed, FALLING);
	attachInterrupt(kRightButtonPin, OnRightButtonPressed, FALLING);
	Logger::Log(LogLevel::kTrace, kButtonInputWatcher, kSetUpButtonInterruption, "out");
}

void ButtonInputWatcher::OnButtonPressed(ButtonType type)
{
	Logger::Log(LogLevel::kTrace, kButtonInputWatcher, kOnButtonPressed,
		std::string("in: type=") + std::string(String((int)type).c_str())
	);
	switch (type)
	{
	case ButtonType::kMiddleButton:
		if (!middle_button_pressed_) {
			middle_button_pressed_ = true;
			EventHandler::GetInstance()->AddEvent(sEventData{ EventType::kMiddleButtonPressed, nullptr });
			middle_button_pressed_ = false;
		}
		break;
	case ButtonType::kRightButton:
		if (!right_button_pressed_) {
			right_button_pressed_ = true;
			EventHandler::GetInstance()->AddEvent(sEventData{ EventType::kRightButtonPressed, nullptr });
			right_button_pressed_ = false;
		}
		break;
	default:
		Logger::Log(LogLevel::kError, kButtonInputWatcher, kOnButtonPressed, "not supported button type");
		break;
	}
	Logger::Log(LogLevel::kTrace, kButtonInputWatcher, kOnButtonPressed,
		std::string("out: type=") + std::string(String((int)type).c_str())
	);
}

void OnMiddleButtonPressed()
{
	ButtonInputWatcher::GetInstance()->OnButtonPressed(ButtonType::kMiddleButton);
}

void OnRightButtonPressed()
{
	ButtonInputWatcher::GetInstance()->OnButtonPressed(ButtonType::kRightButton);
}
