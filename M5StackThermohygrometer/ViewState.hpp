#pragma once

#include "GUIContext.hpp"
#include "ViewType.hpp"

class ViewState
{
public:
    static ViewState* GetInstance(ViewType type);

private:
    ViewState() {}
    virtual ~ViewState() {}

public:
    virtual void Initialize(GUIContext* context) = 0;
    virtual void Finalize(GUIContext* context) = 0;
    virtual void OnMeasureEnvData(GUIContext* context, MeasurementResult* result) = 0;
    virtual void DoRightButtonAction(GUIContext* context) = 0;
    virtual void DoMiddleButtonAction(GUIContext* context) = 0;
    virtual void DoLeftButtonAction(GUIContext* context) = 0;
};