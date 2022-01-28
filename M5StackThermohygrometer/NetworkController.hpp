#pragma once

class NetworkController
{
public:
	NetworkController(const char* ssid, const char* password);
	~NetworkController();
	bool Prepare();

private:
	bool Connect();
	bool SyncronizeTime();

	const char* ssid_;
	const char* password_;
	bool is_connected_;
};