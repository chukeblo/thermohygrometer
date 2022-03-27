#include "SettingsProvider.hpp"

#include <map>
#include <stdexcept>
#include <string>

#include "ConsoleLogger.hpp"
#include "JsonHandler.hpp"
#include "LogConstants.hpp"
#include "SDCardConstants.hpp"
#include "SDCardController.hpp"

ThermohygrometerSettings* SettingsProvider::Of()
{
    return ReadThermohygrometerSettings();
}

ThermohygrometerSettings* SettingsProvider::ReadThermohygrometerSettings()
{
    std::string raw_thermohygrometer_settings = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kThermohygrometerSettingsFilename);
    std::map<std::string, std::string> thermohygrometer_settings_map = JsonHandler::Parse(raw_thermohygrometer_settings);
    std::string communication_type = thermohygrometer_settings_map[kCommunicationTypeKey];
    if (communication_type != kAWSType)
    {
        ConsoleLogger::Log(new LogData(LogLevel::kError, kSettingsProvider, kReadThermohygrometerSettings, "not supported communication type"));
        return nullptr;
    }
    AWSCommunicationSettings* aws_communication_settings = ReadAWSCommunicationSettings(communication_type);
    return new ThermohygrometerSettings(communication_type, aws_communication_settings);
}

AWSCommunicationSettings* SettingsProvider::ReadAWSCommunicationSettings(std::string communication_type)
{
    AWSCommunicationSettings* aws_communication_settings = nullptr;
    if (communication_type == kAWSType)
    {
        WiFiSettings* wifi_settings = ReadWiFiSettings();
        AWSSettings* aws_settings = ReadAWSSettings();
        aws_communication_settings =  new AWSCommunicationSettings(wifi_settings, aws_settings);
    }
    return aws_communication_settings;
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
