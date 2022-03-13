#include "ResultListViewState.hpp"

#include "ConsoleLogger.hpp"
#include "LogConstants.hpp"

ResultListViewState::ResultListViewState()
{
}

ResultListViewState::~ResultListViewState()
{
}

void ResultListViewState::Initialize(GUIContext* context)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kInitialize, "in"));
}

void ResultListViewState::Finalize(GUIContext* context)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kFinalize, "in"));
}

void ResultListViewState::OnMeasureEnvData(GUIContext* context, MeasurementResult* result)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kOnMeasureEnvData, "in"));
	context->AddDisplayData(result);
}

void ResultListViewState::DoRightButtonAction(GUIContext* context)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kDoRightButtonAction, "in"));
	context->ScrollDown();
}

void ResultListViewState::DoMiddleButtonAction(GUIContext* context)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kDoMiddleButtonAction, "in"));
	context->ChangeState(ViewType::kLatestResultView);
}

void ResultListViewState::DoLeftButtonAction(GUIContext* context)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kResultListViewState, kDoLeftButtonAction, "in"));
}
