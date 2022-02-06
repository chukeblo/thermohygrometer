#pragma once

#include "EventType.hpp"

struct EventData {
    EventType type;
    void* data;
};