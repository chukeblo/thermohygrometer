#pragma once

#include "EventType.hpp"

class EventData
{
public:
    EventData(EventType type, void* data)
    {
        this->type = type;
        this->data = data;
    }

    EventType type;
    void* data;
};