#pragma once

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
        virtual void ChangeState(ViewType type) = 0;
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
    virtual void Initialize() = 0;
    virtual void Finalize() = 0;
    virtual void OnMeasureEnvData() = 0;
    virtual void DoRightButtonAction() = 0;
    virtual void DoMiddleButtonAction() = 0;
    virtual void DoLeftButtonAction() = 0;

protected:
    ViewControlDelegate* view_control_delegate_;
};