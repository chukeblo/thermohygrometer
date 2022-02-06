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
	Logger::Log(Logger::kTraceBit, kButtonInputWatcher, kSetUpButtonInterruption, "in");
	pinMode(kMiddleButtonPin, INPUT);
	pinMode(kRightButtonPin, INPUT);

	attachInterrupt(kMiddleButtonPin, OnMiddleButtonPressed, FALLING);
	attachInterrupt(kRightButtonPin, OnRightButtonPressed, FALLING);
	Logger::Log(Logger::kTraceBit, kButtonInputWatcher, kSetUpButtonInterruption, "out");
}

void ButtonInputWatcher::OnButtonPressed(uint8_t button_type)
{
	Logger::Log(Logger::kTraceBit, kButtonInputWatcher, kOnButtonPressed,
		std::string("in: type=") + std::string(String(button_type).c_str())
	);

	if (button_type & kMiddleButtonBit > 0)
	{
		if (!middle_button_pressed_) {
			middle_button_pressed_ = true;
			EventHandler::GetInstance()->AddEvent(EventData{ EventType::kMiddleButtonPressed, nullptr });
			middle_button_pressed_ = false;
		}
	}
	else if (button_type & kRightButtonBit > 0) {
		if (!right_button_pressed_) {
			right_button_pressed_ = true;
			EventHandler::GetInstance()->AddEvent(EventData{ EventType::kRightButtonPressed, nullptr });
			right_button_pressed_ = false;
		}
	}
	
	Logger::Log(Logger::kTraceBit, kButtonInputWatcher, kOnButtonPressed,
		std::string("out: type=") + std::string(String(button_type).c_str())
	);
}

void OnMiddleButtonPressed()
{
	ButtonInputWatcher::GetInstance()->OnButtonPressed(ButtonInputWatcher::kMiddleButtonBit);
}

void OnRightButtonPressed()
{
	ButtonInputWatcher::GetInstance()->OnButtonPressed(ButtonInputWatcher::kRightButtonBit);
}
