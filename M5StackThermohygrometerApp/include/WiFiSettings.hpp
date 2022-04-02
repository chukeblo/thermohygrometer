#pragma once

#include <string>

class WiFiSettings
{
public:
	WiFiSettings(std::string ssid, std::string password);

public:
	static WiFiSettings* FromString(std::string json);

public:
	std::string ssid;
	std::string password;
};