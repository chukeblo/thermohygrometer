#include "SDCardController.hpp"

#include <M5Stack.h>
#include <SD.h>
#include <stdexcept>
#include "JsonHandler.hpp"
#include "SDCardConstants.hpp"

static const int kMaxReadSize = 2048;

sNetworkSettings SDCardController::ReadNetworkSettings()
{
	sNetworkSettings settings;
	try
	{
		std::string raw_text = ReadFileFromSDCard(kSDCardRootPath + kNetworkSettingsFileName);
		std::map<std::string, std::string> parseResult = JsonHandler::Parse(raw_text);
		settings.ssid = parseResult[kSsidKey];
		settings.password = parseResult[kPasswordKey];
	}
	catch (std::invalid_argument e)
	{
		Serial.println(e.what());
	}
	return settings;
}

sAWSConfig SDCardController::ReadAWSConfig()
{
	sAWSConfig config;
	try
	{
		std::string raw_text = ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + kAwsConfigFileName);
		std::map<std::string, std::string> parse_result = JsonHandler::Parse(raw_text);
		config.clientId = parse_result[kClientIdKey];
		config.endpoint = parse_result[kEndpointKey];
		config.rootCa = ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + kAWSRootCAFileName);
		config.deviceCert = ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + kDeviceCertFileName);
		config.privateKey = ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + kPrivateKeyFileName);
	}
	catch (std::invalid_argument e)
	{
		Serial.println(e.what());
	}
	Serial.printf("SDCardController::ReadAWSConfig() clientId = %s\n", config.clientId.c_str());
	Serial.printf("SDCardController::ReadAWSConfig() endpoint = %s\n", config.endpoint.c_str());
	Serial.printf("SDCardController::ReadAWSConfig() rootCa = \n%s\n", config.rootCa.c_str());
	Serial.printf("SDCardController::ReadAWSConfig() deviceCert = \n%s\n", config.deviceCert.c_str());
	Serial.printf("SDCardController::ReadAWSConfig() privateKey = \n%s\n", config.privateKey.c_str());
	return config;
}

std::string SDCardController::ReadFileFromSDCard(std::string fileName)
{
	File file = SD.open(fileName.c_str());
	if (!file)
	{
		throw std::invalid_argument("file not found: " + fileName);
	}
	uint32_t file_size = file.size();
	if (file_size > kMaxReadSize)
	{
		throw std::invalid_argument("too large file size: " + fileName);
	}
	char content[kMaxReadSize] = {};
	for (int i = 0; i < file_size; i++)
	{
		content[i] = file.read();
	}
	file.close();
	return std::string(content);
}
