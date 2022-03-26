#pragma once

#include "CommunicationClient.hpp"

#include <string>

#include <WiFiClientSecure.h>
#include "src/PubSubClient/PubSubClient.h"
#include "AWSCommunicationSettings.hpp"

class CommunicationClientImpl : public CommunicationClient
{
private:
	const long kJST = 3600L * 9;

public:
	CommunicationClientImpl();
	~CommunicationClientImpl() override;

public:
	void Prepare() override;
	void SendThermohygroData(MeasurementResult* result) override;

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