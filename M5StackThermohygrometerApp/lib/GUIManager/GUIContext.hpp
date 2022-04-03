#pragma once

#include <list>

#include <ButtonType.hpp>
#include <ViewType.hpp>

class GUIContext
{
public:
    GUIContext() {}
    virtual ~GUIContext() {}

public:
    virtual void OnButtonPressed(ButtonType type) = 0;
    virtual void OnMeasureEnvData() = 0;
    virtual void ChangeState(ViewType type) = 0;
    virtual void ScrollUp() = 0;
    virtual void ScrollDown() = 0;
    virtual void DisplayLatestResult() = 0;
    virtual void DisplayResultList() = 0;
};