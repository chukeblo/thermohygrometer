#pragma once

#include <string>

class AWSSettings
{
public:
	AWSSettings(std::string endpoint, std::string port, std::string root_ca, std::string device_certificate, std::string private_key)
	{
		this->endpoint = endpoint;
		this->port = port;
		this->root_ca = root_ca;
		this->device_certificate = device_certificate;
		this->private_key = private_key;
	}

	std::string endpoint;
	std::string port;
	std::string root_ca;
	std::string device_certificate;
	std::string private_key;
};