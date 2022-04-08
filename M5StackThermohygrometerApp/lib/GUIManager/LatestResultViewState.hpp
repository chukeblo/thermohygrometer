#pragma once

#include <ViewState.hpp>

class LatestResultViewState : public ViewState
{
public:
    LatestResultViewState(ViewControlDelegate* delegate);
    ~LatestResultViewState() override;

public:
    void Initialize() override;
    void Finalize() override;
    void OnMeasureEnvData() override;
    void DoRightButtonAction() override;
    void DoMiddleButtonAction() override;
    void DoLeftButtonAction() override;
};