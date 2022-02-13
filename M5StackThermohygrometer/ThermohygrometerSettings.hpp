#pragma once

#include <string>

#include "AWSCommunicationSettings.hpp"

class ThermohygrometerSettings
{
public:
    ThermohygrometerSettings(std::string communication_type, AWSCommunicationSettings* aws_communication_settings)
    {
        this->communication_type = communication_type;
        this->aws_communication_settings = aws_communication_settings;
    }

    std::string communication_type;
    AWSCommunicationSettings* aws_communication_settings;
};