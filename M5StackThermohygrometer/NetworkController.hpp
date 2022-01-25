#pragma once

class NetworkController
{
public:
	NetworkController(char* ssid, char* password);
	~NetworkController();
	bool Prepare();

private:
	bool Connect();
	bool SyncronizeTime();

	char* ssid_;
	char* password_;
	bool is_connected_;
};