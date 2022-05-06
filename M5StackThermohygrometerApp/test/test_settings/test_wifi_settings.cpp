#include <Arduino.h>
#include <unity.h>

#include <string>

#include "test_settings.hpp"
#include <WiFiSettings.hpp>

static void test_wifi_settings_ctor(void)
{
    std::string ssid("hoge");
    std::string password("fuga");
    WiFiSettings* settings = new WiFiSettings(ssid, password);
    TEST_ASSERT_EQUAL_STRING(ssid.c_str(), settings->ssid.c_str());
    TEST_ASSERT_EQUAL_STRING(password.c_str(), settings->password.c_str());
}

static void test_wifi_settings_FromString(void)
{
    std::string ssid("hoge");
    std::string password("fuga");
    std::string wifi_settings_json("{\"ssid\":\"hoge\",\"password\":\"fuga\"}");
    WiFiSettings* settings = WiFiSettings::FromString(wifi_settings_json);
    TEST_ASSERT_EQUAL_STRING(ssid.c_str(), settings->ssid.c_str());
    TEST_ASSERT_EQUAL_STRING(password.c_str(), settings->password.c_str());
}

void run_wifi_settings_tests()
{
    RUN_TEST(test_wifi_settings_ctor);
    RUN_TEST(test_wifi_settings_FromString);
}
