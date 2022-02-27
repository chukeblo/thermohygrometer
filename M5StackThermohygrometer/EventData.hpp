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
    ~EventData() {
        if (this->context != nullptr) {
            delete this->context;
        }
    }

public:
    EventType type;
    void* context;
};