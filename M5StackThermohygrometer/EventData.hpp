#pragma once

#include "EventType.hpp"

class EventData
{
public:
    EventData(EventType type, void* context)
    {
        this->type = type;
        this->context = context;
    }

    EventType type;
    void* context;
};