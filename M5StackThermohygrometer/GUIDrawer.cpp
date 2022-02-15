#include "GUIDrawer.hpp"

#include <M5Stack.h>

GUIDrawer::GUIDrawer()
{
    M5.Lcd.setTextSize(2);
}

GUIDrawer::~GUIDrawer()
{
}

void GUIDrawer::DisplayMeasurementResult(MeasurementResult* result)
{
    M5.Lcd.setCursor(0, 100);
    M5.Lcd.printf("Time: %s\nTemp: %2.2f 'C\nHumi: %2.2f\%\n", result->time.c_str(), result->thermohygro_data->temperature, result->thermohygro_data->humidity);
}
