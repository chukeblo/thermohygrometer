#pragma once

#include <string>

typedef struct AWSConfig
{
	std::string clientId;
	std::string endpoint;
	std::string rootCa;
	std::string deviceCert;
	std::string privateKey;
} sAWSConfig;