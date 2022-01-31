#include "UIManagerBase.hpp"

#include "CUIManager.hpp"
#include "GUIManager.hpp"

UIManagerBase* UIManagerBase::GetInstance(UIType type)
{
	static UIManagerBase* gui_manager = nullptr;
	static UIManagerBase* cui_manager = nullptr;

	switch (type)
	{
	case UIType::kCUI:
		if (!cui_manager)
		{
			cui_manager = new CUIManager();
		}
		return cui_manager;
	case UIType::kGUI:
		if (!gui_manager)
		{
			gui_manager = new GUIManager();
		}
		return gui_manager;
	default:
		return nullptr;
	}
}

UIManagerBase::UIManagerBase()
{
}

UIManagerBase::~UIManagerBase()
{
}

