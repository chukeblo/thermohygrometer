#include <Arduino.h>
#include <unity.h>

#include "test_main.hpp"

void setup()
{
    // wait for over 2 secs
    // if board does not support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();

    run_aws_settings_tests();
    run_wifi_settings_tests();
    run_aws_communication_settings_tests();

    UNITY_END();
}

void loop()
{
}