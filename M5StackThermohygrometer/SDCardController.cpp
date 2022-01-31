#include "SDCardController.hpp"

#include <stdexcept>

#include <M5Stack.h>
#include <SD.h>
#include "JsonHandler.hpp"
#include "LogConstants.hpp"
#include "Logger.hpp"
#include "SDCardConstants.hpp"

sNetworkSettings SDCardController::ReadNetworkSettings()
{
	Logger::Log(LogLevel::kTrace, kSDCardController, kReadNetworkSettings, "in");
	sNetworkSettings settings;
	try
	{
		std::string raw_text = ReadFileFromSDCard(kSDCardRootPath + kNetworkSettingsFileName);
		std::map<std::string, std::string> parseResult = JsonHandler::Parse(raw_text);
		settings.ssid = parseResult[kSsidKey];
		settings.password = parseResult[kPasswordKey];
		Logger::Log(LogLevel::kDebug, kSDCardController, kReadNetworkSettings,
			std::string("ssid=") + settings.ssid + std::string(",password=") + settings.password
		);
	}
	catch (std::invalid_argument e)
	{
		Logger::Log(LogLevel::kError, kSDCardController, kReadNetworkSettings, e.what());
	}
	return settings;
}

sAWSConfig SDCardController::ReadAWSConfig()
{
	Logger::Log(LogLevel::kTrace, kSDCardController, kReadAWSConfig, "in");
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
		Logger::Log(LogLevel::kDebug, kSDCardController, kReadAWSConfig,
			std::string("clientId=") + config.clientId + std::string(",endpoint=") + config.endpoint
		);
		Logger::Log(LogLevel::kDebug, kSDCardController, kReadAWSConfig,
			std::string("rootCA = ") + config.rootCa
		);
		Logger::Log(LogLevel::kDebug, kSDCardController, kReadAWSConfig,
			std::string("deviceCert = ") + config.deviceCert
		);
		Logger::Log(LogLevel::kDebug, kSDCardController, kReadAWSConfig,
			std::string("privateKey = ") + config.privateKey
		);
	}
	catch (std::invalid_argument e)
	{
		Logger::Log(LogLevel::kError, kSDCardController, kReadAWSConfig, e.what());
	}
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
