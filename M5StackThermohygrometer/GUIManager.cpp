#include "GUIManager.hpp"

#include "EventHandler.hpp"

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
    gui_drawer_ = new GUIDrawer();
}

void GUIManager::HandleEvent(EventData* event_data)
{
    switch (event_data->type)
    {
        case EventType::kReadEnvData:
            gui_drawer_->DisplayMeasurementResult((MeasurementResult*)(event_data->context));
            break;
        case EventType::kMiddleButtonPressed:
            NotifyMeasurementRequest();
            break;
        case EventType::kRightButtonPressed:
            break;
        default:
            break;
    }
}

void GUIManager::NotifyMeasurementRequest()
{
    EventHandler::GetInstance()->AddEvent(new EventData(EventType::kMeasurementRequested, nullptr));
}
