#include <Arduino.h>
#include <unity.h>

#include <string>

#include <WiFiSettings.hpp>

void test_ctor(void)
{
    std::string ssid("hoge");
    std::string password("fuga");
    WiFiSettings* settings = new WiFiSettings(ssid, password);
    TEST_ASSERT_EQUAL_STRING(ssid.c_str(), settings->ssid.c_str());
    TEST_ASSERT_EQUAL_STRING(password.c_str(), settings->password.c_str());
}

void test_FromString(void)
{
    std::string ssid("hoge");
    std::string password("fuga");
    std::string wifi_settings_json("{\"ssid\":\"hoge\",\"password\":\"fuga\"}");
    WiFiSettings* settings = WiFiSettings::FromString(wifi_settings_json);
    TEST_ASSERT_EQUAL_STRING(ssid.c_str(), settings->ssid.c_str());
    TEST_ASSERT_EQUAL_STRING(password.c_str(), settings->password.c_str());
}

void setup()
{
    // wait for over 2 secs
    // if board does not support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();

    RUN_TEST(test_ctor);
    RUN_TEST(test_FromString);

    UNITY_END();
}

void loop()
{
}