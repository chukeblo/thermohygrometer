#pragma once

#include <queue>
#include "EventType.hpp"

class EventHandler
{
public:
    static EventHandler *GetInstance();
    void EventHandle();
    void AddEvent(EventType type);

private:
    EventHandler();
    ~EventHandler();
    EventType GetEvent();

    std::queue<EventType> event_queue_;
};
