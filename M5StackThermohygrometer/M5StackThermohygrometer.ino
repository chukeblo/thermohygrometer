#include <M5Stack.h>
#include <WiFi.h>
#include "EventHandler.hpp"
#include "GUIManager.hpp"

EventHandler* event_handler = EventHandler::GetInstance();
GUIManager* gui_manager = new GUIManager();

void setup()
{
    M5.begin();
    Wire.begin();

    event_handler->Initialize();
}

void loop()
{
    event_handler->EventHandle();
    gui_manager->CheckIfButtonsPressed();
    delay(10);
}
