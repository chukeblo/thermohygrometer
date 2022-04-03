#include <CommunicationClientImpl.hpp>

#include <stdio.h>

#include <M5Stack.h>
#include <ConsoleLogger.hpp>
#include <LogConstants.hpp>
#include <SettingsProvider.hpp>

CommunicationClientImpl::CommunicationClientImpl()
{
	settings_ = SettingsProvider::Of();
	http_client_ = new WiFiClientSecure();
	mqtt_client_ = new PubSubClient(*http_client_);
	Prepare();
}

CommunicationClientImpl::~CommunicationClientImpl()
{
}

void CommunicationClientImpl::Prepare()
{
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kCommunicationClient, kPrepare, "in"));

	bool result = false;
	result = ConnectToWiFi();
	ConsoleLogger::Log(new LogData(LogLevel::kDebug, kCommunicationClient, kPrepare,
		"network connect result=" + std::string(String((int)result).c_str())
	));
	result = SyncronizeTime();
	ConsoleLogger::Log(new LogData(LogLevel::kDebug, kCommunicationClient, kPrepare,
		"time sync result=" + std::string(String((int)result).c_str())
	));
	SetUpMqttClient();
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kCommunicationClient, kPrepare, "out"));
}

static void MqttCallback(char* topic, byte* payload, unsigned int length)
{
	char payload_char_array[length] = {};
	for (int i = 0; i < length; i++)
	{
		payload_char_array[i] = (char)payload[i];
	}
	ConsoleLogger::Log(new LogData(LogLevel::kDebug, kCommunicationClient, kMqttCallback,
		"received topic=" + std::string(topic) + ", payload=" + payload_char_array
	));
}

void CommunicationClientImpl::SendThermohygroData(MeasurementResult* result)
{
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
		"published message to aws. topic=" + settings_->aws_settings->topic + ", message=" + message));
}

bool CommunicationClientImpl::ConnectToWiFi()
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
				"ssid=" + settings_->wifi_settings->ssid + ",password=" + settings_->wifi_settings->password
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

bool CommunicationClientImpl::SyncronizeTime()
{
	if (WiFi.status() != WL_CONNECTED) {
		return false;
	}
	configTime(kJST, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
	return true;
}

bool CommunicationClientImpl::SetUpMqttClient()
{
	http_client_->setCACert(settings_->aws_settings->root_ca.c_str());
	http_client_->setCertificate(settings_->aws_settings->device_certificate.c_str());
	http_client_->setPrivateKey(settings_->aws_settings->private_key.c_str());
	mqtt_client_->setServer(settings_->aws_settings->endpoint.c_str(), settings_->aws_settings->port);
	mqtt_client_->setCallback(&MqttCallback);
}

bool CommunicationClientImpl::ConnectToAws()
{
	if (mqtt_client_->connect(settings_->aws_settings->client_id.c_str()));
	{
		ConsoleLogger::Log(new LogData(LogLevel::kInfo, kCommunicationClient, kConnectToAws, "connected to aws"));
		return true;
	}

	ConsoleLogger::Log(new LogData(LogLevel::kError, kCommunicationClient, kConnectToAws,
		"Failed to connect to aws: error state=" + std::string(String(mqtt_client_->state()).c_str())
	));
	return false;
}
