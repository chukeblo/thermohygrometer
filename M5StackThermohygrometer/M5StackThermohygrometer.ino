#include <M5Stack.h>
#include <WiFi.h>
#include "EventHandler.hpp"

void setup()
{
    M5.begin();
    Wire.begin();
}

void loop()
{
    EventHandler::GetInstance()->EventHandle();
    delay(10);
}
