#include <Arduino.h>
#include <unity.h>

#include "test_settings_main.hpp"

void setup()
{
    // wait for over 2 secs
    // if board does not support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();

    // unit tests for Settings lib
    run_aws_settings_tests();
    run_wifi_settings_tests();
    run_aws_communication_settings_tests();
    run_settings_provider_tests();

    UNITY_END();
}

void loop()
{
}