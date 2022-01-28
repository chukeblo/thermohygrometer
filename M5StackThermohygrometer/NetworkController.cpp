#include "NetworkController.hpp"

#include <M5Stack.h>
#include <WiFi.h>

#define JST (3600L * 9)

NetworkController::NetworkController(const char* ssid, const char* password) : ssid_(ssid), password_(password), is_connected_(false)
{
}

NetworkController::~NetworkController()
{
}

bool NetworkController::Prepare()
{
	bool result = false;
	result = ConnectToWiFi();
	Serial.printf("network connect result = %d\n", result);
	result = SyncronizeTime();
	Serial.printf("time sync result = %d\n", result);
	return result;
}

bool NetworkController::ConnectToWiFi()
{
	WiFi.begin(ssid_, password_);
	Serial.println("NetworkController::ConnectToWiFi() connecting...");

	uint8_t status;
	while (true)
	{
		status = WiFi.status();
		if (status == WL_CONNECTED)
		{
			is_connected_ = true;
			Serial.println("NetworkController::ConnectToWiFi() WiFi connected");
			Serial.printf("NetworkController::ConnectToWiFi() ssid = %s\n", ssid_);
			Serial.printf("NetworkController::ConnectToWiFi() password = %s\n", password_);
			IPAddress ip_address = WiFi.localIP();
			Serial.printf("NetworkController::ConnectToWiFi() localIP = %d\n", (int32_t)ip_address);
			return true;
		}
		else if (status == WL_CONNECT_FAILED)
		{
			Serial.println("NetworkController::ConnectToWiFi() Failed in WiFi connection");
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
	configTime(JST, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
	return true;
}