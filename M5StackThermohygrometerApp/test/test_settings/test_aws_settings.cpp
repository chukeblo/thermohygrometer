#include <Arduino.h>
#include <unity.h>

#include <string>

#include "test_settings.hpp"
#include <AWSSettings.hpp>
#include <SDCardConstants.hpp>
#include <SDCardController.hpp>

static const std::string kClientId = "client_id";
static const std::string kEndpoint = "endpoint";
static const int kPort = 0;
static const std::string kRootCA = "root_ca";
static const std::string kDeviceCert = "device_certificate";
static const std::string kPrivateKey = "private_key";
static const std::string kTopic = "topic";

class SDCardControllerMockForAWSSettings : public SDCardController
{
public:
    std::string ReadFileFromSDCard(std::string file_name) override { return file_name; }
};

static void test_aws_settings_ctor(void)
{
    AWSSettings* settings = new AWSSettings(kClientId, kEndpoint, kPort, kRootCA, kDeviceCert, kPrivateKey, kTopic);
    TEST_ASSERT_EQUAL_STRING(kClientId.c_str(), settings->client_id.c_str());
    TEST_ASSERT_EQUAL_STRING(kEndpoint.c_str(), settings->endpoint.c_str());
    TEST_ASSERT_EQUAL_INT32(kPort, settings->port);
    TEST_ASSERT_EQUAL_STRING(kRootCA.c_str(), settings->root_ca.c_str());
    TEST_ASSERT_EQUAL_STRING(kDeviceCert.c_str(), settings->device_certificate.c_str());
    TEST_ASSERT_EQUAL_STRING(kPrivateKey.c_str(), settings->private_key.c_str());
    TEST_ASSERT_EQUAL_STRING(kTopic.c_str(), settings->topic.c_str());
}

static void test_aws_settings_FromString(void)
{
    std::string aws_settings_json
        = "{\"clientId\":\"" + kClientId + "\",\"endpoint\":\"" + kEndpoint +
            "\",\"port\":" + std::to_string(kPort) + ",\"rootCaPath\":\"" + kRootCA +
            "\",\"deviceCertPath\":\"" + kDeviceCert + "\",\"privateKeyPath\":\"" + kPrivateKey +
            "\",\"topic\":\"" + kTopic + "\"}";
    SDCardController* sd_card_controller_mock = new SDCardControllerMockForAWSSettings();
    AWSSettings* settings = AWSSettings::FromString(aws_settings_json, sd_card_controller_mock);
    delete sd_card_controller_mock;
    TEST_ASSERT_NOT_NULL(settings);
    TEST_ASSERT_EQUAL_STRING(kClientId.c_str(), settings->client_id.c_str());
    TEST_ASSERT_EQUAL_STRING(kEndpoint.c_str(), settings->endpoint.c_str());
    TEST_ASSERT_EQUAL_INT32(kPort, settings->port);
    TEST_ASSERT_EQUAL_STRING((kSDCardRootPath + kAwsDocsFilePath + kRootCA).c_str(), settings->root_ca.c_str());
    TEST_ASSERT_EQUAL_STRING((kSDCardRootPath + kAwsDocsFilePath + kDeviceCert).c_str(), settings->device_certificate.c_str());
    TEST_ASSERT_EQUAL_STRING((kSDCardRootPath + kAwsDocsFilePath + kPrivateKey).c_str(), settings->private_key.c_str());
    TEST_ASSERT_EQUAL_STRING(kTopic.c_str(), settings->topic.c_str());
}

void run_aws_settings_tests()
{
    RUN_TEST(test_aws_settings_ctor);
    RUN_TEST(test_aws_settings_FromString);
}
