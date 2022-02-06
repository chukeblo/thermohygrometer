#pragma once

#include <string>

struct AWSConfig
{
	std::string clientId;
	std::string endpoint;
	std::string rootCa;
	std::string deviceCert;
	std::string privateKey;
};