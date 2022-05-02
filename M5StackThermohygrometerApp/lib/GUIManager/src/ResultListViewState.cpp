#include <ResultListViewState.hpp>

#include <ConsoleLogger.hpp>
#include <LogConstants.hpp>

ResultListViewState::ResultListViewState(ViewControlDelegate* delegate) : ViewState(delegate)
{
}

ResultListViewState::~ResultListViewState()
{
}

void ResultListViewState::Initialize()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kInitialize, "in"));
	view_control_delegate_->DisplayResultList();
}

void ResultListViewState::Finalize()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kFinalize, "in"));
}

void ResultListViewState::OnMeasureEnvData()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kOnMeasureEnvData, "in"));
	view_control_delegate_->DisplayResultList();
}

void ResultListViewState::DoRightButtonAction()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kDoRightButtonAction, "in"));
	view_control_delegate_->CursorDown();
	view_control_delegate_->DisplayResultList();
}

void ResultListViewState::DoMiddleButtonAction()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kDoMiddleButtonAction, "in"));
	view_control_delegate_->ChangeState(ViewType::kLatestResultView);
}

void ResultListViewState::DoLeftButtonAction()
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kDoLeftButtonAction, "in"));
	view_control_delegate_->CursorUp();
	view_control_delegate_->DisplayResultList();
}
