#pragma once

#include <AWSSettings.hpp>
#include <WiFiSettings.hpp>

class AWSCommunicationSettings
{
public:
    AWSCommunicationSettings(WiFiSettings* wifi_settings, AWSSettings* aws_settings)
    {
        this->wifi_settings = wifi_settings;
        this->aws_settings = aws_settings;
    }
    ~AWSCommunicationSettings()
    {
        delete this->wifi_settings;
        delete this->aws_settings;
    }

    WiFiSettings* wifi_settings;
    AWSSettings* aws_settings;
};