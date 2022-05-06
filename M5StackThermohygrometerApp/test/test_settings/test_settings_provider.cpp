#include <Arduino.h>
#include <unity.h>

#include <string>

#include <SDCardConstants.hpp>
#include <SDCardController.hpp>
#include <SettingsProvider.hpp>
#include "../test_main.hpp"

static const std::string kWiFiSettingsFile = kSDCardRootPath + kWiFiSettingsFileName;
static const std::string kAWSSettingsFile = kSDCardRootPath + kAwsDocsFilePath + kAwsSettingsFileName;

static const std::string kSsid = "hoge";
static const std::string kPassword = "fuga";
static const std::string kWiFiSettingsJson
    = "{\"ssid\":\"" + kSsid + "\",\"password\":\"" + kPassword + "\"}";
static const std::string kClientId = "hoge";
static const std::string kEndpoint = "fuga";
static const int kPort = 8883;
static const std::string kRootCA = "hoge.pem";
static const std::string kDeviceCert = "hoge-certificate.pem.crt";
static const std::string kPrivateKey = "hoge-private.pem.key";
static const std::string kTopic = "piyo";
static const std::string kAWSSettingsJson
    = "{\"clientId\":\"" + kClientId + "\",\"endpoint\":\"" + kEndpoint +
        "\",\"port\":" + std::to_string(kPort) + ",\"rootCaPath\":\"" + kRootCA +
        "\",\"deviceCertPath\":\"" + kDeviceCert + "\",\"privateKeyPath\":\"" + kPrivateKey +
        "\",\"topic\":\"" + kTopic + "\"}";

class SDCardControllerMockForSettingsProvider : public SDCardController
{
public:
    std::string ReadFileFromSDCard(std::string file_name) override
    {
        if (file_name == kWiFiSettingsFile)
        {
            return kWiFiSettingsJson;
        }
        if (file_name == kAWSSettingsFile)
        {
            return kAWSSettingsJson;
        }
        return file_name;
    }
};

static void test_settings_provider_of(void)
{
    SDCardController* mock = new SDCardControllerMockForSettingsProvider();
    AWSCommunicationSettings* settings = SettingsProvider::Of(mock);
    TEST_ASSERT_NOT_NULL(settings);
    TEST_ASSERT_EQUAL_STRING(kSsid.c_str(), settings->wifi_settings->ssid.c_str());
    TEST_ASSERT_EQUAL_STRING(kPassword.c_str(), settings->wifi_settings->password.c_str());
    TEST_ASSERT_EQUAL_STRING(kClientId.c_str(), settings->aws_settings->client_id.c_str());
    TEST_ASSERT_EQUAL_STRING(kEndpoint.c_str(), settings->aws_settings->endpoint.c_str());
    TEST_ASSERT_EQUAL_INT32(kPort, settings->aws_settings->port);
    TEST_ASSERT_EQUAL_STRING((kSDCardRootPath + kAwsDocsFilePath + kRootCA).c_str(), settings->aws_settings->root_ca.c_str());
    TEST_ASSERT_EQUAL_STRING((kSDCardRootPath + kAwsDocsFilePath + kDeviceCert).c_str(), settings->aws_settings->device_certificate.c_str());
    TEST_ASSERT_EQUAL_STRING((kSDCardRootPath + kAwsDocsFilePath + kPrivateKey).c_str(), settings->aws_settings->private_key.c_str());
    TEST_ASSERT_EQUAL_STRING(kTopic.c_str(), settings->aws_settings->topic.c_str());
}

void run_settings_provider_tests()
{
    RUN_TEST(test_settings_provider_of);
}