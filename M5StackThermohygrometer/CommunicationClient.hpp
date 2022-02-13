#pragma once

#include <string>

#include <WiFiClientSecure.h>
#include "src/PubSubClient/PubSubClient.h"
#include "AWSCommunicationSettings.hpp"

class CommunicationClient
{
private:
	const long kJST = 3600L * 9;

public:
	CommunicationClient(AWSCommunicationSettings* settings);
	~CommunicationClient();

public:
	bool Prepare();

private:
	bool ConnectToWiFi();
	bool SyncronizeTime();

private:
	AWSCommunicationSettings* settings_;
	PubSubClient* mqtt_client_;
	WiFiClientSecure* http_client_;
};