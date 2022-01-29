#include "NetworkController.hpp"

#include <M5Stack.h>
#include <WiFi.h>
#include "LogConstants.hpp"
#include "Logger.hpp"

#define JST (3600L * 9)

NetworkController::NetworkController(const char* ssid, const char* password) : ssid_(ssid), password_(password), is_connected_(false)
{
}

NetworkController::~NetworkController()
{
}

bool NetworkController::Prepare()
{
	Logger::Log(LogLevel::kTrace, kNetworkController, kPrepare, "in");
	bool result = false;
	result = ConnectToWiFi();
	Logger::Log(LogLevel::kDebug, kNetworkController, kPrepare,
		std::string("network connect result = ") + std::string(String((int)result).c_str())
	);
	result = SyncronizeTime();
	Logger::Log(LogLevel::kDebug, kNetworkController, kPrepare,
		std::string("time sync result = ") + std::string(String((int)result).c_str())
	);
	Logger::Log(LogLevel::kTrace, kNetworkController, kPrepare, "out");
	return result;
}

bool NetworkController::ConnectToWiFi()
{
	WiFi.begin(ssid_, password_);
	Logger::Log(LogLevel::kInfo, kNetworkController, kConnectToWiFi, "connecting...");

	uint8_t status;
	while (true)
	{
		status = WiFi.status();
		if (status == WL_CONNECTED)
		{
			is_connected_ = true;
			Logger::Log(LogLevel::kInfo, kNetworkController, kConnectToWiFi, "connected");
			Logger::Log(LogLevel::kDebug, kNetworkController, kConnectToWiFi,
				std::string("ssid=") + std::string(ssid_) + std::string(",password=") + std::string(password_)
			);
			return true;
		}
		else if (status == WL_CONNECT_FAILED)
		{
			Logger::Log(LogLevel::kError, kNetworkController, kConnectToWiFi, "failed in WiFi connection");
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