#pragma once

#include <string>

struct AWSSettings
{
	std::string client_id;
	std::string endpoint;
	std::string port;
	std::string root_ca;
	std::string device_certificate;
	std::string private_key;
};