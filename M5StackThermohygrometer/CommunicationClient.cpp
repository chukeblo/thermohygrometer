#include "CommunicationClient.hpp"

#include <M5Stack.h>
#include <WiFi.h>
#include "EventHandler.hpp"
#include "LogConstants.hpp"
#include "LogData.hpp"

CommunicationClient::CommunicationClient(const char* ssid, const char* password) : ssid_(ssid), password_(password), is_connected_(false)
{
}

CommunicationClient::~CommunicationClient()
{
}

bool CommunicationClient::Prepare()
{
	LogData* log_data = new LogData(LogLevel::kTrace, kCommunicationClient, kPrepare, "in");
	EventHandler* event_handler = EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	
	bool result = false;
	result = ConnectToWiFi();
	log_data = new LogData(LogLevel::kDebug, kCommunicationClient, kPrepare,
		std::string("network connect result = ") + std::string(String((int)result).c_str())
	);
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	result = SyncronizeTime();
	log_data = new LogData(LogLevel::kDebug, kCommunicationClient, kPrepare,
		std::string("time sync result = ") + std::string(String((int)result).c_str())
	);
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	log_data = new LogData(LogLevel::kTrace, kCommunicationClient, kPrepare, "out");
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	return result;
}

bool CommunicationClient::ConnectToWiFi()
{
	WiFi.begin(ssid_, password_);
	LogData* log_data = new LogData(LogLevel::kInfo, kCommunicationClient, kConnectToWiFi, "connecting...");
	EventHandler* event_handler = EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));

	uint8_t status;
	while (true)
	{
		status = WiFi.status();
		if (status == WL_CONNECTED)
		{
			is_connected_ = true;
			log_data = new LogData(LogLevel::kInfo, kCommunicationClient, kConnectToWiFi, "connected");
			event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
			log_data = new LogData(LogLevel::kDebug, kCommunicationClient, kConnectToWiFi,
				std::string("ssid=") + std::string(ssid_) + std::string(",password=") + std::string(password_)
			);
			event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
			return true;
		}
		else if (status == WL_CONNECT_FAILED)
		{
			log_data = new LogData(LogLevel::kError, kCommunicationClient, kConnectToWiFi, "failed in WiFi connection");
			event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
			return false;
		}
		delay(500);
	}
}

bool CommunicationClient::SyncronizeTime()
{
	if (!is_connected_) {
		return false;
	}
	configTime(kJST, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
	return true;
}