#pragma once

#include <GUIContext.hpp>

#include <MeasurementResultManager.hpp>
#include <ViewState.hpp>

class ViewController : public GUIContext
{
public:
    ViewController();
    ~ViewController() override;

public:
    void OnButtonPressed(ButtonType type) override;
    void OnMeasureEnvData() override;
    void ChangeState(ViewType type) override;
    void ScrollUp() override;
    void ScrollDown() override;
    void DisplayLatestResult() override;
    void DisplayResultList() override;

private:
    ViewState* state_;
    MeasurementResultManager* result_manager_;
    int current_cursor_;
};