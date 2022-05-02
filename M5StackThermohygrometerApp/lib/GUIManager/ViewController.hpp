#pragma once

#include <ButtonType.hpp>
#include <GUIManager.hpp>
#include <MeasurementResultManager.hpp>
#include <ViewState.hpp>

class ViewController
{
public:
    class GUIEventListenerImpl : public GUIManager::GUIEventListener
    {
    public:
        GUIEventListenerImpl(ViewController* view_controller);
        ~GUIEventListenerImpl() override;
    
    public:
        void OnButtonPressed(ButtonType type) override;
        void OnMeasureEnvData() override;

    private:
        ViewController* view_controller_;
    };

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
    ViewController::GUIEventListenerImpl* GetGUIEventListener();

private:
    void OnButtonPressed(ButtonType type);
    void OnMeasureEnvData();
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