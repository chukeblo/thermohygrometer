#include <Arduino.h>
#include <unity.h>

#include "test_measurement_result_manager_main.hpp"
#include <MeasurementResult.hpp>

std::string kTime = "00:00:00";
ThermohygroData* thermohygro_data = new ThermohygroData(0.5f, 1.0f);

static void test_measurement_result_ctor(void)
{
    MeasurementResult* measurement_result = new MeasurementResult(kTime, thermohygro_data);
    TEST_ASSERT_NOT_NULL(measurement_result);
    TEST_ASSERT_EQUAL_STRING(kTime.c_str(), measurement_result->time.c_str());
    TEST_ASSERT_EQUAL(thermohygro_data, measurement_result->thermohygro_data);
}

static void test_measurement_result_CopyWith_nonnull(void)
{
    MeasurementResult* measurement_result = new MeasurementResult(kTime, thermohygro_data);
    TEST_ASSERT_NOT_NULL(measurement_result);
    MeasurementResult* copied = MeasurementResult::CopyWith(measurement_result);
    TEST_ASSERT_NOT_NULL(copied);
    TEST_ASSERT_EQUAL_STRING(measurement_result->time.c_str(), copied->time.c_str());
    TEST_ASSERT_EQUAL_FLOAT(measurement_result->thermohygro_data->temperature, copied->thermohygro_data->temperature);
    TEST_ASSERT_EQUAL_FLOAT(measurement_result->thermohygro_data->humidity, copied->thermohygro_data->humidity);
}

static void test_measurement_result_CopyWith_null(void)
{
    MeasurementResult* copied = MeasurementResult::CopyWith(nullptr);
    TEST_ASSERT_NULL(copied);
}

static void test_measurement_result_ToString(void)
{
    MeasurementResult* measurement_result = new MeasurementResult(kTime, thermohygro_data);
    TEST_ASSERT_NOT_NULL(measurement_result);
    std::string json = measurement_result->ToString();
    std::string expected_json = "{\"humidity\":\"1.00\",\"temperature\":\"0.50\",\"time\":\"00:00:00\"}";
    TEST_ASSERT_EQUAL_STRING(expected_json.c_str(), json.c_str());
}

void run_measurement_result_tests()
{
    RUN_TEST(test_measurement_result_ctor);
    RUN_TEST(test_measurement_result_CopyWith_nonnull);
    RUN_TEST(test_measurement_result_ToString);
}