#pragma once

#include <string>

#include "AWSSettings.hpp"
#include "CommunicationSettingsBase.hpp"
#include "ThermohygrometerSettings.hpp"
#include "WiFiSettings.hpp"

class SettingsProvider
{
public:
    static ThermohygrometerSettings* Of();
private:
    static ThermohygrometerSettings* ReadThermohygrometerSettings();
	static CommunicationSettingsBase* ReadCommunicationSettings(std::string communication_type);
    static WiFiSettings* ReadWiFiSettings();
	static AWSSettings* ReadAWSSettings();
};