#pragma once

#include "EventType.hpp"

typedef struct EventData {
    EventType type;
    void* data;

    EventData(EventType event_type, void* event_data)
    {
        type = event_type;
        data = event_data;
    }
} sEventData;