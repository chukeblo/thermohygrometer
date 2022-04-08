#pragma once

#include <ViewState.hpp>

class ResultListViewState : public ViewState
{
public:
    ResultListViewState(ViewControlDelegate* delegate);
    ~ResultListViewState() override;

public:
    void Initialize() override;
    void Finalize() override;
    void OnMeasureEnvData() override;
    void DoRightButtonAction() override;
    void DoMiddleButtonAction() override;
    void DoLeftButtonAction() override;
};