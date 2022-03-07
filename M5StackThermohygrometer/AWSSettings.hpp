#pragma once

#include <string>

class AWSSettings
{
public:
	AWSSettings(std::string client_id, std::string endpoint, std::string port, std::string root_ca, std::string device_certificate, std::string private_key, std::string topic);
	~AWSSettings();

public:
	static AWSSettings* FromString(std::string json);

public:
	std::string client_id;
	std::string endpoint;
	std::string port;
	std::string root_ca;
	std::string device_certificate;
	std::string private_key;
	std::string topic;
};