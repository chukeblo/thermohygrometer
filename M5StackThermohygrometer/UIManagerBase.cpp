#include "UIManagerBase.hpp"

#include "CUIManager.hpp"

UIManagerBase* UIManagerBase::GetInstance(UIManagerType ui_type)
{
	static UIManagerBase* cui_manager = nullptr;

	switch (ui_type)
	{
	case UIManagerType::kCuiManagerType:
		if (!cui_manager)
		{
			cui_manager = new CUIManager();
		}
		return cui_manager;
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

