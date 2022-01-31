#pragma once

#include "EventType.hpp"

typedef struct EventData {
    EventType type;
    void* data;
} sEventData;