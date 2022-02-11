#pragma once

#include "UIManagerBase.hpp"

#include "ConsoleLogger.hpp"

class CUIManager : public UIManagerBase
{
public:
	CUIManager();
	~CUIManager();

public:
	void Initialize() override;
	void HandleEvent(EventData* event_data) override;

private:
	ConsoleLogger* console_logger_;
};