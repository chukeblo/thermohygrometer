#pragma once

#include "ButtonType.hpp"
#include <cstdint>

// SDカードを使用すると左ボタンが押されっぱなしの判定になってしまうため、
// 解決方法が見つかるまで左ボタンは使用しない方針で実装を進める。
class ButtonInputWatcher
{
private:
	const uint8_t kMiddleButtonPin = 38;
	const uint8_t kRightButtonPin = 37;

public:
	static ButtonInputWatcher* GetInstance();

private:
	ButtonInputWatcher();
	~ButtonInputWatcher();

public:
	void SetUpButtonInterruption();
	void OnButtonPressed(ButtonType type);

private:
	bool middle_button_pressed_;
	bool right_button_pressed_;
};

void OnMiddleButtonPressed();
void OnRightButtonPressed();