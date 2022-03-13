#include "ViewController.hpp"

#include "ConsoleLogger.hpp"
#include "LogConstants.hpp"

ViewController::ViewController()
{
    state_ = ViewState::GetInstance(ViewType::kLatestResultView);
}

ViewController::~ViewControler()
{
    state_ = nullptr;
}

void ViewController::OnButtonPressed(ButtonType type)
{
    switch (type)
    {
    case ButtonType::kRightButton:
        state_->DoRightButtonAction(this);
        break;
    case ButtonType::kMiddleButton:
        state->DoMiddleButtonAction(this);
        break;
    case ButtonType::kLeftButton:
        state->DoLeftButtonAction(this);
        break;
    default:
        break;
    }
}

void ViewController::OnMeasureEnvData(MeasurementResult* result)
{
    state_->OnMeasureEnvData(this, result)
}

void ViewController::ChangeState(ViewType type)
{
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kViewController, kChangeState,
        "type=" + std::string(String((int)type).c_str())
    ));
    state_->Finalize(this);
    delete state_;
    state_ = nullptr;
    state_ = ViewState::GetInstance(type);
    state_->Initialize(this);
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kViewController, kChangeState, "out"));
}

void ViewController::ScrollUp()
{
    current_cursor_--;
}

void ViewController::ScrollDown()
{
    current_cursor_++;
}

void ViewController::AddDisplayData(MeasurementResult* result)
{
    results_.push_front(MeasurementResult::CopyWith(result));
}

void ViewController::DisplayMeasurementResult()
{
}
