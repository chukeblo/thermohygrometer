#include "GUIManager.hpp"

#include <M5Stack.h>
#include "ButtonType.hpp"
#include "ConsoleLogger.hpp"
#include "LogConstants.hpp"
#include "MeasurementResult.hpp"

GUIManager::GUIManager()
{
    view_controller_ = new ViewController();
}

GUIManager::~GUIManager()
{
    delete view_controller_;
}

void GUIManager::CheckIfButtonsPressed()
{
    M5.update();
    if (BtnA.wasPressed())
    {
        ConsoleLogger::Log(new LogData(LogLevel::kInfo, kGUIManager, kCheckIfButtonsPressed, "left button has been pressed."));
        view_controller_->OnButtonPressed(ButtonType::kLeftButton);
    }
    else if (BtnB.wasPressed())
    {
        ConsoleLogger::Log(new LogData(LogLevel::kInfo, kGUIManager, kCheckIfButtonsPressed, "middle button has been pressed."));
        view_controller_->OnButtonPressed(ButtonType::kMiddleButton);
    }
    else if (BtnC.wasPressed())
    {
        ConsoleLogger::Log(new LogData(LogLevel::kInfo, kGUIManager, kCheckIfButtonsPressed, "right button has been pressed."));
        view_controller_->OnButtonPressed(ButtonType::kRightButton);
    }
}

void GUIManager::NotifyMeasurementResult(MeasurementResult* result)
{
    view_controller_->OnMeasureEnvData(result);
}
