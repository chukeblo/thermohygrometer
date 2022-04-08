#pragma once

#include <ButtonType.hpp>
#include <MeasurementResultManager.hpp>
#include <ViewState.hpp>

class ViewController
{
public:
    class ViewControlDelegateImpl : public ViewState::ViewControlDelegate
    {
    public:
        ViewControlDelegateImpl(ViewController* view_controller);
        ~ViewControlDelegateImpl();

    public:
        void ChangeState(ViewType type) override;
        void CursorUp() override;
        void CursorDown() override;
        void DisplayLatestResult() override;
        void DisplayResultList() override;

    private:
        ViewController* view_controller_;
    };

public:
    ViewController();
    ~ViewController();

public:
    void OnButtonPressed(ButtonType type);
    void OnMeasureEnvData();

private:
    void ChangeState(ViewType type);
    void ScrollUp();
    void ScrollDown();
    void DisplayLatestResult();
    void DisplayResultList();

private:
    ViewControlDelegateImpl* view_control_delegate_;
    ViewState* state_;
    MeasurementResultManager* result_manager_;
    int current_cursor_;
    int current_start_index_;
    int current_end_index_;
};