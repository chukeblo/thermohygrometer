#include <ViewState.hpp>

#include <LatestResultViewState.hpp>
#include <ResultListViewState.hpp>

ViewState::ViewControlDelegate::ViewControlDelegate()
{
}

ViewState::ViewControlDelegate::~ViewControlDelegate()
{
}

ViewState* ViewState::GetInstance(ViewType type, ViewControlDelegate* delegate)
{
	switch (type)
	{
	case ViewType::kLatestResultView:
		return new LatestResultViewState(delegate);
	case ViewType::kResultListView:
		return new ResultListViewState(delegate);
	default:
		return nullptr;
	}
}

ViewState::ViewState(ViewControlDelegate* delegate)
{
	view_control_delegate_ = delegate;
}

ViewState::~ViewState()
{
}