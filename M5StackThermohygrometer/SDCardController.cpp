#include "SDCardController.hpp"

#include <M5Stack.h>
#include <SD.h>
#include <stdexcept>
#include "JsonHandler.hpp"

sNetworkSettings SDCardController::ReadNetworkSettings()
{
    File file = SD.open("/network_settings.json");
    if (!file)
    {
        throw std::invalid_argument("file not found");
    }
    uint32_t file_size = file.size();
    char raw_data[1000];
    memset(raw_data, 0, sizeof(raw_data));
    for (int i = 0; i < file_size; i++)
    {
        file.seek(i);
        raw_data[i] = file.read();
    }
    sNetworkSettings settings;
    try
    {
        std::map<std::string, std::string> parseResult = JsonHandler::Parse(raw_data);
        settings.ssid = parseResult["ssid"];
        settings.password = parseResult["password"];
    }
    catch (std::invalid_argument e)
    {
        Serial.println(e.what());
    }

    file.close();

    return settings;
}
