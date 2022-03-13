#include "LatestResultViewState.hpp"

#include "ConsoleLogger.hpp"
#include "LogConstants.hpp"

LatestResultViewState::LatestResultViewState()
{
}

LatestResultViewState::~LatestResultViewState()
{
}

void LatestResultViewState::Initialize(GUIContext* context)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kInitialize, "in"));
	context->DisplayMeasurementResult();
}

void LatestResultViewState::Finalize(GUIContext* context)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kFinalize, "in"));
}

void LatestResultViewState::OnMeasureEnvData(GUIContext* context, MeasurementResult* result)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kOnMeasureEnvData, "in"));
	context->AddDisplayData(result);
	context->DisplayMeasurementResult();
}

void LatestResultViewState::DoRightButtonAction(GUIContext* context)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kDoRightButtonAction, "in"));
}

void LatestResultViewState::DoMiddleButtonAction(GUIContext* context)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kDoMiddleButtonAction, "in"));
	context->ChangeState(ViewType::kResultListView);
}

void LatestResultViewState::DoLeftButtonAction(GUIContext* context)
{
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kLatestResultViewState, kDoLeftButtonAction, "in"));
}
