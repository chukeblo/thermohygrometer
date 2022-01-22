#include <M5Stack.h>
#include <WiFi.h>
#include "NetworkController.hpp"

char *ssid = "hoge";
char *password = "fuga";
NetworkController *network_controller = new NetworkController(ssid, password);

void setup()
{
    M5.begin();
    M5.Lcd.setTextSize(2);

    bool result = network_controller->Prepare();
    M5.Lcd.printf("NetworkController::Prepare() result = %d\n", result);
}

void loop()
{
    struct tm tm;
    if (getLocalTime(&tm))
    {
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(60, 80);
        M5.Lcd.printf("%d/%2d/%2d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        M5.Lcd.setCursor(80, 140);
        M5.Lcd.printf("%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    delay(1000);
}
