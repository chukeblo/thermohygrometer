#pragma once

#include <string>

// Common
const std::string kSDCardRootPath = "/";

// Network Settings
// file name
const std::string kNetworkSettingsFileName = "network_settings.json";
// keys
const std::string kSsidKey = "ssid";
const std::string kPasswordKey = "password";

// AWS Docs
// file name
const std::string kAwsDocsFilePath = "aws_docs/";
const std::string kAwsConfigFileName = "aws_config.json";
const std::string kAWSRootCAFileName = "AmazonRootCAxxxx.pem";
const std::string kDeviceCertFileName = "xxxx-certificate.pem.crt";
const std::string kPrivateKeyFileName = "xxxx-private.pem.key";
// keys
const std::string kClientIdKey = "clientId";
const std::string kEndpointKey = "endpoint";