#include <M5Stack.h>
#include <WiFi.h>
#include "NetworkController.hpp"
#include "SDCardController.hpp"

void setup()
{
    M5.begin();
    M5.Lcd.setTextSize(2);

    sNetworkSettings settings = SDCardController::ReadNetworkSettings();
    char *ssid = const_cast<char *>(settings.ssid.c_str());
    char *password = const_cast<char *>(settings.password.c_str());
    NetworkController *network_controller = new NetworkController(ssid, password);
    bool result = network_controller->Prepare();
    M5.Lcd.printf("NetworkController::Prepare() result = %d\n", result);
}

void loop()
{
}
