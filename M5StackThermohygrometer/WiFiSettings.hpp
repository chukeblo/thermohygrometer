#pragma once

#include <string>

class WiFiSettings
{
public:
	WiFiSettings(std::string ssid, std::string password)
	{
		this->ssid = ssid;
		this->password = password;
	}

	std::string ssid;
	std::string password;
};