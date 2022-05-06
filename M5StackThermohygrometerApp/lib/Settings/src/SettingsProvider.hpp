#pragma once

#include <string>

#include <AWSCommunicationSettings.hpp>
#include <SDCardController.hpp>

class SettingsProvider
{
public:
    static AWSCommunicationSettings* Of(SDCardController* sd_card_controller);
private:
	static AWSCommunicationSettings* ReadAWSCommunicationSettings(SDCardController* sd_card_controller);
    static WiFiSettings* ReadWiFiSettings(SDCardController* sd_card_controller);
	static AWSSettings* ReadAWSSettings(SDCardController* sd_card_controller);
};