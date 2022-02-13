#pragma once

#include <cstdint>

#include "EventData.hpp"
#include "UIManagerType.hpp"

class UIManagerBase
{
public:
    static const uint8_t kCuiBit = 1;
    static const uint8_t kGuiBit = 2;

public:
    static UIManagerBase* GetInstance(UIManagerType ui_type);

public:
    UIManagerBase();
    virtual ~UIManagerBase();

public:
    virtual void Initialize() = 0;
    virtual void HandleEvent(EventData* event_data) = 0;
};
