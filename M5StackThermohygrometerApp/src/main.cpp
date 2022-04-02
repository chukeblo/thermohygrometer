#include <M5Stack.h>
#include <WiFi.h>
#include "CommunicationClientImpl.hpp"
#include "GUIManager.hpp"
#include "TaskManager.hpp"
#include "ThermohygroDataMeasurer.hpp"
#include "ViewController.hpp"

GUIManager* gui_manager = new GUIManager(new ViewController());
TaskManager* task_manager = TaskManager::GetInstance();

void setup()
{
    M5.begin();
    Wire.begin();

    ThermohygroDataMeasurer* thermohygrodata_measurer = new ThermohygroDataMeasurer();
    thermohygrodata_measurer->SetMeasureEnvDataListener(gui_manager->GetMeasureEnvDataListener());
    thermohygrodata_measurer->SetCommunicationClient(new CommunicationClientImpl());
    task_manager->CreateTask(TaskManager::GetMeasureTaskToken(), (void*)thermohygrodata_measurer);
}

void loop()
{
    gui_manager->CheckIfButtonsPressed();
    delay(10);
}
