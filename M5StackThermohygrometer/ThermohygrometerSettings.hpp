#pragma once

#include <string>

#include "CommunicationSettingsBase.hpp"

struct ThermohygrometerSettings
{
    std::string communication_type;
    CommunicationSettingsBase communication_settings;
};