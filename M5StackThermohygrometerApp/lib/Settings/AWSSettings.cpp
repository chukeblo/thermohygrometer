#include <AWSSettings.hpp>

#include <map>

#include <JsonHandler.hpp>
#include <SDCardConstants.hpp>
#include <SDCardController.hpp>

const std::string kClientIdKey = "clientId";
const std::string kEndpointKey = "endpoint";
const std::string kPortKey = "port";
const std::string kTopicKey = "topic";
const std::string kRootCaPathKey = "rootCaPath";
const std::string kDeviceCertPathKey = "deviceCertPath";
const std::string kPrivateKeyPathKey = "privateKeyPath";

AWSSettings::AWSSettings(std::string client_id, std::string endpoint, int port, std::string root_ca, std::string device_certificate, std::string private_key, std::string topic)
{
    this->client_id = client_id;
    this->endpoint = endpoint;
    this->port = port;
    this->root_ca = root_ca;
    this->device_certificate = device_certificate;
    this->private_key = private_key;
    this->topic = topic;
}

AWSSettings::~AWSSettings()
{
}

AWSSettings* AWSSettings::FromString(std::string json)
{
    std::map<std::string, JsonElement*> aws_settings_map = JsonHandler::Parse(json);
    JsonStringElement* client_id_element = static_cast<JsonStringElement*>(aws_settings_map[kClientIdKey]);
    std::string client_id = client_id_element->data;
    JsonStringElement* endpoint_element = static_cast<JsonStringElement*>(aws_settings_map[kEndpointKey]);
    std::string endpoint = endpoint_element->data;
    JsonNumberElement* port_element = static_cast<JsonNumberElement*>(aws_settings_map[kPortKey]);
    int port = port_element->data;
    JsonStringElement* topic_element = static_cast<JsonStringElement*>(aws_settings_map[kTopicKey]);
    std::string topic = topic_element->data;
    JsonStringElement* root_ca_path_element = static_cast<JsonStringElement*>(aws_settings_map[kRootCaPathKey]);
    JsonStringElement* device_cert_path_element = static_cast<JsonStringElement*>(aws_settings_map[kDeviceCertPathKey]);
    JsonStringElement* private_key_path_element = static_cast<JsonStringElement*>(aws_settings_map[kPrivateKeyPathKey]);
    std::string root_ca = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + root_ca_path_element->data);
    std::string device_certificate = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + device_cert_path_element->data);
    std::string private_key = SDCardController::ReadFileFromSDCard(kSDCardRootPath + kAwsDocsFilePath + private_key_path_element->data);
    return new AWSSettings(client_id, endpoint, port, root_ca, device_certificate, private_key, topic);
}