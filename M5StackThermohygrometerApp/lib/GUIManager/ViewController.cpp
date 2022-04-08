#include <ViewController.hpp>

#include <M5Stack.h>
#include <ConsoleLogger.hpp>
#include <LogConstants.hpp>

static const int kLatestDisplaySize = 3;
static const int kListDisplaySize = 2;
static const int kMaxDisplayNums = 5;

ViewController::ViewControlDelegateImpl::ViewControlDelegateImpl(ViewController* view_controller)
{
    view_controller_ = view_controller;
}

ViewController::ViewControlDelegateImpl::~ViewControlDelegateImpl()
{
}

void ViewController::ViewControlDelegateImpl::ChangeState(ViewType type)
{
    view_controller_->ChangeState(type);
}

void ViewController::ViewControlDelegateImpl::CursorUp()
{
    view_controller_->ScrollUp();
}

void ViewController::ViewControlDelegateImpl::CursorDown()
{
    view_controller_->ScrollDown();
}

void ViewController::ViewControlDelegateImpl::DisplayLatestResult()
{
    view_controller_->DisplayLatestResult();
}

void ViewController::ViewControlDelegateImpl::DisplayResultList()
{
    view_controller_->DisplayResultList();
}

ViewController::ViewController()
{
    view_control_delegate_ = new ViewController::ViewControlDelegateImpl(this);
    state_ = ViewState::GetInstance(ViewType::kLatestResultView, view_control_delegate_);
    result_manager_ = MeasurementResultManager::GetInstance();
    current_cursor_ = 0;
    current_start_index_ = 0;
    current_end_index_ = 0;
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
        state_->DoRightButtonAction();
        break;
    case ButtonType::kMiddleButton:
        state_->DoMiddleButtonAction();
        break;
    case ButtonType::kLeftButton:
        state_->DoLeftButtonAction();
        break;
    default:
        break;
    }
}

void ViewController::OnMeasureEnvData()
{
    state_->OnMeasureEnvData();
}

void ViewController::ChangeState(ViewType type)
{
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kViewController, kChangeState,
        "type=" + std::string(String((int)type).c_str())
    ));
    state_->Finalize();
    delete state_;
    state_ = nullptr;

    // カーソル位置と表示データ範囲の初期化
    // 表示データ範囲の初期値は一番古いデータから5つないし最新データまで
    current_cursor_ = 0;
    current_start_index_ = 0;
    int size = result_manager_->GetResults().size();
    current_end_index_ = size < kMaxDisplayNums ? size : kMaxDisplayNums;

    state_ = ViewState::GetInstance(type, view_control_delegate_);
    state_->Initialize();
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kViewController, kChangeState, "out"));
}

void ViewController::ScrollUp()
{
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kViewController, kScrollUp, "in"));
    // カーソルがすでに一番古いデータを指している場合は何もしない
    if (current_cursor_ > 0) current_cursor_--;
}

void ViewController::ScrollDown()
{
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kViewController, kScrollDown, "in"));
    // カーソルがすでに最新データをさしている場合は何もしない
    if (current_cursor_ < result_manager_->GetResults().size() - 1) current_cursor_++;
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

    // 測定結果がない場合はここで終了
    if (results.empty()) return;

    // 表示データ範囲のアップデート
    auto itr = results.begin();
    int length = results.size();
    int start = 0;
    int end = 0;
    // カーソルが直前の表示データ範囲におさまっている場合
    if (current_start_index_ <= current_cursor_ && current_cursor_ < current_end_index_)
    {
        start = current_start_index_;
        end = (start + kMaxDisplayNums < length) ? start + kMaxDisplayNums : length;
    }
    else
    {
        // カーソルが直前の表示データ範囲よりも古いものを指している場合
        if (current_cursor_ < current_start_index_)
        {
            end = (current_cursor_ + kMaxDisplayNums < length) ? current_cursor_ + kMaxDisplayNums : length;
        }
        // カーソルが直前の表示データ範囲よりも新しいものをさしている場合
        else if (current_end_index_ <= current_cursor_)
        {
            end = current_cursor_ + 1;
        }
        start = (end - kMaxDisplayNums > 0) ? end - kMaxDisplayNums : 0;
    }

    // 表示データ範囲までスキップ
    for (int i = 0; i < start; i++) itr++;
    for (int i = start; i < end; i++)
    {
        // カーソル位置のデータは黄色で表示。それ以外は白色で表示。
        if (i == current_cursor_) M5.Lcd.setTextColor(YELLOW);
        MeasurementResult* result = *itr;
        M5.Lcd.printf("[%s] %5.2f %5.2f\n", result->time.c_str(), result->thermohygro_data->temperature, result->thermohygro_data->humidity);
        M5.Lcd.setTextColor(WHITE);
        itr++;
    }
    current_start_index_ = start;
    current_end_index_ = end;
}