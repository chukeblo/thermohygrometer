#pragma once

#include "GUIContext.hpp"

class ViewController : public GUIContext
{
public:
    ViewController();
    ~ViewControler() override;

public:
    void OnButtonPressed(ButtonType type) override;
    void OnMeasureEnvData(MeasurementResult* result) override;
    void ChangeState(ViewType type) override;
    void ScrollUp() override;
    void ScrollDown() override;
    void AddDisplayData(MeasurementResult* result) override;
    void DisplayMeasurementResult() override;

private:
    ViewState* state_;
    std::list<MeasurementResult*> results_;
    int current_cursor_;
};