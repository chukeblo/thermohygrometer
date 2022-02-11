#include "NetworkController.hpp"

#include <M5Stack.h>
#include <WiFi.h>
#include "EventHandler.hpp"
#include "LogConstants.hpp"
#include "LogData.hpp"

NetworkController::NetworkController(const char* ssid, const char* password) : ssid_(ssid), password_(password), is_connected_(false)
{
}

NetworkController::~NetworkController()
{
}

bool NetworkController::Prepare()
{
	LogData* log_data = new LogData(LogLevel::kTrace, kNetworkController, kPrepare, "in");
	EventHandler* event_handler = EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	bool result = false;
	result = ConnectToWiFi();
	log_data = new LogData(LogLevel::kDebug, kNetworkController, kPrepare,
		std::string("network connect result = ") + std::string(String((int)result).c_str())
	);
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	result = SyncronizeTime();
	log_data = new LogData(LogLevel::kDebug, kNetworkController, kPrepare,
		std::string("time sync result = ") + std::string(String((int)result).c_str())
	);
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	log_data = new LogData(LogLevel::kTrace, kNetworkController, kPrepare, "out");
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	return result;
}

bool NetworkController::ConnectToWiFi()
{
	WiFi.begin(ssid_, password_);
	LogData* log_data = new LogData(LogLevel::kInfo, kNetworkController, kConnectToWiFi, "connecting...");
	EventHandler* event_handler = EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));

	uint8_t status;
	while (true)
	{
		status = WiFi.status();
		if (status == WL_CONNECTED)
		{
			is_connected_ = true;
			log_data = new LogData(LogLevel::kInfo, kNetworkController, kConnectToWiFi, "connected");
			event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
			log_data = new LogData(LogLevel::kDebug, kNetworkController, kConnectToWiFi,
				std::string("ssid=") + std::string(ssid_) + std::string(",password=") + std::string(password_)
			);
			event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
			return true;
		}
		else if (status == WL_CONNECT_FAILED)
		{
			log_data = new LogData(LogLevel::kError, kNetworkController, kConnectToWiFi, "failed in WiFi connection");
			event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
			return false;
		}
		delay(500);
	}
}

bool NetworkController::SyncronizeTime()
{
	if (!is_connected_) {
		return false;
	}
	configTime(kJST, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
	return true;
}