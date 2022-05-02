#include <LatestResultViewState.hpp>

#include <ConsoleLogger.hpp>
#include <LogConstants.hpp>

LatestResultViewState::LatestResultViewState(ViewControlDelegate* delegate) : ViewState(delegate)
{
}

LatestResultViewState::~LatestResultViewState()
{
}

void LatestResultViewState::Initialize()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kInitialize, "in"));
	view_control_delegate_->DisplayLatestResult();
}

void LatestResultViewState::Finalize()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kFinalize, "in"));
}

void LatestResultViewState::OnMeasureEnvData()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kOnMeasureEnvData, "in"));
	view_control_delegate_->DisplayLatestResult();
}

void LatestResultViewState::DoRightButtonAction()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kDoRightButtonAction, "in"));
}

void LatestResultViewState::DoMiddleButtonAction()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kDoMiddleButtonAction, "in"));
	view_control_delegate_->ChangeState(ViewType::kResultListView);
}

void LatestResultViewState::DoLeftButtonAction()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kDoLeftButtonAction, "in"));
}
