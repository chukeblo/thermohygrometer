#include <Arduino.h>
#include <unity.h>

#include "test_measurement_result_manager_main.hpp"

void setup()
{
    // wait for over 2 secs
    // if board does not support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();

    // unit tests for MeasurementResultManager lib
    run_measurement_result_tests();

    UNITY_END();
}

void loop()
{
}