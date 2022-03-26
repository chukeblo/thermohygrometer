#include <M5Stack.h>
#include <WiFi.h>
#include "CommunicationClientImpl.hpp"
#include "EventHandler.hpp"
#include "GUIManager.hpp"
#include "TaskManager.hpp"
#include "ThermohygroDataMeasurer.hpp"
#include "ViewController.hpp"

const char* kMeasureTask = "MeasureTask";

EventHandler* event_handler = EventHandler::GetInstance();
GUIManager* gui_manager = new GUIManager(new ViewController());
TaskManager* task_manager = TaskManager::GetInstance();

void setup()
{
    M5.begin();
    Wire.begin();

    event_handler->Initialize();

    ThermohygroDataMeasurer* thermohygrodata_measurer = new ThermohygroDataMeasurer();
    thermohygrodata_measurer->SetMeasureEnvDataListener(new GUIManager::MeasureEnvDataListenerImpl(gui_manager));
    thermohygrodata_measurer->SetCommunicationClient(new CommunicationClientImpl());
    task_manager->CreateTask(kMeasureTask, (void*)thermohygrodata_measurer);
}

void loop()
{
    event_handler->EventHandle();
    gui_manager->CheckIfButtonsPressed();
    delay(10);
}
