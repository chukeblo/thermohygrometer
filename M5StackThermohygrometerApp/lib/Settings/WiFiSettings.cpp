#include "WiFiSettings.hpp"

#include <map>

#include <JsonHandler.hpp>

const std::string kSsidKey = "ssid";
const std::string kPasswordKey = "password";

WiFiSettings::WiFiSettings(std::string ssid, std::string password)
{
    this->ssid = ssid;
    this->password = password;
}

WiFiSettings* WiFiSettings::FromString(std::string json) {
    std::map<std::string, JsonElement*> wifi_settings_map = JsonHandler::Parse(json);
    JsonStringElement* ssid_element = static_cast<JsonStringElement*>(wifi_settings_map[kSsidKey]);
    std::string ssid = ssid_element->data;
    JsonStringElement* password_element = static_cast<JsonStringElement*>(wifi_settings_map[kPasswordKey]);
    std::string password = password_element->data;
    return new WiFiSettings(ssid, password);
}