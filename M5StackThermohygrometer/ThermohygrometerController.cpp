#include "ThermohygrometerController.hpp"

#include <M5Stack.h>
#include "ConsoleLogger.hpp"
#include "EventHandler.hpp"
#include "LogConstants.hpp"
#include "MeasurementResult.hpp"
#include "SettingsProvider.hpp"

ThermohygrometerController::ThermohygrometerController()
{
	settings_ = SettingsProvider::Of();
	client_ = new CommunicationClient(settings_->aws_communication_settings);
	measurer_ = new ThermohygroDataMeasurer();
}

ThermohygrometerController::~ThermohygrometerController()
{
	delete settings_;
	delete client_;
	delete measurer_;
}

void ThermohygrometerController::MeasureThermohygroData()
{
	ConsoleLogger::Log(new LogData(LogLevel::kTrace, kThermohygrometerController, kReadThermohygroData, "in"));
	struct tm tm;
	getLocalTime(&tm);
}

void ThermohygrometerController::ConnectToMqttServer()
{
	MeasurementResult* result = new MeasurementResult("00:00:00", new ThermohygroData(20.0f, 40.0f));
	client_->SendThermohygroData(result);
}
