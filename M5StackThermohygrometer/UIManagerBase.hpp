#pragma once

#include <cstdint>

#include "EventData.hpp"
#include "UIManagerType.hpp"

class UIManagerBase
{
public:
    static const uint8_t kCuiBit = 1;

public:
    static UIManagerBase* GetInstance(UIManagerType ui_type);

protected:
    UIManagerBase();
    virtual ~UIManagerBase();

public:
    virtual void Initialize() = 0;
    virtual void HandleEvent(EventData* event_data) = 0;
};
