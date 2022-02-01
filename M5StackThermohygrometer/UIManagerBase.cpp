#include "UIManagerBase.hpp"

#include "CUIManager.hpp"
#include "GUIManager.hpp"

UIManagerBase* UIManagerBase::GetInstance(uint8_t ui_type)
{
	static UIManagerBase* gui_manager = nullptr;
	static UIManagerBase* cui_manager = nullptr;

	if (ui_type & kCuiBit)
	{
		if (!cui_manager)
		{
			cui_manager = new CUIManager();
		}
		return cui_manager;
	}
	if (ui_type & kGuiBit)
	{
		if (!gui_manager)
		{
			gui_manager = new GUIManager();
		}
		return gui_manager;
	}
	return nullptr;
}

UIManagerBase::UIManagerBase()
{
}

UIManagerBase::~UIManagerBase()
{
}

