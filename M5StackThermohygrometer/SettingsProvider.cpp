#include "SettingsProvider.hpp"

#include <map>
#include <stdexcept>
#include <string>

#include "ConsoleLogger.hpp"
#include "JsonHandler.hpp"
#include "LogConstants.hpp"
#include "SDCardConstants.hpp"
#include "SDCardController.hpp"

AWSCommunicationSettings* SettingsProvider::Of()
{
    return ReadAWSCommunicationSettings();
}

AWSCommunicationSettings* SettingsProvider::ReadAWSCommunicationSettings()
{
    WiFiSettings* wifi_settings = ReadWiFiSettings();
    AWSSettings* aws_settings = ReadAWSSettings();
    ConsoleLogger::Log(new LogData(LogLevel::kInfo, kSettingsProvider, kReadAWSSettings, "success"));
    return new AWSCommunicationSettings(wifi_settings, aws_settings);
}

WiFiSettings* SettingsProvider::ReadWiFiSettings()
{
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kSettingsProvider, kReadWiFiSettings, "in"));
    try
    {
        std::string raw_wifi_settings = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kWiFiSettingsFileName);
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

AWSSettings* SettingsProvider::ReadAWSSettings()
{
    ConsoleLogger::Log(new LogData(LogLevel::kTrace, kSettingsProvider, kReadAWSSettings, "in"));
    try
    {
        std::string raw_aws_settings = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + kAwsSettingsFileName);
        AWSSettings* aws_settings = AWSSettings::FromString(raw_aws_settings);
        ConsoleLogger::Log(new LogData(LogLevel::kInfo, kSettingsProvider, kReadAWSSettings, "success"));
        return aws_settings;
    }
    catch (std::invalid_argument e)
    {
        ConsoleLogger::Log(new LogData(LogLevel::kError, kSettingsProvider, kReadAWSSettings, e.what()));
    }

    return nullptr;
}
