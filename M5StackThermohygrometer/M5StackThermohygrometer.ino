#include <M5Stack.h>
#include <WiFi.h>
#include "ButtonInputWatcher.hpp"
#include "EventHandler.hpp"
#include "SDCardController.hpp"
#include "ThermohygrometerController.hpp"
#include "UIManagerBase.hpp"

void setup()
{
    M5.begin();
    M5.Lcd.setTextSize(2);
    Wire.begin();

    ThermohygrometerController* controller = new ThermohygrometerController();

    UIManagerBase* gui_manager = UIManagerBase::GetInstance(UIManagerBase::kGuiBit);
}

void loop()
{
    EventHandler::GetInstance()->EventHandle();
    delay(10);
}
