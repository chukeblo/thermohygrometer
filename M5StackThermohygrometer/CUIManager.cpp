#include "CUIManager.hpp"

CUIManager::CUIManager()
{
    Initialize();
}

CUIManager::~CUIManager()
{
    delete console_logger_;
}

void CUIManager::Initialize()
{
    console_logger_ = new ConsoleLogger();
}

void CUIManager::HandleEvent(EventData* event_data)
{
    switch (event_data->type)
    {
    case EventType::kLogDataGenerated:
        console_logger_->Log((LogData*)(event_data->context));
        break;    
    default:
        break;
    }
}
