#include <Arduino.h>
#include <unity.h>

#include <AWSCommunicationSettings.hpp>
#include "../test_main.hpp"

void test_aws_communication_settings_ctor(void)
{
    WiFiSettings* wifi_settings = new WiFiSettings(
        "ssid", "password"
    );
    AWSSettings* aws_settings = new AWSSettings(
        "client_id",
        "endpoint",
        0,
        "root_ca",
        "device_certificate",
        "private_key",
        "topic"
    );
    AWSCommunicationSettings* aws_communication_settings = new AWSCommunicationSettings(
        wifi_settings, aws_settings
    );
    TEST_ASSERT_NOT_NULL(aws_communication_settings);
    TEST_ASSERT_EQUAL(wifi_settings, aws_communication_settings->wifi_settings);
    TEST_ASSERT_EQUAL(aws_settings, aws_communication_settings->aws_settings);
}

void run_aws_communication_settings_tests()
{
    RUN_TEST(test_aws_communication_settings_ctor);
}