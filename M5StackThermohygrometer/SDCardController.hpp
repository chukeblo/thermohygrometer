#pragma once

#include <string>
#include "AWSConfig.hpp"
#include "NetworkSettings.hpp"

class SDCardController
{
public:
	static sNetworkSettings ReadNetworkSettings();
	static sAWSConfig ReadAWSConfig();

private:
	static std::string ReadFileFromSDCard(std::string fileName);
};