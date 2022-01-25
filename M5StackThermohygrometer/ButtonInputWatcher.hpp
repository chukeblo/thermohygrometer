#pragma once

#include "ButtonType.hpp"

// SDカードを使用すると左ボタンが押されっぱなしの判定になってしまうため、
// 解決方法が見つかるまで左ボタンは使用しないこととする。
class ButtonInputWatcher
{
public:
	static ButtonInputWatcher* GetInstance();
	void SetUpButtonInterruption();
	void OnButtonPressed(ButtonType type);

private:
	ButtonInputWatcher();
	~ButtonInputWatcher();

	// bool left_button_pressed_;
	bool middle_button_pressed_;
	bool right_button_pressed_;
};

// void OnLeftButtonPressed();
void OnMiddleButtonPressed();
void OnRightButtonPressed();