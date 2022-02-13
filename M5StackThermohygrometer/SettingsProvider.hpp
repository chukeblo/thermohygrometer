#pragma once

#include <string>

#include "ThermohygrometerSettings.hpp"

class SettingsProvider
{
public:
    static ThermohygrometerSettings* Of();
private:
    static ThermohygrometerSettings* ReadThermohygrometerSettings();
	static AWSCommunicationSettings* ReadAWSCommunicationSettings(std::string communication_type);
    static WiFiSettings* ReadWiFiSettings();
	static AWSSettings* ReadAWSSettings();
};