#pragma once

#include <cstdint>

// SDカードを使用すると左ボタンが押されっぱなしの判定になってしまうため、
// 解決方法が見つかるまで左ボタンは使用しない方針で実装を進める。
class ButtonInputWatcher
{
public:
	ButtonInputWatcher();
	~ButtonInputWatcher();

public:
	void SetUpButtonInterruption();

private:
	bool middle_button_pressed_;
	bool right_button_pressed_;
};

void OnMiddleButtonPressed();
void OnRightButtonPressed();