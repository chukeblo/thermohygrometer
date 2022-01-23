#include <M5Stack.h>
#include <WiFi.h>
#include "EnvironmentDataReader.hpp"
#include "NetworkController.hpp"
#include "SDCardController.hpp"

void setup()
{
    M5.begin();
    M5.Lcd.setTextSize(2);
    Wire.begin();

    sNetworkSettings settings = SDCardController::ReadNetworkSettings();
    char *ssid = const_cast<char *>(settings.ssid.c_str());
    char *password = const_cast<char *>(settings.password.c_str());
    NetworkController *network_controller = new NetworkController(ssid, password);
    bool result = network_controller->Prepare();
    M5.Lcd.printf("NetworkController::Prepare() result = %d\n", result);

    EnvironmentDataReader *reader = new EnvironmentDataReader();
    sThermohydroData data = reader->ReadThermohydroData();
    if (data.is_succeeded) {
        M5.Lcd.printf("Temp: %2.1f\nHumi: %2.0f%%\n", data.temperature, data.humidity);
    }
}

void loop()
{
}
