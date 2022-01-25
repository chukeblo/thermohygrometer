#include "NetworkController.hpp"

#include <M5Stack.h>
#include <WiFi.h>

#define JST (3600L * 9)

NetworkController::NetworkController(char* ssid, char* password) : ssid_(ssid), password_(password), is_connected_(false)
{
}

NetworkController::~NetworkController()
{
}

bool NetworkController::Prepare()
{
	bool result = false;
	result = Connect();
	Serial.printf("network connect result = %d\n", result);
	result = SyncronizeTime();
	Serial.printf("time sync result = %d\n", result);
	return result;
}

bool NetworkController::Connect()
{
	WiFi.begin(ssid_, password_);
	Serial.println("connecting...");

	uint8_t status;
	while (true)
	{
		status = WiFi.status();
		if (status == WL_CONNECTED)
		{
			is_connected_ = true;
			Serial.printf("\nWiFi connected.\nssid=%s\npassword=%s\n", ssid_, password_);
			Serial.println(WiFi.localIP());
			return true;
		}
		else if (status == WL_CONNECT_FAILED)
		{
			Serial.println("\nFailed in WiFi connection");
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