#include "GUIManager.hpp"

#include <M5Stack.h>
#include "ConsoleLogger.hpp"
#include "EventHandler.hpp"
#include "LogConstants.hpp"

GUIManager::GUIManager()
{
	Initialize();
}

GUIManager::~GUIManager()
{
    delete button_input_watcher_;
    delete gui_drawer_;
}

void GUIManager::Initialize()
{
    button_input_watcher_ = new ButtonInputWatcher();
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

void GUIManager::CheckIfButtonsPressed()
{
    M5.update();
    if (BtnA.wasPressed())
    {
        ConsoleLogger::Log(new LogData(LogLevel::kInfo, kGUIManager, kCheckIfButtonsPressed, "left button has been pressed."));
    }
    else if (BtnB.wasPressed())
    {
        ConsoleLogger::Log(new LogData(LogLevel::kInfo, kGUIManager, kCheckIfButtonsPressed, "middle button has been pressed."));
    }
    else if (BtnC.wasPressed())
    {
        ConsoleLogger::Log(new LogData(LogLevel::kInfo, kGUIManager, kCheckIfButtonsPressed, "right button has been pressed."));
    }
}

void GUIManager::NotifyMeasurementRequest()
{
    EventHandler::GetInstance()->AddEvent(new EventData(EventType::kMeasurementRequested, nullptr));
}
