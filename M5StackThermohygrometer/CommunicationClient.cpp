#include "CommunicationClient.hpp"

#include <M5Stack.h>
#include "EventHandler.hpp"
#include "LogConstants.hpp"
#include "LogData.hpp"

CommunicationClient::CommunicationClient(AWSCommunicationSettings* settings)
{
	settings_ = settings;
	http_client_ = new WiFiClientSecure();
	mqtt_client_ = new PubSubClient(*http_client_);
	Prepare();
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
	WiFi.begin(settings_->wifi_settings->ssid.c_str(), settings_->wifi_settings->password.c_str());
	LogData* log_data = new LogData(LogLevel::kInfo, kCommunicationClient, kConnectToWiFi, "connecting...");
	EventHandler* event_handler = EventHandler::GetInstance();
	event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));

	uint8_t status;
	while (true)
	{
		status = WiFi.status();
		if (status == WL_CONNECTED)
		{
			log_data = new LogData(LogLevel::kInfo, kCommunicationClient, kConnectToWiFi, "connected");
			event_handler->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
			log_data = new LogData(LogLevel::kDebug, kCommunicationClient, kConnectToWiFi,
				std::string("ssid=") + settings_->wifi_settings->ssid +
				std::string(",password=") + settings_->wifi_settings->password
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
	if (WiFi.status() != WL_CONNECTED) {
		return false;
	}
	configTime(kJST, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
	return true;
}