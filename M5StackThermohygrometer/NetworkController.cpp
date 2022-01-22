#include "NetworkController.hpp"

#include <M5Stack.h>
#include <WiFi.h>

#define JST (3600L * 9)

NetworkController::NetworkController(char *ssid, char *password) : ssid_(ssid), password_(password), is_connected_(false)
{
}

NetworkController::~NetworkController()
{
}

bool NetworkController::Prepare()
{
    WiFi.begin(ssid_, password_);
    bool result = false;
    result = Connect();
    M5.Lcd.printf("network connect result = %d\n", result);
    result = SyncronizeTime();
    M5.Lcd.printf("time sync result = %d\n", result);
    return result;
}

bool NetworkController::Connect()
{
    uint8_t status;
    while (true)
    {
        status = WiFi.status();
        if (status == WL_CONNECTED)
        {
            M5.Lcd.printf("\nWiFi connected.\nssid=%s\npassword=%s\n", ssid_, password_);
            M5.Lcd.println(WiFi.localIP());
            return true;
        }
        else if (status == WL_CONNECT_FAILED)
        {
            M5.Lcd.println("\nFailed in WiFi connection");
            return false;
        }
        else
        {
            M5.Lcd.print(".");
        }
        delay(500);
    }
}

bool NetworkController::SyncronizeTime()
{
    if (!is_connected_) {
        return false;
    }
    configTime(JST, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
}