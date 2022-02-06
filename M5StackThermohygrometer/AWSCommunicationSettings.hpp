#pragma once

#include "AWSSettings.hpp"
#include "WiFiSettings.hpp"

struct AWSCommunicationSettings : CommunicationSettingsBase
{
    WiFiSettings wifi_settings;
    AWSSettings aws_settings;
};