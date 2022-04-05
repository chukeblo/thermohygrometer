#pragma once

#include <GUIContext.hpp>
#include <ViewType.hpp>

class ViewState
{
public:
    class ViewControlDelegate
    {
    public:
        ViewControlDelegate();
        virtual ~ViewControlDelegate();

    public:
        virtual void CursorUp() = 0;
        virtual void CursorDown() = 0;
        virtual void DisplayLatestResult() = 0;
        virtual void DisplayResultList() = 0;
    };

public:
    static ViewState* GetInstance(ViewType type, ViewControlDelegate* delegate);

public:
    ViewState(ViewControlDelegate* delegate);
    virtual ~ViewState();

public:
    virtual void Initialize(GUIContext* context) = 0;
    virtual void Finalize(GUIContext* context) = 0;
    virtual void OnMeasureEnvData(GUIContext* context) = 0;
    virtual void DoRightButtonAction(GUIContext* context) = 0;
    virtual void DoMiddleButtonAction(GUIContext* context) = 0;
    virtual void DoLeftButtonAction(GUIContext* context) = 0;

protected:
    ViewControlDelegate* view_control_delegate_;
};