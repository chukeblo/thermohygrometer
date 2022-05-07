#include <Arduino.h>
#include <unity.h>

#include "test_measurement_result_manager_main.hpp"
#include <MeasurementResultManager.hpp>

static void test_measurement_result_manager_GetInstance(void)
{
    MeasurementResultManager* manager1 = MeasurementResultManager::GetInstance();
    TEST_ASSERT_NOT_NULL(manager1);
    MeasurementResultManager* manager2 = MeasurementResultManager::GetInstance();
    TEST_ASSERT_NOT_NULL(manager2);
    TEST_ASSERT_EQUAL(manager1, manager2);
}

static void test_measurement_result_manager_AddMeasurementResult_GetResults(void)
{
    MeasurementResultManager* manager = MeasurementResultManager::GetInstance();
    std::list<MeasurementResult*> expected_list;
    for (int i = 0; i < 20; i++)
    {
        MeasurementResult* result = new MeasurementResult("00:00:00", new ThermohygroData(1.0f * i, 1.0f * i));
        expected_list.push_back(result);
        manager->AddMeasurementResult(result);
    }
    std::list<MeasurementResult*> results = manager->GetResults();
    TEST_ASSERT_EQUAL_UINT32(expected_list.size(), results.size());
    auto expected_itr = expected_list.begin();
    auto results_itr = results.begin();
    for (int i = 0; i < 20; i++)
    {
        MeasurementResult* expected = *expected_itr;
        MeasurementResult* result = *results_itr;
        TEST_ASSERT_EQUAL_STRING(expected->time.c_str(), result->time.c_str());
        TEST_ASSERT_EQUAL_FLOAT(expected->thermohygro_data->temperature, result->thermohygro_data->temperature);
        TEST_ASSERT_EQUAL_FLOAT(expected->thermohygro_data->humidity, result->thermohygro_data->humidity);
        expected_itr++;
        results_itr++;
    }
    MeasurementResult* added = new MeasurementResult("00:00:00", new ThermohygroData(20.0f, 20.0f));
    manager->AddMeasurementResult(added);
    std::list<MeasurementResult*> overflowed = manager->GetResults();
    TEST_ASSERT_EQUAL_UINT32(20, overflowed.size());
    MeasurementResult* added_to_list = overflowed.back();
    TEST_ASSERT_EQUAL_STRING(added->time.c_str(), added_to_list->time.c_str());
    TEST_ASSERT_EQUAL_FLOAT(added->thermohygro_data->temperature, added_to_list->thermohygro_data->temperature);
    TEST_ASSERT_EQUAL_FLOAT(added->thermohygro_data->humidity, added_to_list->thermohygro_data->humidity);
}

void run_measurement_result_manager_tests()
{
    RUN_TEST(test_measurement_result_manager_GetInstance);
    RUN_TEST(test_measurement_result_manager_AddMeasurementResult_GetResults);
}