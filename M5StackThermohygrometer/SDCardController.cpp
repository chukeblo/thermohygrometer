#include "SDCardController.hpp"

#include <M5Stack.h>
#include <SD.h>
#include <stdexcept>
#include "JsonHandler.hpp"

static const int kMaxReadSize = 2048;

sNetworkSettings SDCardController::ReadNetworkSettings()
{
	sNetworkSettings settings;
	try
	{
		std::string raw_text = ReadFileFromSDCard("/network_settings.json");
		std::map<std::string, std::string> parseResult = JsonHandler::Parse(raw_text);
		settings.ssid = parseResult["ssid"];
		settings.password = parseResult["password"];
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
		std::string raw_text = ReadFileFromSDCard("/aws_docs/aws_config.json");
		std::map<std::string, std::string> parse_result = JsonHandler::Parse(raw_text);
		config.clientId = parse_result["clientId"];
		config.endpoint = parse_result["endpoint"];
		config.rootCa = ReadFileFromSDCard("/aws_docs/AmazonRootCAxxxx.pem");
		config.deviceCert = ReadFileFromSDCard("/aws_docs/xxxx-certificate.pem.crt");
		config.privateKey = ReadFileFromSDCard("/aws_docs/xxxx-private.pem.key");
	}
	catch (std::invalid_argument e)
	{
		Serial.println(e.what());
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
