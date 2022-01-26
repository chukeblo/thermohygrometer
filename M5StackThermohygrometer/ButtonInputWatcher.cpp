#include "ButtonInputWatcher.hpp"

#include <M5Stack.h>
#include "EventHandler.hpp"

static const uint8_t kMiddleButtonPin = 38;
static const uint8_t kRightButtonPin = 37;

ButtonInputWatcher::ButtonInputWatcher()
{
	middle_button_pressed_ = false;
	right_button_pressed_ = false;
}

ButtonInputWatcher::~ButtonInputWatcher()
{
}

ButtonInputWatcher* ButtonInputWatcher::GetInstance()
{
	static ButtonInputWatcher* instance = nullptr;
	if (!instance)
	{
		instance = new ButtonInputWatcher();
	}
	return instance;
}

void ButtonInputWatcher::SetUpButtonInterruption()
{
	pinMode(kMiddleButtonPin, INPUT);
	pinMode(kRightButtonPin, INPUT);

	attachInterrupt(kMiddleButtonPin, OnMiddleButtonPressed, FALLING);
	attachInterrupt(kRightButtonPin, OnRightButtonPressed, FALLING);
}

void ButtonInputWatcher::OnButtonPressed(ButtonType type)
{
	switch (type)
	{
	case ButtonType::kMiddleButton:
		if (!middle_button_pressed_) {
			middle_button_pressed_ = true;
			EventHandler::GetInstance()->AddEvent(EventType::kMiddleButtonPressed);
			Serial.println("Middle Button Pressed.");
			middle_button_pressed_ = false;
		}
		break;
	case ButtonType::kRightButton:
		if (!right_button_pressed_) {
			right_button_pressed_ = true;
			EventHandler::GetInstance()->AddEvent(EventType::kRightButtonPressed);
			Serial.println("Right Button Pressed.");
			right_button_pressed_ = false;
		}
		break;
	default:
		break;
	}
}

void OnMiddleButtonPressed()
{
	ButtonInputWatcher::GetInstance()->OnButtonPressed(ButtonType::kMiddleButton);
}

void OnRightButtonPressed()
{
	ButtonInputWatcher::GetInstance()->OnButtonPressed(ButtonType::kRightButton);
}