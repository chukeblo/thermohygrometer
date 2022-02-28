#include "AWSSettings.hpp"

#include <map>

#include "JsonHandler.hpp"
#include "SDCardConstants.hpp"
#include "SDCardController.hpp"

const std::string kClientIdKey = "clientId";
const std::string kEndpointKey = "endpoint";
const std::string kPortKey = "port";
const std::string kRootCaPathKey = "rootCaPath";
const std::string kDeviceCertPathKey = "deviceCertPath";
const std::string kPrivateKeyPathKey = "privateKeyPath";

AWSSettings::AWSSettings(std::string client_id, std::string endpoint, std::string port, std::string root_ca, std::string device_certificate, std::string private_key)
{
    this->client_id = client_id;
    this->endpoint = endpoint;
    this->port = port;
    this->root_ca = root_ca;
    this->device_certificate = device_certificate;
    this->private_key = private_key;
}

AWSSettings::~AWSSettings()
{
}

AWSSettings* AWSSettings::FromString(std::string json)
{
    std::map<std::string, std::string> aws_settings_map = JsonHandler::Parse(json);
    std::string client_id = aws_settings_map[kClientIdKey];
    std::string endpoint = aws_settings_map[kEndpointKey];
    std::string port = aws_settings_map[kPortKey];
    std::string root_ca = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + aws_settings_map[kRootCaPathKey]);
    std::string device_certificate = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + aws_settings_map[kDeviceCertPathKey]);
    std::string private_key = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + aws_settings_map[kPrivateKeyPathKey]);
    return new AWSSettings(client_id, endpoint, port, root_ca, device_certificate, private_key);
}