#pragma once

class CommunicationClient
{
private:
	const long kJST = 3600L * 9;

public:
	CommunicationClient(const char* ssid, const char* password);
	~CommunicationClient();

public:
	bool Prepare();

private:
	bool ConnectToWiFi();
	bool SyncronizeTime();

private:
	const char* ssid_;
	const char* password_;
	bool is_connected_;
};