#pragma once

#include "Arduino.h"
#include "Wire.h"

class SHT3X {
private:
	const uint8_t kReadSuccess = 0;
	const uint8_t kWireInitFailure = 1;
	const uint8_t kWireUnavailable = 2;
	const uint8_t kReadBytes = 6;

public:
	SHT3X(uint8_t address = 0x44);

public:
	uint8_t TryReadEnvData(void);
	float GetCTemp();
	float GetFTemp();
	float GetHumidity();

private:
	uint8_t address_;
	float c_temp_;
	float f_temp_;
	float humidity_;
};
