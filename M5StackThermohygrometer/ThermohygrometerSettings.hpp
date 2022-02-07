#pragma once

#include <string>

#include "CommunicationSettingsBase.hpp"

class ThermohygrometerSettings
{
public:
    ThermohygrometerSettings(std::string communication_type, CommunicationSettingsBase* communication_settings)
    {
        this->communication_type = communication_type;
        this->communication_settings = communication_settings;
    }

    std::string communication_type;
    CommunicationSettingsBase* communication_settings;
};