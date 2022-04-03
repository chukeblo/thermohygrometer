#include <SHT3X.h>

SHT3X::SHT3X(uint8_t address) : address_(address), c_temp_(0), f_temp_(0), humidity_(0)
{
	Wire.begin();
}

ThermohygroData* SHT3X::ReadThermohygroData()
{
	uint8_t result = ReadEnvData();
	if (result != kReadSuccess)
	{
		return nullptr;
	}
	return new ThermohygroData(c_temp_, humidity_);
}

uint8_t SHT3X::ReadEnvData()
{
	unsigned int data[6];

	// Start I2C Transmission
	Wire.beginTransmission(address_);
	// Send measurement command
	Wire.write(0x2C);
	Wire.write(0x06);
	// Stop I2C transmission
	if (Wire.endTransmission() != 0)
		return kWireInitFailure;

	delay(200);

	// Request 6 bytes of data
	Wire.requestFrom(address_, kReadBytes);

	// Read 6 bytes of data
	// cTemp msb, cTemp lsb, cTemp crc, humidity msb, humidity lsb, humidity crc
	for (int i = 0; i < kReadBytes; i++) {
		data[i] = Wire.read();
	};

	delay(50);

	if (Wire.available() != 0)
		return kWireUnavailable;

	// Convert the data
	c_temp_ = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
	f_temp_ = (c_temp_ * 1.8) + 32;
	humidity_ = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);

	return kReadSuccess;
}
