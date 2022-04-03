#pragma once

#include <ViewState.hpp>

class ResultListViewState : public ViewState
{
public:
    ResultListViewState();
    ~ResultListViewState() override;

public:
    void Initialize(GUIContext* context) override;
    void Finalize(GUIContext* context) override;
    void OnMeasureEnvData(GUIContext* context) override;
    void DoRightButtonAction(GUIContext* context) override;
    void DoMiddleButtonAction(GUIContext* context) override;
    void DoLeftButtonAction(GUIContext* context) override;
};