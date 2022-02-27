#include "MeasurementResult.hpp"

#include <map>

#include <M5Stack.h>
#include "JsonHandler.hpp"

const std::string kTimeKey = "time";
const std::string kTemperatureKey = "temperature";
const std::string kHumidityKey = "humidity";

MeasurementResult::MeasurementResult(std::string time, ThermohygroData* thermohygro_data)
{
    this->time = time;
    this->thermohygro_data = thermohygro_data;
}

MeasurementResult::~MeasurementResult()
{
    delete this->thermohygro_data;
}

std::string MeasurementResult::ToString()
{
    std::map<std::string, std::string> jsonMap;
    jsonMap.insert({kTimeKey, time});
    jsonMap.insert({kTemperatureKey, std::string(String(thermohygro_data->temperature).c_str())});
    jsonMap.insert({kHumidityKey, std::string(String(thermohygro_data->humidity).c_str())});
    return JsonHandler::Serialize(jsonMap);
}