#pragma once

#include <string>

#include "AWSCommunicationSettings.hpp"

class SettingsProvider
{
public:
    static AWSCommunicationSettings* Of();
private:
	static AWSCommunicationSettings* ReadAWSCommunicationSettings();
    static WiFiSettings* ReadWiFiSettings();
	static AWSSettings* ReadAWSSettings();
};