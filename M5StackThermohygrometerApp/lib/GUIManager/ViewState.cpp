#include <ViewState.hpp>

#include <LatestResultViewState.hpp>
#include <ResultListViewState.hpp>

ViewState* ViewState::GetInstance(ViewType type)
{
	switch (type)
	{
	case ViewType::kLatestResultView:
		return new LatestResultViewState();
	case ViewType::kResultListView:
		return new ResultListViewState();
	default:
		return nullptr;
	}
}
