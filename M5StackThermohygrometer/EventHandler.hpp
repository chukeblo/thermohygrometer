#pragma once

#include <list>

#include "CommunicationClient.hpp"
#include "EventType.hpp"
#include "GUIManager.hpp"
#include "UIManagerBase.hpp"

class EventHandler
{
public:
	static EventHandler* GetInstance();

private:
	EventHandler();
	~EventHandler();

public:
	void Initialize();
	void SetCommunicationClient(CommunicationClient* communication_client);
	void EventHandle();
	void AddEvent(EventType type);

private:
	EventType GetEvent();

private:
	std::list<EventType> event_queue_;
	CommunicationClient* communication_client_;
	UIManagerBase* cui_manager_;
};
