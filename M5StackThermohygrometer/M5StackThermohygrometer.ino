#include <M5Stack.h>
#include <WiFi.h>
#include "ButtonInputWatcher.hpp"
#include "EventHandler.hpp"
#include "SDCardController.hpp"
#include "ThermohygrometerController.hpp"

void setup()
{
    M5.begin();
    M5.Lcd.setTextSize(2);
    Wire.begin();

    ThermohygrometerController* controller = new ThermohygrometerController();

    ButtonInputWatcher::GetInstance()->SetUpButtonInterruption();
}

void loop()
{
    EventHandler::GetInstance()->EventHandle();
    delay(10);
}
