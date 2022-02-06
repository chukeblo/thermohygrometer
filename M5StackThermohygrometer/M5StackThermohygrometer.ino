#include <M5Stack.h>
#include <WiFi.h>
#include "AWSConfig.hpp"
#include "ButtonInputWatcher.hpp"
#include "ThermohygrometerController.hpp"
#include "EventHandler.hpp"
#include "NetworkController.hpp"
#include "SDCardController.hpp"

void setup()
{
    M5.begin();
    M5.Lcd.setTextSize(2);
    Wire.begin();

    NetworkSettings settings = SDCardController::ReadNetworkSettings();
    AWSConfig config = SDCardController::ReadAWSConfig();
    NetworkController* network_controller = new NetworkController(settings.ssid.c_str(), settings.password.c_str());
    network_controller->Prepare();

    ButtonInputWatcher::GetInstance()->SetUpButtonInterruption();
}

void loop()
{
    EventHandler::GetInstance()->EventHandle();
    delay(10);
}
