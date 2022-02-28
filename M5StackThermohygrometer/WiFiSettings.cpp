#include "WiFiSettings.hpp"

#include <map>

#include "JsonHandler.hpp"

const std::string kSsidKey = "ssid";
const std::string kPasswordKey = "password";

WiFiSettings::WiFiSettings(std::string ssid, std::string password)
{
    this->ssid = ssid;
    this->password = password;
}

WiFiSettings* WiFiSettings::FromString(std::string json) {
    std::map<std::string, std::string> wifi_settings_map = JsonHandler::Parse(json);
    std::string ssid = wifi_settings_map[kSsidKey];
    std::string password = wifi_settings_map[kPasswordKey];
    return new WiFiSettings(ssid, password);
}