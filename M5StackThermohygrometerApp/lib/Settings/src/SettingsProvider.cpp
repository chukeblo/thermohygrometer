#include "SettingsProvider.hpp"

#include <map>
#include <stdexcept>
#include <string>

#include <ConsoleLogger.hpp>
#include <JsonHandler.hpp>
#include <LogConstants.hpp>
#include <SDCardConstants.hpp>

AWSCommunicationSettings* SettingsProvider::Of(SDCardController* sd_card_controller)
{
    return ReadAWSCommunicationSettings(sd_card_controller);
}

AWSCommunicationSettings* SettingsProvider::ReadAWSCommunicationSettings(SDCardController* sd_card_controller)
{
    WiFiSettings* wifi_settings = ReadWiFiSettings(sd_card_controller);
    AWSSettings* aws_settings = ReadAWSSettings(sd_card_controller);
    ConsoleLogger::Log(new LogData(LogLevel::kInfo, kSettingsProvider, kReadAWSSettings, "success"));
    return new AWSCommunicationSettings(wifi_settings, aws_settings);
}

WiFiSettings* SettingsProvider::ReadWiFiSettings(SDCardController* sd_card_controller)
{
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kSettingsProvider, kReadWiFiSettings, "in"));
    try
    {
        std::string raw_wifi_settings = sd_card_controller->ReadFileFromSDCard(kSDCardRootPath + kWiFiSettingsFileName);
        WiFiSettings* wifi_settings = WiFiSettings::FromString(raw_wifi_settings);
        ConsoleLogger::Log(new LogData(LogLevel::kDebug, kSettingsProvider, kReadWiFiSettings, "success"));
        return wifi_settings;
    }
    catch (std::invalid_argument e)
    {
        ConsoleLogger::Log(new LogData(LogLevel::kError, kSettingsProvider, kReadWiFiSettings, e.what()));
    }
    return nullptr;
}

AWSSettings* SettingsProvider::ReadAWSSettings(SDCardController* sd_card_controller)
{
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kSettingsProvider, kReadAWSSettings, "in"));
    try
    {
        std::string raw_aws_settings = sd_card_controller->ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + kAwsSettingsFileName);
        AWSSettings* aws_settings = AWSSettings::FromString(raw_aws_settings, sd_card_controller);
        ConsoleLogger::Log(new LogData(LogLevel::kInfo, kSettingsProvider, kReadAWSSettings, "success"));
        return aws_settings;
    }
    catch (std::invalid_argument e)
    {
        ConsoleLogger::Log(new LogData(LogLevel::kError, kSettingsProvider, kReadAWSSettings, e.what()));
    }

    return nullptr;
}
