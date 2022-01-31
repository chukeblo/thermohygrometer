#pragma once

#include <string>
#include "AWSConfig.hpp"
#include "NetworkSettings.hpp"

class SDCardController
{
private:
	static const int kMaxReadSize = 2048;

public:
	static sNetworkSettings ReadNetworkSettings();
	static sAWSConfig ReadAWSConfig();

private:
	static std::string ReadFileFromSDCard(std::string fileName);
};