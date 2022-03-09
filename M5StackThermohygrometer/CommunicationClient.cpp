#include "CommunicationClient.hpp"

#include <stdio.h>

#include <M5Stack.h>
#include "ConsoleLogger.hpp"
#include "EventHandler.hpp"
#include "LogConstants.hpp"

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
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kCommunicationClient, kPrepare, "in"));

	bool result = false;
	result = ConnectToWiFi();
	ConsoleLogger::Log(new LogData(LogLevel::kDebug, kCommunicationClient, kPrepare,
		std::string("network connect result = ") + std::string(String((int)result).c_str())
	));
	result = SyncronizeTime();
	ConsoleLogger::Log(new LogData(LogLevel::kDebug, kCommunicationClient, kPrepare,
		std::string("time sync result = ") + std::string(String((int)result).c_str())
	));
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kCommunicationClient, kPrepare, "out"));
	return result;
}

static void MqttCallback(char* topic, byte* payload, unsigned int length)
{
	char tmp[length] = {};
	for (int i = 0; i < length; i++)
	{
		tmp[i] = (char)payload[i];
	}
	ConsoleLogger::Log(new LogData(LogLevel::kDebug, kCommunicationClient, kMqttCallback,
		std::string("received topic = ") + std::string(topic) + std::string(", payload = ") + std::string(tmp)
	));
}

void CommunicationClient::SendThermohygroData(MeasurementResult* result)
{
	SetUpMqttClient();
	mqtt_client_->setCallback(&MqttCallback);

	while (!mqtt_client_->connected())
	{
		if (ConnectToAws()) {
			ConsoleLogger::Log(new LogData(LogLevel::kInfo, kCommunicationClient, kSendThrmohygroData, "connected to mqtt server"));
		}
		delay(2000);
	}

	mqtt_client_->loop();
	std::string message = result->ToString();
	mqtt_client_->publish(settings_->aws_settings->topic.c_str(), message.c_str());
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kCommunicationClient, kSendThrmohygroData,
		std::string("published message to aws. topic=") + settings_->aws_settings->topic + std::string(", message=") + message));
}

bool CommunicationClient::ConnectToWiFi()
{
	WiFi.begin(settings_->wifi_settings->ssid.c_str(), settings_->wifi_settings->password.c_str());
	ConsoleLogger::Log(new LogData(LogLevel::kInfo, kCommunicationClient, kConnectToWiFi, "connecting..."));

	uint8_t status;
	while (true)
	{
		status = WiFi.status();
		if (status == WL_CONNECTED)
		{
			ConsoleLogger::Log(new LogData(LogLevel::kInfo, kCommunicationClient, kConnectToWiFi, "connected"));
			ConsoleLogger::Log(new LogData(LogLevel::kDebug, kCommunicationClient, kConnectToWiFi,
				std::string("ssid=") + settings_->wifi_settings->ssid +
				std::string(",password=") + settings_->wifi_settings->password
			));
			return true;
		}
		else if (status == WL_CONNECT_FAILED)
		{
			ConsoleLogger::Log(new LogData(LogLevel::kError, kCommunicationClient, kConnectToWiFi, "failed in WiFi connection"));
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
	if (mqtt_client_->connect(settings_->aws_settings->client_id.c_str()));
	{
		ConsoleLogger::Log(new LogData(LogLevel::kInfo, kCommunicationClient, kConnectToAws, "connected to aws"));
		return true;
	}

	ConsoleLogger::Log(new LogData(LogLevel::kError, kCommunicationClient, kConnectToAws,
		std::string("Failed to connect to aws: error state = ") + std::string(String(mqtt_client_->state()).c_str())
	));
	return false;
}
