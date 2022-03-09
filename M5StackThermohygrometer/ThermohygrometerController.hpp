#pragma once

#include <string>

#include "CommunicationClient.hpp"
#include "ThermohygrometerSettings.hpp"

class ThermohygrometerController
{
public:
	ThermohygrometerController();
	~ThermohygrometerController();

public:
	void ConnectToMqttServer();

private:
	ThermohygrometerSettings* settings_;
	CommunicationClient* client_;
};
