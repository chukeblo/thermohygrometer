#include "SettingsProvider.hpp"

#include <map>
#include <stdexcept>
#include <string>

#include "EventHandler.hpp"
#include "JsonHandler.hpp"
#include "LogConstants.hpp"
#include "LogData.hpp"
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
        LogData* log_data = new LogData(LogLevel::kError, kSettingsProvider, kReadThermohygrometerSettings, "not supported communication type");
        EventHandler::GetInstance()->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
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
    LogData* log_data = new LogData(LogLevel::kTrace, kSettingsProvider, kReadWiFiSettings, "in");
    EventHandler* event_handler = EventHandler::GetInstance();
    event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
    try
    {
        std::string raw_wifi_settings = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kWiFiSettingsFileName);
        WiFiSettings* wifi_settings = WiFiSettings::FromString(raw_wifi_settings);
        log_data = new LogData(LogLevel::kDebug, kSettingsProvider, kReadWiFiSettings,
            std::string("ssid=") + wifi_settings->ssid + std::string(",password=") + wifi_settings->password
        );
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
        return wifi_settings;
    }
    catch (std::invalid_argument e)
    {
        log_data = new LogData(LogLevel::kError, kSettingsProvider, kReadWiFiSettings, e.what());
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
    }
    return nullptr;
}

AWSSettings* SettingsProvider::ReadAWSSettings()
{
    LogData* log_data = new LogData(LogLevel::kTrace, kSettingsProvider, kReadAWSSettings, "in");
    EventHandler* event_handler = EventHandler::GetInstance();
    event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
    try
    {
        std::string raw_aws_settings = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + kAwsSettingsFileName);
        AWSSettings* aws_settings = AWSSettings::FromString(raw_aws_settings);
        log_data = new LogData(LogLevel::kDebug, kSettingsProvider, kReadAWSSettings,
            std::string(",endpoint=") + aws_settings->endpoint + std::string(",port=") + aws_settings->port
        );
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
        log_data = new LogData(LogLevel::kDebug, kSettingsProvider, kReadAWSSettings,
            std::string("rootCA = ") + aws_settings->root_ca
        );
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
        log_data = new LogData(LogLevel::kDebug, kSettingsProvider, kReadAWSSettings,
            std::string("deviceCert = ") + aws_settings->device_certificate
        );
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
        log_data = new LogData(LogLevel::kDebug, kSettingsProvider, kReadAWSSettings,
            std::string("privateKey = ") + aws_settings->private_key
        );
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
        return aws_settings;
    }
    catch (std::invalid_argument e)
    {
        log_data = new LogData(LogLevel::kError, kSettingsProvider, kReadAWSSettings, e.what());
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
    }

    return nullptr;
}
