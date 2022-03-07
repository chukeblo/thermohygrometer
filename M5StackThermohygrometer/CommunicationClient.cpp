#include "CommunicationClient.hpp"

#include <stdio.h>

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

static void MqttCallback(char* topic, byte* payload, unsigned int length)
{
	char tmp[length] = {};
	for (int i = 0; i < length; i++)
	{
		tmp[i] = (char)payload[i];
	}
	LogData* log_data = new LogData(LogLevel::kDebug, kCommunicationClient, "MqttCallback",
		std::string("received topic = ") + std::string(topic) + std::string(", payload = ") + std::string(tmp)
	);
	EventHandler::GetInstance()->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
}

void CommunicationClient::SendThermohygroData(MeasurementResult* result)
{
	SetUpMqttClient();
	mqtt_client_->setCallback(&MqttCallback);

	while (!mqtt_client_->connected())
	{
		if (ConnectToAws()) {
			LogData* log_data = new LogData(LogLevel::kInfo, kCommunicationClient, "SendThermohygroData", "connected to mqtt server");
			EventHandler::GetInstance()->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
      mqtt_client_->subscribe("/pub1", 0);
		}
		delay(2000);
	}

  LogData* log_data = new LogData(LogLevel::kInfo, kCommunicationClient, "SendThermohygroData", "connection preparation done.");
  EventHandler::GetInstance()->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
  
	mqtt_client_->loop();
	std::string publish_message = result->ToString();
	mqtt_client_->publish("pub1", publish_message.c_str());
  log_data = new LogData(LogLevel::kInfo, kCommunicationClient, "SendThermohygroData", "published message to aws");
  EventHandler::GetInstance()->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
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

bool CommunicationClient::SetUpMqttClient()
{
	http_client_->setCACert(settings_->aws_settings->root_ca.c_str());
	http_client_->setCertificate(settings_->aws_settings->device_certificate.c_str());
	http_client_->setPrivateKey(settings_->aws_settings->private_key.c_str());
	mqtt_client_->setServer(settings_->aws_settings->endpoint.c_str(), atoi(settings_->aws_settings->port.c_str()));
}

bool CommunicationClient::ConnectToAws()
{
	if (mqtt_client_->connect("M5StackThermohygrometer"))
	{
		LogData* log_data = new LogData(LogLevel::kInfo, kCommunicationClient, "SendThermohygroData", "connected to aws");
		EventHandler::GetInstance()->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
		return true;
	}

	LogData* log_data = new LogData(LogLevel::kError, kCommunicationClient, "SendThermohygroData",
		std::string("Failed to connect to aws: error state = ") + std::string(String(mqtt_client_->state()).c_str())
	);
	EventHandler::GetInstance()->AddEvent(new EventData(EventType::kLogDataGenerated, (void*)log_data));
	return false;
}
