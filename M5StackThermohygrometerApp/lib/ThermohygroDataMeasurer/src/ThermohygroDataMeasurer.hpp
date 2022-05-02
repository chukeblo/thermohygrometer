#pragma once

#include <string>

#include <CommunicationClient.hpp>
#include <SHT3X.h>

class ThermohygroDataMeasurer
{
public:
	class MeasureEnvDataListener
	{
	public:
		virtual ~MeasureEnvDataListener() {}

	public:
		virtual void OnMeasureEnvData() = 0;
	};

private:
	const int kReadSuccess = 0;

public:
	ThermohygroDataMeasurer();
	~ThermohygroDataMeasurer();

public:
	void SetMeasureEnvDataListener(MeasureEnvDataListener* listener);
	void SetCommunicationClient(CommunicationClient* client);
	void ReadThermohygroData();

private:
	bool IsTimeForMeasurement(int current_mins);
	bool IsTimeForSendingEnvData(int current_hours);
	std::string GetStringTimeFrom(struct tm* tm);

private:
	SHT3X thermohydrosensor_;
	MeasureEnvDataListener* measure_env_data_listener_;
	CommunicationClient* communication_client_;
	int next_measure_mins_;
	int next_sending_hours_;
};

void StartMeasureTask(void* context);