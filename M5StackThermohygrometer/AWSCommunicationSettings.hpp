#pragma once

#include "AWSSettings.hpp"
#include "WiFiSettings.hpp"

class AWSCommunicationSettings : public CommunicationSettingsBase
{
public:
    AWSCommunicationSettings(WiFiSettings* wifi_settings, AWSSettings* aws_settings)
    {
        this->wifi_settings = wifi_settings;
        this->aws_settings = aws_settings;
    }
    virtual ~AWSCommunicationSettings(){}

    WiFiSettings* wifi_settings;
    AWSSettings* aws_settings;
};