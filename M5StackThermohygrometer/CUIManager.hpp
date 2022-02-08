#pragma once

#include "UIManagerBase.hpp"

class CUIManager : public UIManagerBase
{
public:
	CUIManager();
	~CUIManager();

public:
	void Initialize() override;
	void HandleEvent(EventData* event_data) override;
};