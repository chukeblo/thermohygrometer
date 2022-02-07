#include "SettingsProvider.hpp"

#include <map>
#include <stdexcept>
#include <string>

#include "AWSCommunicationSettings.hpp"
#include "JsonHandler.hpp"
#include "LogConstants.hpp"
#include "Logger.hpp"
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
        Logger::Log(Logger::kErrorBit, kSettingsProvider, kReadThermohygrometerSettings, "not supported communication type");
        return nullptr;
    }
    CommunicationSettingsBase* communication_settings = ReadCommunicationSettings(communication_type);
    return new ThermohygrometerSettings(communication_type, communication_settings);
}

CommunicationSettingsBase* SettingsProvider::ReadCommunicationSettings(std::string communication_type)
{
    CommunicationSettingsBase* communication_settings = nullptr;
    if (communication_type == kAWSType)
    {
        WiFiSettings* wifi_settings = ReadWiFiSettings();
        AWSSettings* aws_settings = ReadAWSSettings();
        communication_settings =  new AWSCommunicationSettings(wifi_settings, aws_settings);
    }
    return communication_settings;
}

WiFiSettings* SettingsProvider::ReadWiFiSettings()
{
    Logger::Log(Logger::kTraceBit, kSettingsProvider, kReadWiFiSettings, "in");
    std::string ssid = "";
    std::string password = "";
    try
    {
        std::string raw_wifi_settings = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kWiFiSettingsFileName);
        std::map<std::string, std::string> wifi_settings_map = JsonHandler::Parse(raw_wifi_settings);
        ssid = wifi_settings_map[kSsidKey];
        password = wifi_settings_map[kPasswordKey];
        Logger::Log(Logger::kDebugBit, kSettingsProvider, kReadWiFiSettings,
            std::string("ssid=") + ssid + std::string(",password=") + password
        );
    }
    catch (std::invalid_argument e)
    {
        Logger::Log(Logger::kErrorBit, kSettingsProvider, kReadWiFiSettings, e.what());
        return nullptr;
    }
    return new WiFiSettings(ssid, password);
}

AWSSettings* SettingsProvider::ReadAWSSettings()
{
    Logger::Log(Logger::kTraceBit, kSettingsProvider, kReadAWSSettings, "in");
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
        Logger::Log(Logger::kDebugBit, kSettingsProvider, kReadAWSSettings,
            std::string("clientId=") + client_id + std::string(",endpoint=") + endpoint + std::string(",port=") + port
        );
        Logger::Log(Logger::kDebugBit, kSettingsProvider, kReadAWSSettings,
            std::string("rootCA = ") + root_ca
        );
        Logger::Log(Logger::kDebugBit, kSettingsProvider, kReadAWSSettings,
            std::string("deviceCert = ") + device_certificate
        );
        Logger::Log(Logger::kDebugBit, kSettingsProvider, kReadAWSSettings,
            std::string("privateKey = ") + private_key
        );
    }
    catch (std::invalid_argument e)
    {
        Logger::Log(Logger::kErrorBit, kSettingsProvider, kReadAWSSettings, e.what());
        return nullptr;
    }

    return new AWSSettings(client_id, endpoint, port, root_ca, device_certificate, private_key);
}
