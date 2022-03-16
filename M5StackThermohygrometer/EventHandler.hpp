#pragma once

#include <list>

#include "CommunicationClient.hpp"
#include "EventData.hpp"
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
	void SetGUIManager(GUIManager* gui_manager);
	void EventHandle();
	void AddEvent(EventData* data);

private:
	EventData* GetEvent();

private:
	std::list<EventData*> event_queue_;
	CommunicationClient* communication_client_;
	GUIManager* gui_manager_;
	UIManagerBase* cui_manager_;
};
