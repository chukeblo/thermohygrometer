#pragma once

#include <GUIContext.hpp>

#include <MeasurementResultManager.hpp>
#include <ViewState.hpp>

class ViewController : public GUIContext
{
public:
    class ViewControlDelegateImpl : public ViewState::ViewControlDelegate
    {
    public:
        ViewControlDelegateImpl(ViewController* view_controller);
        ~ViewControlDelegateImpl();

    public:
        void CursorUp() override;
        void CursorDown() override;
        void DisplayLatestResult() override;
        void DisplayResultList() override;

    private:
        ViewController* view_controller_;
    };

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
    ViewControlDelegateImpl* view_control_delegate_;
    ViewState* state_;
    MeasurementResultManager* result_manager_;
    int current_cursor_;
    int current_start_index_;
    int current_end_index_;
};