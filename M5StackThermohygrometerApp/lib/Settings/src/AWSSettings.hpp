#pragma once

#include <string>

#include <SDCardController.hpp>

class AWSSettings
{
public:
	AWSSettings(std::string client_id, std::string endpoint, int port, std::string root_ca, std::string device_certificate, std::string private_key, std::string topic);
	~AWSSettings();

public:
	static AWSSettings* FromString(std::string json, SDCardController* sd_card_controller);

public:
	std::string client_id;
	std::string endpoint;
	int port;
	std::string root_ca;
	std::string device_certificate;
	std::string private_key;
	std::string topic;
};