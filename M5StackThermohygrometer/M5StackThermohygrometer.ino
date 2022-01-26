#include <M5Stack.h>
#include <WiFi.h>
#include <stdexcept>
#include "AWSConfig.hpp"
#include "ButtonInputWatcher.hpp"
#include "EnvironmentDataCollector.hpp"
#include "EventHandler.hpp"
#include "NetworkController.hpp"
#include "SDCardController.hpp"

void CreateTasks() {
    xTaskCreatePinnedToCore(StartDataCollectionTask, "DataCollectionTask", 4096, nullptr, 1, nullptr, 0);
}

void setup()
{
    M5.begin();
    M5.Lcd.setTextSize(2);
    Wire.begin();

    sNetworkSettings settings = SDCardController::ReadNetworkSettings();
    char* ssid = const_cast<char*>(settings.ssid.c_str());
    char* password = const_cast<char *>(settings.password.c_str());
    NetworkController* network_controller = new NetworkController(ssid, password);
    bool result = network_controller->Prepare();
    M5.Lcd.printf("NetworkController::Prepare() result = %d\n", result);

    sAWSConfig config = SDCardController::ReadAWSConfig();
    M5.Lcd.printf("clientId = %s\n", config.clientId.c_str());
    M5.Lcd.printf("endpoint = %s\n", config.endpoint.c_str());
    M5.Lcd.printf("rootCa = %s\n", config.rootCa.c_str());
    M5.Lcd.printf("deviceCert = %s\n", config.deviceCert.c_str());
    M5.Lcd.printf("privateKey = %s\n", config.privateKey.c_str());

    CreateTasks();

    ButtonInputWatcher::GetInstance()->SetUpButtonInterruption();
}

void loop()
{
    EventHandler::GetInstance()->EventHandle();
    delay(10);
}
