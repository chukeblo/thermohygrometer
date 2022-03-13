#pragma once

#include "ViewState.hpp"

class ResultListViewState : public ViewState
{
public:
    void Initialize(GUIContext* context) override;
    void Finalize(GUIContext* context) override;
    void OnMeasureEnvData(GUIContext* context, MeasurementResult* result) override;
    void DoRightButtonAction(GUIContext* context) override;
    void DoMiddleButtonAction(GUIContext* context) override;
    void DoLeftButtonAction(GUIContext* context) override;
};