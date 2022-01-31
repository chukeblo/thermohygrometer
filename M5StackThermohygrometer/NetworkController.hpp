#pragma once

class NetworkController
{
private:
	const long kJST = 3600L * 9;

public:
	NetworkController(const char* ssid, const char* password);
	~NetworkController();

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