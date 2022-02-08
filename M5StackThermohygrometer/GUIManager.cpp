#include "GUIManager.hpp"

GUIManager::GUIManager()
{
	Initialize();
}

GUIManager::~GUIManager()
{
}

void GUIManager::Initialize()
{
    button_input_watcher_ = new ButtonInputWatcher();
	button_input_watcher_->SetUpButtonInterruption();
}

void GUIManager::HandleEvent(EventData* event_data)
{
    switch (event_data->type)
    {
        case EventType::kMiddleButtonPressed:
            break;
        case EventType::kRightButtonPressed:
            break;
        default:
            break;
    }
}
