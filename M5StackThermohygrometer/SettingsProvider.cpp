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
    std::string ssid = "";
    std::string password = "";
    try
    {
        std::string raw_wifi_settings = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kWiFiSettingsFileName);
        std::map<std::string, std::string> wifi_settings_map = JsonHandler::Parse(raw_wifi_settings);
        ssid = wifi_settings_map[kSsidKey];
        password = wifi_settings_map[kPasswordKey];
        log_data = new LogData(LogLevel::kDebug, kSettingsProvider, kReadWiFiSettings,
            std::string("ssid=") + ssid + std::string(",password=") + password
        );
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
    }
    catch (std::invalid_argument e)
    {
        log_data = new LogData(LogLevel::kError, kSettingsProvider, kReadWiFiSettings, e.what());
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
        return nullptr;
    }
    return new WiFiSettings(ssid, password);
}

AWSSettings* SettingsProvider::ReadAWSSettings()
{
    LogData* log_data = new LogData(LogLevel::kTrace, kSettingsProvider, kReadAWSSettings, "in");
    EventHandler* event_handler = EventHandler::GetInstance();
    event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
    std::string client_id = "";
    std::string endpoint = "";
    std::string port = "";
    std::string root_ca = "";
    std::string device_certificate = "";
    std::string private_key = "";
    try
    {
        std::string raw_aws_settings = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + kAwsSettingsFileName);
        std::map<std::string, std::string> aws_settings_map = JsonHandler::Parse(raw_aws_settings);
        client_id = aws_settings_map[kClientIdKey];
        endpoint = aws_settings_map[kEndpointKey];
        port = aws_settings_map[kPortKey];
        root_ca = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + kAWSRootCAFileName);
        device_certificate = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + kDeviceCertFileName);
        private_key = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + kPrivateKeyFileName);
        log_data = new LogData(LogLevel::kDebug, kSettingsProvider, kReadAWSSettings,
            std::string("clientId=") + client_id + std::string(",endpoint=") + endpoint + std::string(",port=") + port
        );
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
        log_data = new LogData(LogLevel::kDebug, kSettingsProvider, kReadAWSSettings,
            std::string("rootCA = ") + root_ca
        );
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
        log_data = new LogData(LogLevel::kDebug, kSettingsProvider, kReadAWSSettings,
            std::string("deviceCert = ") + device_certificate
        );
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
        log_data = new LogData(LogLevel::kDebug, kSettingsProvider, kReadAWSSettings,
            std::string("privateKey = ") + private_key
        );
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
    }
    catch (std::invalid_argument e)
    {
        log_data = new LogData(LogLevel::kError, kSettingsProvider, kReadAWSSettings, e.what());
        event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
        return nullptr;
    }

    return new AWSSettings(client_id, endpoint, port, root_ca, device_certificate, private_key);
}
