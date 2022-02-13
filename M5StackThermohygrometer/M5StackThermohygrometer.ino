#include <M5Stack.h>
#include <WiFi.h>
#include "EventHandler.hpp"
#include "ThermohygrometerController.hpp"
#include "UIManagerBase.hpp"

void setup()
{
    M5.begin();
    Wire.begin();

    ThermohygrometerController* controller = new ThermohygrometerController();

    UIManagerBase* gui_manager = UIManagerBase::GetInstance(UIManagerType::kGuiManagerType);
}

void loop()
{
    EventHandler::GetInstance()->EventHandle();
    delay(10);
}
