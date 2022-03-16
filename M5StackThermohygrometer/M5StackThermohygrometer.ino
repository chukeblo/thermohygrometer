#include <M5Stack.h>
#include <WiFi.h>
#include "EventHandler.hpp"
#include "GUIManager.hpp"
#include "TaskManager.hpp"
#include "ThermohygroDataMeasurer.hpp"

const char* kMeasureTask = "MeasureTask";

EventHandler* event_handler = EventHandler::GetInstance();
GUIManager* gui_manager = new GUIManager();
TaskManager* task_manager = TaskManager::GetInstance();

void setup()
{
    M5.begin();
    Wire.begin();

    event_handler->Initialize();
    event_handler->SetCommunicationClient(CommunicationClient::GetInstance());
    event_handler->SetGUIManager(gui_manager);

    ThermohygroDataMeasurer* thermohygrodata_measurer = new ThermohygroDataMeasurer();
    task_manager->CreateTask(kMeasureTask, (void*)thermohygrodata_measurer);
}

void loop()
{
    event_handler->EventHandle();
    gui_manager->CheckIfButtonsPressed();
    delay(10);
}
