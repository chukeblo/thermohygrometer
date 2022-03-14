#include <M5Stack.h>
#include <WiFi.h>
#include "EventHandler.hpp"
#include "GUIManager.hpp"

GUIManager* gui_manager = new GUIManager();

void setup()
{
    M5.begin();
    Wire.begin();

    EventHandler::GetInstance()->Initialize();
}

void loop()
{
    EventHandler::GetInstance()->EventHandle();
    gui_manager->CheckIfButtonsPressed();
    delay(10);
}
