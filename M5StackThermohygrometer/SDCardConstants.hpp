#pragma once

#include <string>

// Common
const std::string kSDCardRootPath = "/";

// Thermohygrometer Settings
// file name
const std::string kThermohygrometerSettingsFilename = "thermohygrometer_settings.json";
// keys
const std::string kCommunicationTypeKey = "communicationType";
// values
const std::string kAWSType = "aws";

// Communication Settings
// WiFi Settings
// file name
const std::string kWiFiSettingsFileName = "wifi_settings.json";
// keys
const std::string kSsidKey = "ssid";
const std::string kPasswordKey = "password";

// AWS Docs
// file name
const std::string kAwsDocsFilePath = "aws_docs/";
const std::string kAwsSettingsFileName = "aws_settings.json";
// keys
const std::string kEndpointKey = "endpoint";
const std::string kPortKey = "port";
const std::string kRootCaPath = "rootCaPath";
const std::string kDeviceCertPath = "deviceCertPath";
const std::string kPrivateKeyPath = "privateKeyPath";