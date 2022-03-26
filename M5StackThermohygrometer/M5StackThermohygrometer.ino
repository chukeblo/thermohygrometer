#include <M5Stack.h>
#include <WiFi.h>
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
    event_handler->SetCommunicationClient(new CommunicationClient());

    ThermohygroDataMeasurer* thermohygrodata_measurer = new ThermohygroDataMeasurer();
    thermohygrodata_measurer->SetMeasureEnvDataListener(new GUIManager::MeasureEnvDataListenerImpl(gui_manager));
    task_manager->CreateTask(kMeasureTask, (void*)thermohygrodata_measurer);
}

void loop()
{
    event_handler->EventHandle();
    gui_manager->CheckIfButtonsPressed();
    delay(10);
}
