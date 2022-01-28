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
    NetworkController* network_controller = new NetworkController(settings.ssid.c_str(), settings.password.c_str());
    bool result = network_controller->Prepare();
    sAWSConfig config = SDCardController::ReadAWSConfig();

    CreateTasks();

    ButtonInputWatcher::GetInstance()->SetUpButtonInterruption();
}

void loop()
{
    EventHandler::GetInstance()->EventHandle();
    delay(10);
}
