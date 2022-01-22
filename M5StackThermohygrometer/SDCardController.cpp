#include "SDCardController.hpp"

#include <M5Stack.h>
#include <SD.h>

void SDCardController::ReadNetworkSettings()
{
    File file = SD.open("/network_settings.json");
    if (!file)
    {
        return;
    }
    uint32_t file_size = file.size();
    char raw_data[1000];
    memset(raw_data, 0, sizeof(raw_data));
    for (int i = 0; i < file_size; i++)
    {
        file.seek(i);
        raw_data[i] = file.read();
    }
    M5.Lcd.println(raw_data);

    file.close();
}