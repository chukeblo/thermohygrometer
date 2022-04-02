#include "ViewController.hpp"

#include <M5Stack.h>
#include "ConsoleLogger.hpp"
#include "LogConstants.hpp"

static const int kLatestDisplaySize = 3;
static const int kListDisplaySize = 2;
static const int kMaxDisplayNums = 5;

ViewController::ViewController()
{
    state_ = ViewState::GetInstance(ViewType::kLatestResultView);
    result_manager_ = MeasurementResultManager::GetInstance();
}

ViewController::~ViewController()
{
    delete state_;
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
        state_->DoMiddleButtonAction(this);
        break;
    case ButtonType::kLeftButton:
        state_->DoLeftButtonAction(this);
        break;
    default:
        break;
    }
}

void ViewController::OnMeasureEnvData()
{
    state_->OnMeasureEnvData(this);
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
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kViewController, kScrollUp, "in"));
    current_cursor_--;
}

void ViewController::ScrollDown()
{
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kViewController, kScrollDown, "in"));
    current_cursor_++;
}

void ViewController::DisplayLatestResult()
{
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kViewController, kDisplayLatestResult, "in"));
    MeasurementResult* latest_result = result_manager_->GetResults().back();
    ConsoleLogger::Log(new LogData(LogLevel::kDebug, kViewController, kDisplayLatestResult,
        "result: time=" + latest_result->time + 
        ",temperature=" + std::string(String(latest_result->thermohygro_data->temperature).c_str()) +
        ",humidity=" + std::string(String(latest_result->thermohygro_data->humidity).c_str())
    ));
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextSize(kLatestDisplaySize);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println(latest_result->time.c_str());
    M5.Lcd.println(latest_result->thermohygro_data->temperature);
    M5.Lcd.println(latest_result->thermohygro_data->humidity);
}

void ViewController::DisplayResultList()
{
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kViewController, kDisplayResultList, "in"));
    std::list<MeasurementResult*> results = result_manager_->GetResults();
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kViewController, kDisplayResultList, "get result list"));
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextSize(kListDisplaySize);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(0, 0);
    auto itr = results.begin();
    int dest = results.size();
    int start = dest < kMaxDisplayNums ? 0 : dest - kMaxDisplayNums;
    for (int i = 0; i < start; i++) itr++;
    for (int i = start; i < dest; i++)
    {
        MeasurementResult* result = *itr;
        M5.Lcd.printf("[%s] %5.2f %5.2f\n", result->time.c_str(), result->thermohygro_data->temperature, result->thermohygro_data->humidity);
        itr++;
    }
}