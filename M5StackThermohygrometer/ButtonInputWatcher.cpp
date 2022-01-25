#include "ButtonInputWatcher.hpp"

#include <M5Stack.h>
#include "EventHandler.hpp"

static const uint8_t kLeftButtonPin = 39;
static const uint8_t kMiddleButtonPin = 38;
static const uint8_t kRightButtonPin = 37;

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
	pinMode(kLeftButtonPin, INPUT);
	pinMode(kMiddleButtonPin, INPUT);
	pinMode(kRightButtonPin, INPUT);

	attachInterrupt(kLeftButtonPin, OnLeftButtonPressed, FALLING);
	attachInterrupt(kMiddleButtonPin, OnMiddleButtonPressed, FALLING);
	attachInterrupt(kRightButtonPin, OnRightButtonPressed, FALLING);
}

void ButtonInputWatcher::OnButtonPressed(ButtonType type)
{
	bool isPressed = false;
	switch (type)
	{
	case ButtonType::kLeftButton:
		if (!left_button_pressed_) {
			left_button_pressed_ = true;
			EventHandler::GetInstance()->AddEvent(EventType::kLeftButtonPressed);
			left_button_pressed_ = false;
		}
		break;
	case ButtonType::kMiddleButton:
		if (!middle_button_pressed_) {
			middle_button_pressed_ = true;
			EventHandler::GetInstance()->AddEvent(EventType::kMiddleButtonPressed);
			middle_button_pressed_ = false;
		}
		break;
	case ButtonType::kRightButton:
		if (!right_button_pressed_) {
			right_button_pressed_ = true;
			EventHandler::GetInstance()->AddEvent(EventType::kRightButtonPressed);
			right_button_pressed_ = false;
		}
		break;
	default:
		break;
	}
}

void OnLeftButtonPressed()
{
	ButtonInputWatcher::GetInstance()->OnButtonPressed(ButtonType::kLeftButton);
}

void OnMiddleButtonPressed()
{
	ButtonInputWatcher::GetInstance()->OnButtonPressed(ButtonType::kMiddleButton);
}

void OnRightButtonPressed()
{
	ButtonInputWatcher::GetInstance()->OnButtonPressed(ButtonType::kRightButton);
}
