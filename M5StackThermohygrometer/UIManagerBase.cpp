#include "UIManagerBase.hpp"

#include "CUIManager.hpp"
#include "GUIManager.hpp"

UIManagerBase* UIManagerBase::GetInstance(UIManagerType ui_type)
{
	static UIManagerBase* gui_manager = nullptr;
	static UIManagerBase* cui_manager = nullptr;

	switch (ui_type)
	{
	case UIManagerType::kCuiManagerType:
		if (!cui_manager)
		{
			cui_manager = new CUIManager();
		}
		return cui_manager;
	case UIManagerType::kGuiManagerType:
		if (!gui_manager)
		{
			gui_manager = new GUIManager();
		}
		return gui_manager;
	default:
		nullptr;
	}
}

UIManagerBase::UIManagerBase()
{
}

UIManagerBase::~UIManagerBase()
{
}

