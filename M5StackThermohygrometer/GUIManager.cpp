#include "GUIManager.hpp"

#include <M5Stack.h>
#include "ButtonType.hpp"
#include "ConsoleLogger.hpp"
#include "LogConstants.hpp"

GUIManager::MeasureEnvDataListenerImpl::MeasureEnvDataListenerImpl(GUIManager* gui_manager)
{
    gui_manager_ = gui_manager;
}

void GUIManager::MeasureEnvDataListenerImpl::OnMeasureEnvData()
{
    gui_manager_->NotifyEnvDataMeasured();
}

GUIManager::GUIManager(GUIContext* context)
{
    gui_context_ = context;
}

GUIManager::~GUIManager()
{
    delete gui_context_;
}

void GUIManager::CheckIfButtonsPressed()
{
    M5.update();
    if (M5.BtnA.wasPressed())
    {
        ConsoleLogger::Log(new LogData(LogLevel::kInfo, kGUIManager, kCheckIfButtonsPressed, "left button has been pressed."));
        gui_context_->OnButtonPressed(ButtonType::kLeftButton);
    }
    else if (M5.BtnB.wasPressed())
    {
        ConsoleLogger::Log(new LogData(LogLevel::kInfo, kGUIManager, kCheckIfButtonsPressed, "middle button has been pressed."));
        gui_context_->OnButtonPressed(ButtonType::kMiddleButton);
    }
    else if (M5.BtnC.wasPressed())
    {
        ConsoleLogger::Log(new LogData(LogLevel::kInfo, kGUIManager, kCheckIfButtonsPressed, "right button has been pressed."));
        gui_context_->OnButtonPressed(ButtonType::kRightButton);
    }
}

void GUIManager::NotifyEnvDataMeasured()
{
    gui_context_->OnMeasureEnvData();
}
