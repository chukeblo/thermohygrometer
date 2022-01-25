#pragma once

#include "ButtonType.hpp"

class ButtonInputWatcher
{
public:
	static ButtonInputWatcher* GetInstance();
	void SetUpButtonInterruption();
	void OnButtonPressed(ButtonType type);

private:
	ButtonInputWatcher();
	~ButtonInputWatcher();

	bool left_button_pressed_;
	bool middle_button_pressed_;
	bool right_button_pressed_;
};

void OnLeftButtonPressed();
void OnMiddleButtonPressed();
void OnRightButtonPressed();