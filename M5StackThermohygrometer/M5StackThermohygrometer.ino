#include <M5Stack.h>
#include <WiFi.h>
#include "NetworkController.hpp"
#include "SDCardController.hpp"

void setup()
{
    M5.begin();
    M5.Lcd.setTextSize(2);

    // bool result = network_controller->Prepare();
    // M5.Lcd.printf("NetworkController::Prepare() result = %d\n", result);

    SDCardController::ReadNetworkSettings();
}

void loop()
{
}
