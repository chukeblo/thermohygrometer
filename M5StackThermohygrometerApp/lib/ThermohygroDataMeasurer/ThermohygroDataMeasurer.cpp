#include "ThermohygroDataMeasurer.hpp"

#include <ConsoleLogger.hpp>
#include <LogConstants.hpp>
#include <MeasurementResult.hpp>
#include <MeasurementResultManager.hpp>

// 温湿度測定実施のインターバル[minutes]
static const int kMeasureIntervalMins = 1;
// 測定結果送信実施のインターバル[hours]
static const int kSendingIntervalHours = 1;

ThermohygroDataMeasurer::ThermohygroDataMeasurer()
{
	next_measure_mins_ = -1;
	next_sending_hours_ = -1;
}

ThermohygroDataMeasurer::~ThermohygroDataMeasurer()
{
}

void ThermohygroDataMeasurer::SetMeasureEnvDataListener(MeasureEnvDataListener* listener)
{
	measure_env_data_listener_ = listener;
}

void ThermohygroDataMeasurer::SetCommunicationClient(CommunicationClient* client)
{
	communication_client_ = client;
}

void ThermohygroDataMeasurer::ReadThermohygroData()
{
	struct tm tm;
	getLocalTime(&tm);
	next_measure_mins_ = (kMeasureIntervalMins * ((tm.tm_min / kMeasureIntervalMins) + 1) % 60);
	next_sending_hours_ = (tm.tm_hour + 1) % 24;

	while (true)
	{
		getLocalTime(&tm);
		if (IsTimeForMeasurement(tm.tm_min))
		{
			ThermohygroData* data = thermohydrosensor_.ReadThermohygroData();
			if (data)
			{
				MeasurementResult* result = new MeasurementResult(GetStringTimeFrom(&tm), data);
				ConsoleLogger::Log(new LogData(LogLevel::kDebug, kThermohygroDataMeasurer, kReadThermohygroData,
					"measurement result: time=" + result->time +
					", temperature=" + std::string(String(result->thermohygro_data->temperature).c_str()) +
					", humidity=" + std::string(String(result->thermohygro_data->humidity).c_str())
				));
				MeasurementResultManager::GetInstance()->AddMeasurementResult(result);
				if (measure_env_data_listener_)
				{
					measure_env_data_listener_->OnMeasureEnvData();
				}
				else
				{
					ConsoleLogger::Log(new LogData(LogLevel::kError, kThermohygroDataMeasurer, kReadThermohygroData,
						"MeasureEnvDataListener instance is not attached"
					));
				}
				if (communication_client_)
				{
					communication_client_->SendThermohygroData(result);
				}
				else
				{
					ConsoleLogger::Log(new LogData(LogLevel::kError, kThermohygroDataMeasurer, kReadThermohygroData,
						"CommunicationClient instance is not attached"
					));
				}
			}
		}
		if (IsTimeForSendingEnvData(tm.tm_hour))
		{
			ConsoleLogger::Log(new LogData(LogLevel::kInfo, kThermohygroDataMeasurer, kReadThermohygroData,
				"sending environment data has been requested. time=" + GetStringTimeFrom(&tm)
			));
			if (communication_client_)
			{
				// communication_client_->SendThermohygroData(MeasurementResultManager::GetInstance()->GetResults().back());
			}
			else
			{
				ConsoleLogger::Log(new LogData(LogLevel::kError, kThermohygroDataMeasurer, kReadThermohygroData,
					"CommunicationClient instance is not attached"
				));
			}
		}
		delay(1000);
	}
}

bool ThermohygroDataMeasurer::IsTimeForMeasurement(int current_mins)
{
	if (current_mins != next_measure_mins_)
	{
		return false;
	}
	next_measure_mins_ = (next_measure_mins_ + kMeasureIntervalMins) % 60;
	return true;
}

bool ThermohygroDataMeasurer::IsTimeForSendingEnvData(int current_hours)
{
	if (current_hours != next_sending_hours_)
	{
		return false;
	}
	next_sending_hours_ = (next_sending_hours_ + kSendingIntervalHours) % 24;
	return true;
}

std::string ThermohygroDataMeasurer::GetStringTimeFrom(struct tm* tm)
{
	std::string timestamp = "";
	if (tm->tm_hour < 10)
	{
		timestamp += "0";
	}
	timestamp += std::string(String(tm->tm_hour).c_str());
	timestamp += ":";
	if (tm->tm_min < 10)
	{
		timestamp += "0";
	}
	timestamp += std::string(String(tm->tm_min).c_str());

	return timestamp;
}

void StartMeasureTask(void* context)
{
	ThermohygroDataMeasurer* measurer = static_cast<ThermohygroDataMeasurer*>(context);
	measurer->ReadThermohygroData();
}