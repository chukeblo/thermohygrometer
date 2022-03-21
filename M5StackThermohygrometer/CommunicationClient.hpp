#pragma once

#include <string>

#include <WiFiClientSecure.h>
#include "src/PubSubClient/PubSubClient.h"
#include "AWSCommunicationSettings.hpp"
#include "MeasurementResult.hpp"

class CommunicationClient
{
private:
	const long kJST = 3600L * 9;

public:
	CommunicationClient();
	~CommunicationClient();

public:
	bool Prepare();
	void SendThermohygroData(MeasurementResult* result);

private:
	bool ConnectToWiFi();
	bool SyncronizeTime();
	bool SetUpMqttClient();
	bool ConnectToAws();

private:
	AWSCommunicationSettings* settings_;
	PubSubClient* mqtt_client_;
	WiFiClientSecure* http_client_;
};