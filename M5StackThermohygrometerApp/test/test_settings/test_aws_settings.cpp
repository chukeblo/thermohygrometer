#include <Arduino.h>
#include <unity.h>

#include <string>

#include "../test_main.hpp"
#include <AWSSettings.hpp>
#include <SDCardController.hpp>

class SDCardControllerMock : public SDCardController
{
public:
    std::string ReadFileFromSDCard(std::string file_name) override { return file_name; }
};

static void test_aws_settings_ctor(void)
{
	std::string client_id = "client_id";
	std::string endpoint = "endpoint";
	int port = 0;
	std::string root_ca = "root_ca";
	std::string device_certificate = "device_certificate";
	std::string private_key = "private_key";
	std::string topic = "topic";

    AWSSettings* settings = new AWSSettings(client_id, endpoint, port, root_ca, device_certificate, private_key, topic);
    TEST_ASSERT_EQUAL_STRING(client_id.c_str(), settings->client_id.c_str());
    TEST_ASSERT_EQUAL_STRING(endpoint.c_str(), settings->endpoint.c_str());
    TEST_ASSERT_EQUAL_INT32(port, settings->port);
    TEST_ASSERT_EQUAL_STRING(root_ca.c_str(), settings->root_ca.c_str());
    TEST_ASSERT_EQUAL_STRING(device_certificate.c_str(), settings->device_certificate.c_str());
    TEST_ASSERT_EQUAL_STRING(private_key.c_str(), settings->private_key.c_str());
    TEST_ASSERT_EQUAL_STRING(topic.c_str(), settings->topic.c_str());
}

static void test_aws_settings_FromString(void)
{
    std::string aws_settings_json("{\"clientId\":\"M5StackThermohygrometer\",\"endpoint\":\"a173nwsyyt709l-ats.iot.us-east-1.amazonaws.com\",\"port\":8883,\"rootCaPath\":\"AmazonRootCA1.pem\",\"deviceCertPath\":\"5c1d8dff120f7de45a8fb8c86c5d32656fb1f6220e3ebc273a8eb22fb1b11512-certificate.pem.crt\",\"privateKeyPath\":\"5c1d8dff120f7de45a8fb8c86c5d32656fb1f6220e3ebc273a8eb22fb1b11512-private.pem.key\",\"topic\":\"envdata\"}");
    SDCardController* sd_card_controller_mock = new SDCardControllerMock();
    AWSSettings* settings = AWSSettings::FromString(aws_settings_json, sd_card_controller_mock);
    delete sd_card_controller_mock;
    TEST_ASSERT_NOT_NULL(settings);
    TEST_ASSERT_EQUAL_STRING("M5StackThermohygrometer", settings->client_id.c_str());
    TEST_ASSERT_EQUAL_STRING("a173nwsyyt709l-ats.iot.us-east-1.amazonaws.com", settings->endpoint.c_str());
    TEST_ASSERT_EQUAL_INT32(8883, settings->port);
    TEST_ASSERT_FALSE(settings->root_ca.empty());
    TEST_ASSERT_FALSE(settings->device_certificate.empty());
    TEST_ASSERT_FALSE(settings->private_key.empty());
    TEST_ASSERT_EQUAL_STRING("envdata", settings->topic.c_str());
}

void run_aws_settings_tests()
{
    RUN_TEST(test_aws_settings_ctor);
    RUN_TEST(test_aws_settings_FromString);
}
